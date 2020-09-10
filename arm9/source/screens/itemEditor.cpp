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

#include "itemEditor.hpp"
#include "itemManager.hpp"
#include "overlay.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);

ItemEditor::ItemEditor(std::unique_ptr<Player> &refPlayer) : player(refPlayer) {
	for (int i = 0; i < 15; i++) {
		this->pockets[i] = this->player->pocket(i);
	}

	for (int i = 0; i < 90; i++) {
		this->dresser[i] = this->player->dresser(i);
	}
}

ItemEditor::~ItemEditor() { }

void ItemEditor::Draw(void) const {
	switch(this->Mode) {
		case 0:
			this->DrawSubMenu();
			break;

		case 1:
			this->DrawPocket();
			break;

		case 2:
			this->DrawDresser();
			break;
	}
}

void ItemEditor::Logic(u16 hDown, touchPosition touch) {
	switch(this->Mode) {
		case 0:
			this->SubMenuLogic(hDown, touch);
			break;

		case 1:
			this->PocketLogic(hDown, touch);
			break;

		case 2:
			this->DresserLogic(hDown, touch);
			break;
	}
}

void ItemEditor::DrawSubMenu() const {
	Gui::DrawTop(true);
	printTextCentered("WildEdit", 0, 0, true, true);
	
	Gui::DrawBottom(true);

	for (int i = 0; i < 2; i++) {
		drawRectangle(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, GRAY, false, true);
	}

	printTextCentered(Lang::get("POCKET"), 0, 40, false, true);
	printTextCentered(Lang::get("DRESSER"), 0, 90, false, true);
}

void ItemEditor::DrawPocket() const {
	Gui::DrawTop(true);
	printTextCentered(Lang::get("CURRENT_ITEM") + this->pockets[this->Selection]->name(), 0, 170, true, true);
	
	Gui::DrawBottom(false);
	for (int i = 0; i < 15; i++) {
		drawRectangle(pocketPos[i].x, pocketPos[i].y, pocketPos[i].w, pocketPos[i].h, ItemManager::getColor(this->pockets[i]->itemtype()), false, true);
		drawOutline(pocketPos[i].x - 2, pocketPos[i].y - 1, pocketPos[i].w + 2, pocketPos[i].h + 2, BLACK, false, true);
	}
}

void ItemEditor::DrawDresser() const {
	Gui::DrawTop(true);
	printTextCentered("WildEdit - " + Lang::get("DRESSER") + std::to_string(this->box + 1), 0, 0, true, true);
	printTextCentered(Lang::get("CURRENT_ITEM") + this->dresser[(this->box * 10) + this->Selection]->name(), 0, 170, true, true);
	
	Gui::DrawBottom(false);
	for (int i = 0; i < 10; i++) {
		drawRectangle(dresserPos[i].x, dresserPos[i].y, dresserPos[i].w, dresserPos[i].h, ItemManager::getColor(this->dresser[(this->box * 10) + i]->itemtype()), false, true);
		drawOutline(dresserPos[i].x - 2, dresserPos[i].y - 1, dresserPos[i].w + 2, dresserPos[i].h + 2, BLACK, false, true);
	}
}

void ItemEditor::SubMenuLogic(u16 hDown, touchPosition touch) {
	if (updatePointer) Gui::pointerUpdate(mainButtons[this->Selection].x+14, mainButtons[this->Selection].y+14);

	if (hDown & KEY_B) {
		Gui::screenBack();
		Gui::DrawScreen();
		updatePointer = true;
		return;
	}

	if (hDown & KEY_UP) {
		if (this->Selection > 0) {
			this->Selection--;
			updatePointer = true;
		}
	}
	
	if (hDown & KEY_DOWN) {
		if (this->Selection < 1) {
			this->Selection++;
			updatePointer = true;
		}
	}

	if (hDown & KEY_A) {
		switch(this->Selection) {
			case 0:
				this->Mode = 1;
				this->Selection = 0;
				Gui::DrawScreen();
				updatePointer = true;
				break;

			case 1:
				this->Mode = 2;
				this->Selection = 0;
				Gui::DrawScreen();
				updatePointer = true;
				break;
		}
	}
}

void ItemEditor::PocketLogic(u16 hDown, touchPosition touch) {
	if (updatePointer) Gui::pointerUpdate(pocketPos[this->Selection].x+10, pocketPos[this->Selection].y+10);

	if (hDown & KEY_B) {
		this->Mode = 0;
		this->Selection = 0;
		Gui::DrawScreen();
		updatePointer = true;
	}

	if (hDown & KEY_A) {
		this->pockets[this->Selection]->id(Overlays::SelectItem(this->pockets[this->Selection]->id(), Lang::get("SELECT_ITEM")));
		Gui::DrawScreen();
	}

	if (hDown & KEY_RIGHT) {
		if (this->Selection < 14) {
			this->Selection++;
			Gui::DrawScreen();
			updatePointer = true;
		}
	}

	if (hDown & KEY_LEFT) {
		if (this->Selection > 0) {
			this->Selection--;
			Gui::DrawScreen();
			updatePointer = true;
		}
	}
}

void ItemEditor::DresserLogic(u16 hDown, touchPosition touch) {
	if (updatePointer) Gui::pointerUpdate(dresserPos[this->Selection].x+10, dresserPos[this->Selection].y+10);

	if (hDown & KEY_B) {
		this->Mode = 0;
		this->Selection = 0;
		Gui::DrawScreen();
		updatePointer = true;
	}

	if (hDown & KEY_A) {
		this->dresser[(this->box * 10) + this->Selection]->id(Overlays::SelectItem(this->dresser[(this->box * 10) + this->Selection]->id(), Lang::get("SELECT_ITEM")));
		Gui::DrawScreen();
	}

	if (hDown & KEY_RIGHT) {
		if (this->Selection < 9) {
			this->Selection++;
			Gui::DrawScreen();
			updatePointer = true;
		}
	}

	if (hDown & KEY_LEFT) {
		if (this->Selection > 0) {
			this->Selection--;
			Gui::DrawScreen();
			updatePointer = true;
		}
	}

	if (hDown & KEY_R) {
		if (this->box < 8) {
			this->box++;
			Gui::DrawScreen();
			updatePointer = true;
		}
	}

	if (hDown & KEY_L) {
		if (this->box > 0) {
			this->box--;
			Gui::DrawScreen();
			updatePointer = true;
		}
	}
}