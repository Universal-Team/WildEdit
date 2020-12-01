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

#include "gui.hpp"
#include "input.hpp"
#include "itemManager.hpp"
#include "overlay.hpp"
#include "stringDB.hpp"
#include <dirent.h>

extern std::vector<std::tuple<u16, std::string, std::string>> itemDB;
extern std::vector<std::string> itemCategories;
extern bool updatePointer;

static std::vector<std::tuple<u16, std::string, std::string>> search(std::vector<std::string> searchCategory = {""}, std::string searchResult = "", bool compare = false) {
	return StringDB::searchTuple(searchResult, searchCategory, itemDB, compare);
}

static void DrawList(int screenPos, bool background, std::vector<std::tuple<u16, std::string, std::string>> &list, const std::string Text) {
	drawRectangle(0, 0, 256, 192, DARKERER_GRAY, DARKER_GRAY, true, true);
	drawRectangle(0, 0, 256, 192, DARKERER_GRAY, DARKER_GRAY, true, false);
	printTextCentered(Text, 0, 0, true, true);

	if (background) {
		/* Clear screen. */
		drawRectangle(0, 0, 256, 192, DARKERER_GRAY, DARKER_GRAY, false, false);
	}

	/* Clear text. */
	drawRectangle(0, 0, 256, 192, CLEAR, false, true);

	/* Print list. */
	for (unsigned i = 0; i < std::min(9u, list.size() - screenPos); i++) {
		printText(std::get<1>(list[screenPos + i]), 4, 4 + (i * 20), false, true);
	}
}

/* Select Item from a list. */
u16 Overlays::SelectItem(u16 oldItem, const std::string &Text, bool showPointer, bool redrawScreen) {
	std::vector<std::tuple<u16, std::string, std::string>> itemList = itemDB;
	s32 selectedItem = (s32)ItemManager::getIndex(oldItem);

	/* Set pointer position. */
	setSpriteVisibility(Gui::pointerID, false, true);
	setSpritePosition(Gui::pointerID, false, 4 + getTextWidth(std::get<1>(itemList[0])), -2);
	updateOam();

	/* Clear Screen. */
	Gui::clearScreen(true, true);

	DrawList(selectedItem, true, itemList, Text);

	int held, pressed, screenPos = selectedItem, entriesPerScreen = 9;
	while(1) {
		do {
			swiWaitForVBlank();
			scanKeys();
			pressed = keysDown();
			held = keysDownRepeat();
		} while(!held);

		if (held & KEY_UP) {
			if (selectedItem > 0) selectedItem--;
			else selectedItem = itemList.size()-1;
		}

		if (held & KEY_DOWN) {
			if (selectedItem < (int)itemList.size()-1) selectedItem++;
			else selectedItem = 0;
		}

		if (held & KEY_LEFT) {
			selectedItem -= entriesPerScreen;
			if (selectedItem < 0) selectedItem = 0;
		}

		if (held & KEY_RIGHT) {
			selectedItem += entriesPerScreen;
			if (selectedItem > (int)itemList.size()-1) selectedItem = itemList.size()-1;
		}

		if (pressed & KEY_A) {
			if (showPointer) {
				setSpriteVisibility(Gui::pointerID, false, true);
				updatePointer = true;

			} else {
				setSpriteVisibility(Gui::pointerID, false, false);
				updateOam();
			}

			if (redrawScreen) Gui::DrawScreen();
			return std::get<0>(itemList[selectedItem]);
		}

		if (pressed & KEY_B) {
			if (showPointer) {
				setSpriteVisibility(Gui::pointerID, false, true);
				updatePointer = true;

			} else {
				setSpriteVisibility(Gui::pointerID, false, false);
				updateOam();
			}

			if (redrawScreen) Gui::DrawScreen();
			return oldItem;
		}

		if (pressed & KEY_X) {
			selectedItem = 0;
			itemList.clear();

			int category = Overlays::SelectList(itemCategories, 0, "Select an Item category.", false, false);

			std::vector<std::string> categoryNames;
			categoryNames.push_back({itemCategories[category]});

			const std::string searchResult = Input::getLine2("Enter your search.", "", true, false);
			itemList = search(categoryNames, searchResult);
			selectedItem = 0;
			screenPos = selectedItem;
			DrawList(screenPos, false, itemList, Text);
		}

		if (pressed & KEY_Y) {
			itemList = itemDB;
			selectedItem = 0;
			screenPos = selectedItem;
			DrawList(screenPos, false, itemList, Text);
		}

		/* Scroll screen if needed. */
		if (selectedItem < screenPos) {
			screenPos = selectedItem;
			DrawList(screenPos, false, itemList, Text);

		} else if (selectedItem > screenPos + entriesPerScreen - 1) {
			screenPos = selectedItem - entriesPerScreen + 1;
			DrawList(screenPos, false, itemList, Text);
		}

		/* Move pointer. */
		setSpritePosition(Gui::pointerID, false, 3 + getTextWidth(std::get<1>(itemList[selectedItem])), (20 * (selectedItem - screenPos) - 2) + 10);
		updateOam();
	}
}