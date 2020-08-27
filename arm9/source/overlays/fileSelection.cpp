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

#include "fileBrowse.hpp"
#include "gui.hpp"
#include "overlay.hpp"
#include <dirent.h>

static void DrawList(int screenPos, bool background, std::vector<DirEntry> dirContents, const std::string Text) {
	drawRectangle(0, 0, 256, 192, DARKERER_GRAY, DARKER_GRAY, true, false);
	printTextCentered(Text, 0, 0, true, true);
	if (background) {
		/* Clear screen. */
		drawRectangle(0, 0, 256, 192, DARKERER_GRAY, DARKER_GRAY, false, false);
	}
	
	/* Clear text. */
	drawRectangle(0, 0, 256, 192, CLEAR, false, true);
	/* Print list. */
	for (unsigned i = 0; i < std::min(9u, dirContents.size() - screenPos); i++) {
		printText(dirContents[screenPos + i].name, 4, 4 + (i * 20), false, true);
	}
}

std::string Overlays::SelectFile(const std::string initialPath, std::vector<std::string> fileType, const std::string Text) {
	s32 selectedFile = 0;
	bool dirChanged = false;
	std::vector<DirEntry> dirContents;

	/* Initial dir change. */
	dirContents.clear();
	chdir(initialPath.c_str());
	std::vector<DirEntry> dirContentsTemp;
	getDirectoryContents(dirContentsTemp, fileType);
	for(uint i = 0; i < dirContentsTemp.size(); i++) {
		dirContents.push_back(dirContentsTemp[i]);
	}

	/* Set pointer position. */
	setSpriteVisibility(Gui::pointerID, false, true);
	setSpritePosition(Gui::pointerID, false, 4 + getTextWidth(dirContents[0].name), -2);
	updateOam();

	/* Clear Screen. */
	Gui::clearScreen(true, true);

	DrawList(selectedFile, true, dirContents, Text);

	int held, pressed, screenPos = selectedFile, entriesPerScreen = 9;
	while(1) {
		do {
			swiWaitForVBlank();
			scanKeys();
			pressed = keysDown();
			held = keysDownRepeat();
		} while(!held);

		// if directory changed -> Refresh it.
		if (dirChanged) {
			dirChanged = false;
			dirContents.clear();
			std::vector<DirEntry> dirContentsTemp;
			getDirectoryContents(dirContentsTemp, fileType);
			for(uint i = 0; i < dirContentsTemp.size(); i++) {
				dirContents.push_back(dirContentsTemp[i]);
			}

			selectedFile = 0;
			screenPos = 0;
			DrawList(screenPos, true, dirContents, Text);

		}

		if (held & KEY_UP) {
			if (selectedFile > 0) selectedFile--;
			else selectedFile = dirContents.size()-1;
		}
		
		if (held & KEY_DOWN) {
			if (selectedFile < (int)dirContents.size()-1) selectedFile++;
			else selectedFile = 0;
		}
		
		if (held & KEY_LEFT) {
			selectedFile -= entriesPerScreen;
			if (selectedFile < 0) selectedFile = 0;
		}
		
		if (held & KEY_RIGHT) {
			selectedFile += entriesPerScreen;
			if (selectedFile > (int)dirContents.size()-1) selectedFile = dirContents.size()-1;
		}
		
		if (pressed & KEY_A) {
			if (dirContents[selectedFile].isDirectory) {
				chdir(dirContents[selectedFile].name.c_str());
				selectedFile = 0;
				dirChanged = true;
			} else {
				char path[PATH_MAX];
				getcwd(path, PATH_MAX);
				std::string output = path + dirContents[selectedFile].name;
				Gui::DrawScreen();
				return output;
			}
		}

		if (pressed & KEY_B) {
			char path[PATH_MAX];
			getcwd(path, PATH_MAX);
			if (strcmp(path, "sd:/") == 0 || strcmp(path, "fat:/") == 0 || strcmp(path, "/") == 0) {
				Gui::DrawScreen();
				return "";
			} else {
				chdir("..");
				selectedFile = 0;
				dirChanged = true;
			}
		}

		/* Scroll screen if needed. */
		if (selectedFile < screenPos) {
			screenPos = selectedFile;
			DrawList(screenPos, false, dirContents, Text);
		} else if (selectedFile > screenPos + entriesPerScreen - 1) {
			screenPos = selectedFile - entriesPerScreen + 1;
			DrawList(screenPos, false, dirContents, Text);
		}

		/* Move pointer. */
		setSpritePosition(Gui::pointerID, false, 3 + getTextWidth(dirContents[selectedFile].name), (20 * (selectedFile - screenPos) - 2) + 10);
		updateOam();
	}
}