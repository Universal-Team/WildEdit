/*
*   This file is part of WildEdit
*   Copyright (C) 2020-2021 Universal-Team
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
#include "overlay.hpp"
#include <dirent.h>

extern bool updatePointer;

static void DrawList(int screenPos, bool background, std::vector<std::string> contents, const std::string Text) {
	drawRectangle(0, 0, 256, 192, DARKERER_GRAY, DARKER_GRAY, true, false);
	printTextCentered(Text, 0, 0, true, true);

	if (background) {
		/* Clear screen. */
		drawRectangle(0, 0, 256, 192, DARKERER_GRAY, DARKER_GRAY, false, false);
	}

	/* Clear text. */
	drawRectangle(0, 0, 256, 192, CLEAR, false, true);

	/* Print list. */
	for (unsigned i = 0; i < std::min(9u, contents.size() - screenPos); i++) {
		printText(contents[screenPos + i], 4, 4 + (i * 20), false, true);
	}
}

/* Select from a list. */
int Overlays::SelectList(const std::vector<std::string> &contents, int oldIndex, const std::string &Text, bool showPointer, bool redrawScreen) {
	int selectedEntry = 0;

	/* Set pointer position. */
	setSpriteVisibility(Gui::pointerID, false, true);
	setSpritePosition(Gui::pointerID, false, 4 + getTextWidth(contents[0]), -2);
	updateOam();

	/* Clear Screen. */
	Gui::clearScreen(true, true);

	DrawList(selectedEntry, true, contents, Text);

	int held, pressed, screenPos = selectedEntry, entriesPerScreen = 9;
	while(1) {
		do {
			swiWaitForVBlank();
			scanKeys();
			pressed = keysDown();
			held = keysDownRepeat();
		} while(!held);

		if (held & KEY_UP) {
			if (selectedEntry > 0) selectedEntry--;
			else selectedEntry = contents.size()-1;
		}

		if (held & KEY_DOWN) {
			if (selectedEntry < (int)contents.size()-1) selectedEntry++;
			else selectedEntry = 0;
		}

		if (held & KEY_LEFT) {
			selectedEntry -= entriesPerScreen;
			if (selectedEntry < 0) selectedEntry = 0;
		}

		if (held & KEY_RIGHT) {
			selectedEntry += entriesPerScreen;
			if (selectedEntry > (int)contents.size()-1) selectedEntry = contents.size()-1;
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
			return selectedEntry;
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
			return oldIndex;
		}

		/* Scroll screen if needed. */
		if (selectedEntry < screenPos) {
			screenPos = selectedEntry;
			DrawList(screenPos, false, contents, Text);

		} else if (selectedEntry > screenPos + entriesPerScreen - 1) {
			screenPos = selectedEntry - entriesPerScreen + 1;
			DrawList(screenPos, false, contents, Text);
		}

		/* Move pointer. */
		setSpritePosition(Gui::pointerID, false, 3 + getTextWidth(contents[selectedEntry]), (20 * (selectedEntry - screenPos) - 2) + 10);
		updateOam();
	}
}