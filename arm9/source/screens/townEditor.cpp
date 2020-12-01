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

#include "acresEditor.hpp"
#include "townEditor.hpp"
#include "townMapEditor.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);

TownEditor::TownEditor(std::unique_ptr<Town> refTown) : town(std::move(refTown)) { };

TownEditor::~TownEditor() { };

void TownEditor::Draw(void) const {
	Gui::DrawTop(true);
	printTextCentered("WildEdit - " + Lang::get("TOWN_EDITOR"), 0, 0, true, true);

	Gui::DrawBottom(true);
	for (int i = 0; i < 3; i++) {
		drawRectangle(townButtons[i].x, townButtons[i].y, townButtons[i].w, townButtons[i].h, GRAY, false, true);
	}

	printTextCentered(Lang::get("ACRES_EDITOR"), 0, 40, false, true);
	printTextCentered(Lang::get("TOWN_MAP_EDITOR"), 0, 90, false, true);
}

void TownEditor::Logic(u16 hDown, touchPosition touch) {
	if (updatePointer) Gui::pointerUpdate(townButtons[this->selection].x+60, townButtons[this->selection].y+12);

	if (hDown & KEY_B) {
		setSpriteVisibility(Gui::saveID, false, true);
		Gui::screenBack();
		Gui::DrawScreen();
		updatePointer = true;
		return;
	}

	if (hDown & KEY_DOWN) {
		if (this->selection < 1) {
			this->selection++;
			updatePointer = true;
		}
	}

	if (hDown & KEY_UP) {
		if (this->selection > 0) {
			this->selection--;
			updatePointer = true;
		}
	}

	if (hDown & KEY_A) {
		switch(this->selection) {
			case 0:
				Gui::setScreen(std::make_unique<AcresEditor>(this->town));
				Gui::DrawScreen();
				updatePointer = true;
				break;

			case 1:
				Gui::setScreen(std::make_unique<TownMapEditor>(this->town));
				Gui::DrawScreen();
				Gui::showPointer(false);
				updateOam();
				break;
		}
	}
}