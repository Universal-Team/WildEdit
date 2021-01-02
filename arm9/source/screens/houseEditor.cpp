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

#include "houseEditor.hpp"

extern std::vector<std::string> g_houseSizes, g_roomNames;

HouseEditor::HouseEditor() {
	this->house = save->house();
	this->activeRoom = this->house->room(0); // Load first room.
}

void HouseEditor::Draw(void) const {
	switch(this->Mode) {
		case 0:
			this->DrawBase();
			break;

		case 1:
			break;

		case 2:
			break;
	}
}

void HouseEditor::Logic(u16 hDown, touchPosition touch) {
	switch(this->Mode) {
		case 0:
			this->BaseLogic(hDown, touch);
			break;

		case 1:
			break;

		case 2:
			break;
	}
}

void HouseEditor::DrawBase(void) const {
	Gui::DrawTop(true);
	printTextCentered("WildEdit - " + Lang::get("HOUSE_EDITOR"), 0, 0, true, true);

	printTextCentered(Lang::get("HOUSE_DEBTS") + ": " + std::to_string(this->house->debts()), 0, 28, true, true);
	printTextCentered(Lang::get("HOUSE_SIZE") + ": " + g_houseSizes[this->house->size()], 0, 53, true, true);
}
void HouseEditor::BaseLogic(u16 hDown, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack();

		/* Display Save icon. */
		setSpriteVisibility(Gui::saveID, false, true);
		updateOam();
		Gui::DrawScreen();
		Gui::showPointer(true);
		return;
	}
}