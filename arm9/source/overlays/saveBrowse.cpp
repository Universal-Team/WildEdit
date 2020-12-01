/*
*   This file is part of WildEdit
*   Copyright (C) 2020 Universal-Team
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "cardSaves.hpp"
#include "coreUtils.hpp"
#include "fileBrowse.hpp"
#include "flashcard.hpp"
#include "gui.hpp"
#include "lang.hpp"
#include "overlay.hpp"
#include "stringUtils.hpp"
#include <dirent.h>
#include <fat.h>

#define ENTRIES_PER_SCREEN 11
#define ENTRY_PAGE_LENGTH 10
bool showTopMenuOnExit = true, noCardMessageSet = false;
char fatLabel[14];
char sdLabel[14];
extern bool loadedFromCart;
int tmSlot1Offset = 0, tmCurPos = 0, tmScreenOffset = 0;

struct topMenuItem {
	std::string name;
	bool valid;
};

static void updateDriveLabel(bool fat) {
	if (fat) {
		fatGetVolumeLabel("fat", fatLabel);
		for (int i = 0; i < 12; i++) {
			if (((fatLabel[i] == ' ') && (fatLabel[i+1] == ' ') && (fatLabel[i+2] == ' '))
			|| ((fatLabel[i] == ' ') && (fatLabel[i+1] == ' '))
			|| (fatLabel[i] == ' ')) {
				fatLabel[i] = '\0';
				break;
			}
		}

	} else {
		fatGetVolumeLabel("sd", sdLabel);
		for (int i = 0; i < 12; i++) {
			if (((sdLabel[i] == ' ') && (sdLabel[i+1] == ' ') && (sdLabel[i+2] == ' '))
			|| ((sdLabel[i] == ' ') && (sdLabel[i+1] == ' '))
			|| (sdLabel[i] == ' ')) {
				sdLabel[i] = '\0';
				break;
			}
		}
	}
}

static void DrawSDText(int i, bool valid) {
	char str[20];
	updateDriveLabel(false);
	snprintf(str, sizeof(str), "sd: (%s)", sdLabel[0] == '\0' ? Lang::get("SD_CARD").c_str() : sdLabel);
	printTextTinted(str, valid ? TextColor::white : TextColor::red, 10, (i+1)*16, false, true);
}

static void DrawFatText(int i, bool valid) {
	char str[21];
	updateDriveLabel(true);
	snprintf(str, sizeof(str), "fat: (%s)", fatLabel[0] == '\0' ? Lang::get("FLASHCARD").c_str() : fatLabel);
	printTextTinted(str, valid ? TextColor::white : TextColor::red, 10, (i+1)*16, false, true);
}

static void DrawSlot1Text(int i, bool valid) {
	char slot1Text[34];
	snprintf(slot1Text, sizeof(slot1Text), "Slot-1: (%s) [%s]", REG_SCFG_MC == 0x11 ? Lang::get("NO_CARD_INSERTED").c_str() : gamename, gameid);
	printTextTinted(slot1Text, valid ? TextColor::white : TextColor::red, 10, (i+1)*16, false, true);
}

static bool updateSlot1Text(int &cardWait, bool valid) {
	if (REG_SCFG_MC == 0x11) {
		disableSlot1();
		cardWait = 30;

		if (!noCardMessageSet) {
			drawRectangle(10, ((tmSlot1Offset - tmScreenOffset) + 1) * 16, 246, 16, CLEAR, false, true);
			printText("Slot-1: " + Lang::get("NO_CARD_INSERTED"), 10, ((tmSlot1Offset - tmScreenOffset) + 1) *16, false, true);
			noCardMessageSet = true;
			return false;
		}
	}

	if (cardWait > 0) {
		cardWait--;

	} else if(cardWait == 0) {
		cardWait--;
		enableSlot1();

		if (updateCardInfo()) {
			valid = isValidTid(gameid);
			drawRectangle(10, ((tmSlot1Offset - tmScreenOffset) + 1) * 16, 246, 16, CLEAR, false, true);
			DrawSlot1Text(tmSlot1Offset - tmScreenOffset, valid);
			noCardMessageSet = false;
			return valid;
		}
	}

	return valid;
}

static void showDirectoryContents(const std::vector<DirEntry>& dirContents, int startRow) {
	char path[PATH_MAX];
	getcwd(path, PATH_MAX);

	/* Print path. */
	drawRectangle(0, 0, 256, 16, CLEAR, false, true);
	printTextMaxW(path, 250, 1, 4, 0, false, true);

	/* Print directory listing. */
	for(int i = 0; i < ENTRIES_PER_SCREEN; i++) {
		/* Clear row. */
		drawRectangle(10, (i+1)*16, 246, 16, CLEAR, false, true);

		if (i < ((int)dirContents.size() - startRow)) {
			std::u16string name = StringUtils::UTF8toUTF16(dirContents[i + startRow].name);

			/* Trim to fit on screen. */
			bool addEllipsis = false;
			while(getTextWidth(name) > 227) {
				name = name.substr(0, name.length()-1);
				addEllipsis = true;
			}

			if (addEllipsis) name += StringUtils::UTF8toUTF16("...");

			printText(name, 10, i*16+16, false, true);
		}
	}
}

static void showTopMenu(const std::vector<topMenuItem> &topMenuContents) {
	for(unsigned i=0;i<ENTRIES_PER_SCREEN;i++) {
		/* Clear row. */
		drawRectangle(10, (i+1)*16, 246, 16, CLEAR, false, true);

		if (i < topMenuContents.size()) {
			if (topMenuContents[i+tmScreenOffset].name == "fat:") DrawFatText(i, topMenuContents[i+tmScreenOffset].valid);
			else if (topMenuContents[i+tmScreenOffset].name == "sd:") DrawSDText(i, topMenuContents[i+tmScreenOffset].valid);
			else if (topMenuContents[i+tmScreenOffset].name == Lang::get("CARD")) DrawSlot1Text(i, topMenuContents[i+tmScreenOffset].valid);
			else {
				std::u16string name = StringUtils::UTF8toUTF16(topMenuContents[i+tmScreenOffset].name);
				name = name.substr(name.find_last_of(StringUtils::UTF8toUTF16("/"))+1); // Remove path to the file

				/* Trim to fit on screen. */
				bool addEllipsis = false;
				while(getTextWidth(name) > 227) {
					name = name.substr(0, name.length()-1);
					addEllipsis = true;
				}

				if (addEllipsis) name += StringUtils::UTF8toUTF16("...");

				printTextTinted(name, topMenuContents[i+tmScreenOffset].valid ? TextColor::white : TextColor::red, 10, i*16+16, false, true);
			}
		}
	}
}

static std::string topMenuSelect(void) {
	int pressed, held;
	touchPosition touch;

	drawRectangle(0, 0, 256, 192, DARKER_GRAY, true, false);
	drawRectangle(0, 0, 256, 192, DARKER_GRAY, false, false);

	/* Clear text. */
	drawRectangle(0, 0, 256, 192, CLEAR, true, true);
	drawRectangle(0, 0, 256, 192, CLEAR, false, true);

	/* Print version number of the app. */
	printText(VER_NUMBER, 256-getTextWidth(VER_NUMBER)-1, 176, true, true);

	if (!flashcardFound()) updateCardInfo();

	std::vector<topMenuItem> topMenuContents;

	if (flashcardFound()) topMenuContents.push_back({ "fat:", true });
	if (sdFound()) topMenuContents.push_back({ "sd:", true });
	if (!flashcardFound()) topMenuContents.push_back({ Lang::get("CARD"), false });
	if (!flashcardFound()) tmSlot1Offset = topMenuContents.size()-1;

	FILE *favs = fopen((sdFound() ? "sd:/_nds/WildEdit/favorites.lst" : "fat:/_nds/WildEdit/favorites.lst"), "rb");

	if (favs) {
		char *line = nullptr;
		size_t len = 0;

		while(__getline(&line, &len, favs) != -1) {
			line[strlen(line)-1] = '\0'; // Remove newline.
			topMenuContents.push_back({ line, (access(line, F_OK) == 0) });
		}
	}

	int cardWait = 0;
	if (!flashcardFound())	topMenuContents[tmSlot1Offset].valid = updateSlot1Text(cardWait, topMenuContents[tmSlot1Offset].valid);

	/* Show topMenuContents. */
	showTopMenu(topMenuContents);

	while(1) {
		/* Clear old cursors. */
		drawRectangle(0, 16, 10, 176, CLEAR, false, true);

		/* Draw cursor. */
		drawRectangle(3, (tmCurPos-tmScreenOffset)*16+24, 4, 3, LIGHT_GRAY, false, true);

		/* Power saving loop. Only poll the keys once per frame and sleep the CPU if there is nothing else to do. */
		do {
			swiWaitForVBlank();
			scanKeys();
			pressed = keysDown();
			held = keysDownRepeat();

			if (!flashcardFound()) {
				if (tmScreenOffset <= tmSlot1Offset) {
					topMenuContents[tmSlot1Offset].valid = updateSlot1Text(cardWait, topMenuContents[tmSlot1Offset].valid);
				}
			}

		} while(!held);

		if (held & KEY_UP) {
			if (tmCurPos > 0) tmCurPos -= 1;
			else tmCurPos = topMenuContents.size()-1;
		}

		if (held & KEY_DOWN) {
			if (tmCurPos < (int)topMenuContents.size()-1) tmCurPos += 1;
			else tmCurPos = 0;
		}

		if (held & KEY_LEFT) {
			tmCurPos -= ENTRY_PAGE_LENGTH;
			if (tmCurPos < 0) tmCurPos = 0;
		}

		if (held & KEY_RIGHT) {
			tmCurPos += ENTRY_PAGE_LENGTH;
			if (tmCurPos > (int)topMenuContents.size()-1) tmCurPos = topMenuContents.size()-1;
		}

		if (pressed & KEY_A) {
			selection:
			if (topMenuContents[tmCurPos].name == "fat:") {
				chdir("fat:/");
				return "";

			} else if (topMenuContents[tmCurPos].name == "sd:") {
				chdir("sd:/");
				return "";

			} else if (topMenuContents[tmCurPos].name == Lang::get("CARD") && topMenuContents[tmSlot1Offset].valid) {
				dumpSave();
				showTopMenuOnExit = 1;
				loadedFromCart = true;
				return cardSave;

			} else if (topMenuContents[tmCurPos].valid) {
				showTopMenuOnExit = 1;
				return topMenuContents[tmCurPos].name;
			}
		}

		if (pressed & KEY_X) {
			if ((topMenuContents[tmCurPos].name != "fat:") && (topMenuContents[tmCurPos].name != "sd:") && (topMenuContents[tmCurPos].name != Lang::get("CARD"))) {
				topMenuContents.erase(topMenuContents.begin() + tmCurPos);

				FILE *out = fopen((sdFound() ? "sd:/_nds/WildEdit/favorites.lst" : "fat:/_nds/WildEdit/favorites.lst"), "wb");

				if (out) {
					for(int i=0;i<(int)topMenuContents.size();i++) {
						if (topMenuContents[i].name != "fat:" && topMenuContents[i].name != "sd:" && topMenuContents[i].name != Lang::get("CARD")) {
							fwrite((topMenuContents[i].name+"\n").c_str(), 1, (topMenuContents[i].name+"\n").size(), out);
						}
					}

					fclose(out);
				}

				if (tmCurPos > (int)topMenuContents.size()-1) {
					tmCurPos = topMenuContents.size()-1;
					tmScreenOffset = std::max(tmCurPos - ENTRIES_PER_SCREEN + 1, 0);
				}

				showTopMenu(topMenuContents);
			}
		}

		if (pressed & KEY_TOUCH) {
			touchRead(&touch);
			for(int i = 0; i < std::min(ENTRIES_PER_SCREEN, (int)topMenuContents.size()); i++) {
				if (touch.py > (i+1)*16 && touch.py < (i+2)*16) {
					tmCurPos = i;
					goto selection;
				}
			}
		}

		/* Scroll screen if needed. */
		if (tmCurPos < tmScreenOffset) {
			tmScreenOffset = tmCurPos;
			showTopMenu(topMenuContents);

		} else if (tmCurPos > tmScreenOffset + ENTRIES_PER_SCREEN - 1) {
			tmScreenOffset = tmCurPos - ENTRIES_PER_SCREEN + 1;
			showTopMenu(topMenuContents);
		}

		if (held & KEY_UP || held & KEY_DOWN || held & KEY_LEFT || held & KEY_RIGHT || pressed & KEY_X) {
			/* Clear the path area of the screen. */
			drawRectangle(0, 0, 256, 16, CLEAR, false, true);

			/* Print the path to the currently selected file. */
			std::u16string path = StringUtils::UTF8toUTF16(topMenuContents[tmCurPos].name);
			path = path.substr(0, path.find_last_of(StringUtils::UTF8toUTF16("/"))+1); // Cut to just the path
			printTextMaxW(path, 250, 1, 4, 0, false, true);
		}
	}
}

static std::string browseForFile(const std::vector<std::string> &extensionList, bool accessSubdirectories, bool canChooseDirs) {
	char startPath[PATH_MAX];
	if (!accessSubdirectories) getcwd(startPath, PATH_MAX);
	int pressed, held, screenOffset = 0, fileOffset = 0;
	touchPosition touch;
	std::vector<DirEntry> dirContents;

	getDirectoryContents(dirContents, extensionList);
	showDirectoryContents(dirContents, screenOffset);

	while(1) {
		/* Clear old cursors. */
		drawRectangle(0, 16, 10, 176, CLEAR, false, true);

		/* Draw cursor. */
		drawRectangle(3, (fileOffset - screenOffset) * 16 + 24, 4, 3, LIGHT_GRAY, false, true);


		/* Power saving loop. Only poll the keys once per frame and sleep the CPU if there is nothing else to do. */
		do {
			swiWaitForVBlank();
			scanKeys();
			pressed = keysDown();
			held = keysDownRepeat();
		} while(!held);

		if (held & KEY_UP) {
			if (fileOffset > 0)	fileOffset -= 1;
			else fileOffset = dirContents.size()-1;
		}

		if (held & KEY_DOWN) {
			if (fileOffset < (int)dirContents.size()-1)	fileOffset += 1;
			else fileOffset = 0;
		}

		if (held & KEY_LEFT) {
			fileOffset -= ENTRY_PAGE_LENGTH;
			if (fileOffset < 0)	fileOffset = 0;
		}

		if (held & KEY_RIGHT) {
			fileOffset += ENTRY_PAGE_LENGTH;
			if (fileOffset > (int)dirContents.size()-1)	fileOffset = dirContents.size()-1;
		}

		if (pressed & KEY_A) {
			selection:
			DirEntry* entry = &dirContents.at(fileOffset);
			if (entry->isDirectory && !canChooseDirs) {
				/* Don't go up directory if in the start directory. */
				char path[PATH_MAX];
				getcwd(path, PATH_MAX);
				if (!accessSubdirectories && entry->name == ".." && (strcmp(startPath, path) == 0))	continue;

				/* Enter selected directory. */
				chdir(entry->name.c_str());
				getDirectoryContents(dirContents, extensionList);
				screenOffset = 0;
				fileOffset = 0;
				showDirectoryContents(dirContents, screenOffset);

			} else {
				/* Return the chosen file. */
				return entry->name;
			}
		}

		if (pressed & KEY_B) {
			/* Don't go up directory if in the start directory. */
			char path[PATH_MAX];
			getcwd(path, PATH_MAX);

			if (!accessSubdirectories && (strcmp(startPath, path) == 0)) return "";

			/* Go up a directory. */
			if ((strcmp (path, "sd:/") == 0) || (strcmp (path, "fat:/") == 0)) {
				std::string str = topMenuSelect();
				if (str != "") return str;

			} else {
				chdir("..");
			}

			getDirectoryContents(dirContents, extensionList);
			screenOffset = 0;
			fileOffset = 0;
			showDirectoryContents(dirContents, screenOffset);
		}

		if (pressed & KEY_Y && !dirContents[fileOffset].isDirectory && accessSubdirectories) { // accessSubdirectory check is a hack to make it not trigger except in save selection.
			if (CoreUtils::loadSave(dirContents[fileOffset].name)) {
				char path[PATH_MAX];
				getcwd(path, PATH_MAX);

				FILE *favs = fopen((sdFound() ? "sd:/_nds/WildEdit/favorites.lst" : "fat:/_nds/WildEdit/favorites.lst"), "ab");

				if (favs) {
					fwrite((path+dirContents[fileOffset].name+"\n").c_str(), 1, (path+dirContents[fileOffset].name+"\n").size(), favs);
					fclose(favs);
				}
			}
		}

		if (pressed & KEY_TOUCH) {
			touchRead(&touch);
			for(int i = 0; i < std::min(ENTRIES_PER_SCREEN, (int)dirContents.size()); i++) {
				if (touch.py > (i+1)*16 && touch.py < (i+2)*16) {
					fileOffset = i;
					goto selection;
				}
			}
		}

		/* Scroll screen if needed. */
		if (fileOffset < screenOffset) {
			screenOffset = fileOffset;
			showDirectoryContents(dirContents, screenOffset);

		} else if (fileOffset > screenOffset + ENTRIES_PER_SCREEN - 1) {
			screenOffset = fileOffset - ENTRIES_PER_SCREEN + 1;
			showDirectoryContents(dirContents, screenOffset);
		}
	}
}

std::string Overlays::browseForSave(void) {
	if (showTopMenuOnExit) {
		showTopMenuOnExit = 0;
		std::string str = topMenuSelect();
		if (str != "") return str;
	}

	drawRectangle(0, 0, 256, 192, DARKER_GRAY, true, false);
	drawRectangle(0, 0, 256, 192, DARKER_GRAY, false, false);

	/* Clear text. */
	drawRectangle(0, 0, 256, 192, CLEAR, true, true);
	drawRectangle(0, 0, 256, 192, CLEAR, false, true);

	std::vector<std::string> extensionList;
	extensionList.push_back("sav");
	char sav[6];

	for(int i = 1; i < 10; i++) {
		snprintf(sav, sizeof(sav), "sav%i", i);
		extensionList.push_back(sav);
	}

	return browseForFile(extensionList, true, false);
}