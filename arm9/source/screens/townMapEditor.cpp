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

#include "graphicManagement.hpp"
#include "itemManager.hpp"
#include "itemUtils.hpp"
#include "gui.hpp"
#include "input.hpp"
#include "overlay.hpp"
#include "townMapEditor.hpp"

TownMapEditor::TownMapEditor(std::unique_ptr<Town> &refTown) : town(refTown) {
	/* Get Town Items. */
	for (int i = 0; i < 4096; i++) this->MapItems[i] = this->town->item(i);

	for (int i = 0; i < 36; i++) this->townAcres[i] = this->town->acre(i);

	/* Initialize Temp Item. */
	this->TempItem = 65521;

	/* Init Top Town Map Acre sprites. */
	for (int i = 0; i < 16; i++) {
		this->topAcres[i] = maxSpriteMain + i;
		initSprite(true, SpriteSize_32x32, this->topAcres[i]);
		prepareSprite(this->topAcres[i], true, TopPos[i].x, TopPos[i].y, 1);
		setSpriteVisibility(this->topAcres[i], true, true);
		fillSpriteImage(this->topAcres[i], true, 32, 0, 0, loadImage("/graphics/acres/" + std::to_string(this->townAcres[this->SelectionToAcre(i)]->id()) + ".gfx"));
	}
}

TownMapEditor::~TownMapEditor() {
	/* Free allocated OAM for the top acres here and hide. */
	for (int i = 0; i < 16; i++) {
		setSpriteVisibility(this->topAcres[i], true, false);

		if (spritesMain[this->topAcres[i]].gfx) oamFreeGfx(&oamMain, spritesMain[this->topAcres[i]].gfx);
	}
}

void TownMapEditor::Draw(void) const {
	switch(this->Mode) {
		case 0:
			this->DrawMain();
			break;

		case 1:
			this->DrawTempItem();
			break;
	}
}

void TownMapEditor::Logic(u16 hDown, touchPosition touch) {
	switch(this->Mode) {
		case 0:
			this->MainLogic(hDown, touch);
			break;

		case 1:
			this->TempLogic(hDown, touch);
			break;
	}
}

/* NOTES:
	32x32 is the native Acre resolution.
	32 * 5 -> 160;; 160 % 16 --> 10.
	Notes end.
*/
void TownMapEditor::DrawGrid(void) const {
	for (int i = 0 + (this->currentAcre * 256); i < 256 + (this->currentAcre * 256); i++) {
		for (u32 y = 0; y < 16; y++) {
			for (u32 x = 0; x < 16; x++, i++) {
				drawRectangle(10 + (x*10), 15 + (y*10), 10, 10, ItemManager::getColor(this->MapItems[i]->itemtype()), false, true);
				drawOutline(10 + (x*10), 15 + (y*10), 10, 10, BLACK, false, true);
			}
		}
	}
}

/* Draw the current position / Selector / Cursor. */
void TownMapEditor::DrawPosition(void) const {
	drawOutline(10 + (this->currentPosX*10), 15 + (this->currentPosY*10), 10, 10, LIGHT_GRAY, false, true);
}

/* Draw the information such as Item Name, Position. */
void TownMapEditor::DrawInformation() const {
	int x;
	if (this->currentAcre < 4)	x = this->currentAcre;
	else if (this->currentAcre > 3 && this->currentAcre < 8) x = this->currentAcre - 4;
	else if (this->currentAcre > 7 && this->currentAcre < 12) x = this->currentAcre - 8;
	else	x = this->currentAcre - 12;
	drawOutline(10 + (x*32), 30 + (this->currentAcre/4*32), 32, 32, BLACK, true, true);

	/* Display Informations. */
	printText(Lang::get("CURRENT_POSITION") + "\n" + std::to_string(this->PositionX) + " | " + std::to_string(this->PositionY), 150, 40, true, true);
	printText(Lang::get("CURRENT_ITEM") + "\n" + ItemUtils::getName(this->MapItems[this->MapSelection]->id()), 150, 70, true, true);
}

/* Update the Top Screen. */
void TownMapEditor::updateTopGrid() {
	Gui::clearScreen(true, true); // Clear Top.
	DrawInformation();
}

/* Update Bottom Screen. */
void TownMapEditor::updateBottomGrid() {
	Gui::clearScreen(false, true); // Clear Bottom.

	/* Update Item Grid. */
	for (int i = 0 + (this->currentAcre * 256); i < 256 + (this->currentAcre * 256); i++) {
		for (u32 y = 0; y < 16; y++) {
			for (u32 x = 0; x < 16; x++, i++) {
				drawRectangle(10 + (x*10), 15 + (y*10), 10, 10, ItemManager::getColor(this->MapItems[i]->itemtype()), false, true);
				drawOutline(10 + (x*10), 15 + (y*10), 10, 10, BLACK, false, true);
			}
		}
	}

	DrawPosition(); // Draw Position cursor.
}

/* Update Acre Image from the bottom screen. */
void TownMapEditor::updateAcreImage() {
	Gui::clearScreen(false, false); // Clear Layer.
	Gui::DrawBottom(false); // Draw Base UI.
	GraphicManagement::DrawAcre(this->townAcres[this->SelectionToAcre(this->currentAcre)]->id(), 10, 15, 5, 5, false, false);
	drawRectangle(175, 100, 75, 25, GRAY, false, false);
	printText(Lang::get("TEMP_ITEM"), 178, 105, false, false);
}

/* Initial draw. */
void TownMapEditor::DrawMain(void) const {
	Gui::DrawTop(false);

	for (int i = 0; i < 16; i++) {
		for (u32 y = 0; y < 4; y++) {
			for (u32 x = 0; x < 4; x++, i++) {
				drawOutline(10 + (x*32), 30 + (y*32), 32, 32, BLACK, true, false);
			}
		}
	}

	this->DrawInformation();

	Gui::DrawBottom(false);
	GraphicManagement::DrawAcre(this->townAcres[this->SelectionToAcre(this->currentAcre)]->id(), 10, 15, 5, 5, false, false);
	this->DrawGrid();
	this->DrawPosition();

	drawRectangle(175, 100, 75, 25, GRAY, false, false);
	printText(Lang::get("TEMP_ITEM"), 178, 105, false, false);
}

/* Draw Temp Item screen. */
void TownMapEditor::DrawTempItem() const {
	Gui::DrawTop(true);
	printTextCentered("WildEdit - " + Lang::get("TEMP_ITEM"), 0, 0, true, true);
	printTextCentered(Lang::get("ITEM_NAME") + ItemUtils::getName(this->TempItem), 0, 50, true, true);
	printTextCentered(Lang::get("ITEM_ID") + std::to_string(this->TempItem), 0, 80, true, true);

	Gui::DrawBottom(true);
	for (int i = 0; i < 3; i++) {
		drawRectangle(TempPos[i].x, TempPos[i].y, TempPos[i].w, TempPos[i].h, GRAY, false, true);
	}

	printTextCentered(Lang::get("ITEM_MANUALLY"), 0, 40, false, true);
	printTextCentered(Lang::get("ITEM_SELECTION"), 0, 90, false, true);
}

/* Convert the positions to selection. */
void TownMapEditor::convertToSelection() {
	this->MapSelection = (this->currentAcre * 256) + (this->currentPosY * 16) + this->currentPosX;
}

/* Convert the selections to positions. */
void TownMapEditor::convertToPosition() {
	if (this->currentAcre < 4) {
		this->PositionX = (this->currentAcre * 16) + this->currentPosX;

	} else if (this->currentAcre > 3 && this->currentAcre < 8) {
		this->PositionX = (((this->currentAcre - 4) * 16)) + this->currentPosX;

	} else if (this->currentAcre > 7 && this->currentAcre < 12) {
		this->PositionX = (((this->currentAcre - 8) * 16)) + this->currentPosX;

	} else if (this->currentAcre > 11 && this->currentAcre < 16) {
		this->PositionX = (((this->currentAcre - 12) * 16)) + this->currentPosX;
	}

	int acre = 0;
	if (this->currentAcre < 4) {
		acre = 0;

	} else if (this->currentAcre > 3 && this->currentAcre < 8) {
		acre = 1;

	} else if (this->currentAcre > 7 && this->currentAcre < 12) {
		acre = 2;

	} else if (this->currentAcre > 11 && this->currentAcre < 16) {
		acre = 3;
	}

	this->PositionY = (acre * 16) + this->currentPosY;
}

/* The selection to an acre. */
int TownMapEditor::SelectionToAcre(int i) const {
	switch(i) {
		case 0:
			return 7;

		case 1:
			return 8;

		case 2:
			return 9;

		case 3:
			return 10;

		case 4:
			return 13;

		case 5:
			return 14;

		case 6:
			return 15;

		case 7:
			return 16;

		case 8:
			return 19;

		case 9:
			return 20;

		case 10:
			return 21;

		case 11:
			return 22;

		case 12:
			return 25;

		case 13:
			return 26;

		case 14:
			return 27;

		case 15:
			return 28;
	}

	return 7; // Should Never Happen.
}

/* Inject the temp item to a map slot. */
void TownMapEditor::injectTo(int MapSlot) {
	if (ItemUtils::getName(this->TempItem) != "???") {
		this->MapItems[this->MapSelection]->id(this->TempItem);
		updateBottomGrid();
	}
}

/* Main Screen logic. */
void TownMapEditor::MainLogic(u16 hDown, touchPosition touch) {
	u16 held = keysDownRepeat();

	if (hDown & KEY_B) {
		Gui::screenBack();
		Gui::DrawScreen();
		Gui::showPointer(true);
		updatePointer = true;
		return;
	}

	/* Pressing X for now leads to the Temp Item Screen. */
	if (hDown & KEY_X) {
		for (int i = 0; i < 16; i++) {
			setSpriteVisibility(this->topAcres[i], true, false);
		}

		this->Mode = 1;
		Gui::DrawScreen();
		Gui::showPointer(true);
		updatePointer = true;
	}

	if (hDown & KEY_A) {
		injectTo(this->MapSelection);
		this->updateTopGrid();
	}

	/* Set the current Map Item to the temp item. */
	if (hDown & KEY_Y) {
		this->TempItem = this->MapItems[this->MapSelection]->id();
	}

	if (held & KEY_RIGHT) {
		if (this->currentPosX == 15 && this->currentAcre < 15) {
			this->currentAcre++;
			this->currentPosX = 0;
			this->convertToSelection();
			this->updateAcreImage();
			this->convertToPosition();
			this->updateBottomGrid();
			this->updateTopGrid();

		} else if (this->currentPosX < 15) {
			this->currentPosX++;
			this->convertToSelection();
			this->convertToPosition();
			this->updateBottomGrid();
			this->updateTopGrid();
		}
	}

	if (held & KEY_LEFT) {
		if (this->currentPosX == 0 && this->currentAcre > 0) {
			this->currentAcre--;
			this->currentPosX = 15;
			this->convertToSelection();
			this->updateAcreImage();
			this->convertToPosition();
			this->updateBottomGrid();
			this->updateTopGrid();

		} else if (this->currentPosX > 0) {
			this->currentPosX--;
			this->convertToSelection();
			this->convertToPosition();
			this->updateBottomGrid();
			this->updateTopGrid();
		}
	}

	if (held & KEY_DOWN) {
		if (this->currentPosY == 15 && this->currentAcre < 12) {
			this->currentAcre += 4;
			this->currentPosY = 0;
			this->convertToSelection();
			this->updateAcreImage();
			this->convertToPosition();
			this->updateBottomGrid();
			this->updateTopGrid();

		} else if (this->currentPosY < 15) {
			this->currentPosY++;
			this->convertToSelection();
			this->convertToPosition();
			this->updateBottomGrid();
			this->updateTopGrid();
		}
	}

	if (held & KEY_UP) {
		if (this->currentPosY == 0 && this->currentAcre > 3) {
			this->currentAcre -= 4;
			this->currentPosY = 15;
			this->convertToSelection();
			this->updateAcreImage();
			this->convertToPosition();
			this->updateBottomGrid();
			this->updateTopGrid();

		} else if (this->currentPosY > 0) {
			this->currentPosY--;
			this->convertToSelection();
			this->convertToPosition();
			this->updateBottomGrid();
			this->updateTopGrid();
		}
	}
}

/* Temp Item logic. */
void TownMapEditor::TempLogic(u16 hDown, touchPosition touch) {
	if (updatePointer) Gui::pointerUpdate(TempPos[this->selection].x+60, TempPos[this->selection].y+12);

	/* Hide the selector, display top acres and go to main screen. */
	if (hDown & KEY_B) {
		for (int i = 0; i < 16; i++) {
			setSpriteVisibility(this->topAcres[i], true, true);
		}

		this->Mode = 0;
		Gui::DrawScreen();
		Gui::showPointer(false);
		updateOam();
	}

	if (hDown & KEY_A) {
		if (this->selection == 0) {
			int ID = Input::getInt(Lang::get("ENTER_DECIMAL_ID"), 99999);

			if (ID != -1) {
				this->TempItem = ID;
				Gui::DrawScreen();
			}

		} else if (this->selection == 1) {
			Gui::clearScreen(true, true);
			this->TempItem = Overlays::SelectItem(this->TempItem, Lang::get("SELECT_ITEM"));
			Gui::DrawScreen();
		}
	}

	if (hDown & KEY_DOWN) {
		if (this->selection < 2) {
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
}