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

#include "coreUtils.hpp"
#include "input.hpp"
#include "itemEditor.hpp"
#include "msg.hpp"
#include "overlay.hpp"
#include "playerEditor.hpp"
#include "stringUtils.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);

extern std::vector<std::string> g_hairStyle;
extern std::vector<std::string> g_hairColor;
extern std::vector<std::string> g_faceType;

std::vector<std::string> TanLevel = {
	"0",
	"1",
	"2",
	"3"
};

PlayerEditor::PlayerEditor(std::unique_ptr<Player> refPlayer) : player(std::move(refPlayer)) {
	for (int i = 0; i < 8; i++) this->allocatedPattern[i] = maxSpriteSub + i;
}

PlayerEditor::~PlayerEditor() { this->FreePattern(); };

void PlayerEditor::Draw(void) const {
	switch(this->Mode) {
		case 0:
			this->DrawSubMenu();
			break;

		case 1:
			this->DrawPlayerScreen();
			break;

		case 2:
			this->DrawAppearance();
			break;

		case 3:
			this->DrawPattern();
			break;
	}
}

void PlayerEditor::Logic(u16 hDown, touchPosition touch) {
	switch(this->Mode) {
		case 0:
			this->SubMenuLogic(hDown, touch);
			break;

		case 1:
			this->PlayerLogic(hDown, touch);
			break;

		case 2:
			this->AppearanceLogic(hDown, touch);
			break;

		case 3:
			this->PatternLogic(hDown, touch);
			break;
	}
}

void PlayerEditor::DrawSubMenu(void) const {
	Gui::DrawTop(true);
	printTextCentered("WildEdit - " + Lang::get("PLAYER_SUBMENU"), 0, 0, true, true);

	Gui::DrawBottom(true);
	for (int i = 0; i < 6; i++) {
		drawRectangle(playerButtons[i].x, playerButtons[i].y, playerButtons[i].w, playerButtons[i].h, GRAY, false, true);
	}

	printTextCentered(Lang::get("PLAYER"), -64, 40, false, true);
	printTextCentered(Lang::get("APPEARANCE"), -64, 90, false, true);
	printTextCentered(Lang::get("PATTERN"), -64, 140, false, true);
	printTextCentered(Lang::get("ITEMS"), 64, 40, false, true);
}

void PlayerEditor::DrawPlayerScreen(void) const {
	Gui::DrawTop(true);
	printTextCentered("WildEdit - " + Lang::get("PLAYER_EDITOR"), 0, 0, true, true);

	printTextCentered(Lang::get("PLAYER_WALLET") + ": " + std::to_string(this->player->wallet()), 0, 28, true, true);
	printTextCentered(Lang::get("PLAYER_BANK") + ": " + std::to_string(this->player->bank()), 0, 53, true, true);

	Gui::DrawBottom(true);
	for (int i = 0; i < 6; i++) {
		drawRectangle(playerButtons[i].x, playerButtons[i].y, playerButtons[i].w, playerButtons[i].h, GRAY, false, true);
	}

	printTextCentered(Lang::get("PLAYER_WALLET"), -64, 40, false, true);
	printTextCentered(Lang::get("PLAYER_BANK"), -64, 90, false, true);
}

void PlayerEditor::DrawAppearance(void) const {
	Gui::DrawTop(true);
	printTextCentered("WildEdit - " + Lang::get("APPEARANCE"), 0, 0, true, true);

	printTextCentered(Lang::get("PLAYER_NAME") + ": " + StringUtils::UTF16toUTF8(this->player->name()), 0, 28, true, true);
	printTextCentered(Lang::get("PLAYER_GENDER") + ": " + std::to_string(this->player->gender()), 0, 53, true, true);
	printTextCentered(Lang::get("PLAYER_TAN_VALUE") + ": " + std::to_string(this->player->tan()), 0, 78, true, true);
	printTextCentered(Lang::get("PLAYER_FACE") + ": " + std::to_string(this->player->face()), 0, 103, true, true);
	printTextCentered(Lang::get("PLAYER_HAIRSTYLE") + ": " + std::to_string(this->player->hairstyle()), 0, 128, true, true);
	printTextCentered(Lang::get("PLAYER_HAIRCOLOR") + ": " + std::to_string(this->player->haircolor()), 0, 153, true, true);

	Gui::DrawBottom(true);
	for (int i = 0; i < 6; i++) {
		drawRectangle(playerButtons[i].x, playerButtons[i].y, playerButtons[i].w, playerButtons[i].h, GRAY, false, true);
	}

	printTextCentered(Lang::get("PLAYER_NAME"), -64, 40, false, true);
	printTextCentered(Lang::get("PLAYER_GENDER"), -64, 90, false, true);
	printTextCentered(Lang::get("PLAYER_TAN_VALUE"), -64, 140, false, true);
	printTextCentered(Lang::get("PLAYER_FACE"), 64, 40, false, true);
	printTextCentered(Lang::get("PLAYER_HAIRSTYLE"), 64, 90, false, true);
	printTextCentered(Lang::get("PLAYER_HAIRCOLOR"), 64, 140, false, true);
}

void PlayerEditor::DrawPattern(void) const {
	Gui::DrawTop(true);
	printTextCentered("WildEdit - " + Lang::get("PATTERN"), 0, 0, true, true);

	printTextCentered(Lang::get("PATTERN_NAME") + StringUtils::UTF16toUTF8(this->ptrn[this->selection]->name()), 0, 28, true, true);
	printTextCentered(Lang::get("PATTERN_CREATOR_NAME") + StringUtils::UTF16toUTF8(this->ptrn[this->selection]->creatorname()), 0, 53, true, true);
	printTextCentered(Lang::get("PATTERN_CREATOR_ID") + std::to_string(this->ptrn[this->selection]->creatorid()), 0, 78, true, true);
	printTextCentered(Lang::get("PATTERN_ORIGIN_TOWN_NAME") + StringUtils::UTF16toUTF8(this->ptrn[this->selection]->origtownname()), 0, 103, true, true);
	printTextCentered(Lang::get("PATTERN_ORIGIN_TOWN_ID") + std::to_string(this->ptrn[this->selection]->origtownid()), 0, 128, true, true);

	if (this->ptrn[this->selection]->creatorGender()) {
		printTextCentered(Lang::get("PATTERN_CREATOR_GENDER") + Lang::get("FEMALE"), 0, 153, true, true);

	} else {
		printTextCentered(Lang::get("PATTERN_CREATOR_GENDER") + Lang::get("MALE"), 0, 153, true, true);
	}

	Gui::DrawBottom(true);
}

void PlayerEditor::SubMenuLogic(u16 hDown, touchPosition touch) {
	if (updatePointer) Gui::pointerUpdate(playerButtons[this->selection].x+60, playerButtons[this->selection].y+12);

	if (hDown & KEY_B) {
		Gui::showPointer(false);
		updateOam();
		Gui::screenBack();
		Gui::DrawScreen();
		return;
	}

	if (hDown & KEY_UP) {
		if (this->selection > 0) {
			this->selection--;
			updatePointer = true;
		}
	}

	if (hDown & KEY_DOWN) {
		if (this->selection < 5) {
			this->selection++;
			updatePointer = true;
		}
	}

	if (hDown & KEY_RIGHT) {
		if (this->selection < 3) {
			this->selection += 3;
			updatePointer = true;
		}
	}

	if (hDown & KEY_LEFT) {
		if (this->selection < 6 && this->selection > 2) {
			this->selection -= 3;
			updatePointer = true;
		}
	}

	if (hDown & KEY_A) {
		switch(this->selection) {
			case 0:
				this->selection = 0;
				this->Mode = 1;
				Gui::DrawScreen();
				updatePointer = true;
				break;

			case 1:
				this->selection = 0;
				this->Mode = 2;
				Gui::DrawScreen();
				updatePointer = true;
				break;

			case 2:
				this->DecodePattern();

				this->selection = 0;
				this->Mode = 3;
				Gui::DrawScreen();
				updatePointer = true;
				break;

			case 3:
				Gui::setScreen(std::make_unique<ItemEditor>(this->player));
				Gui::DrawScreen();
				updatePointer = true;
				break;
		}
	}
}

void PlayerEditor::PlayerLogic(u16 hDown, touchPosition touch) {
	if (updatePointer) Gui::pointerUpdate(playerButtons[this->selection].x+60, playerButtons[this->selection].y+12);

	if (hDown & KEY_B) {
		this->selection = 0;
		this->Mode = 0;
		Gui::DrawScreen();
		updatePointer = true;
	}

	if (hDown & KEY_UP) {
		if (this->selection > 0) {
			this->selection--;
			updatePointer = true;
		}
	}

	if (hDown & KEY_DOWN) {
		if (this->selection < 5) {
			this->selection++;
			updatePointer = true;
		}
	}

	if (hDown & KEY_RIGHT) {
		if (this->selection < 3) {
			this->selection += 3;
			updatePointer = true;
		}
	}

	if (hDown & KEY_LEFT) {
		if (this->selection < 6 && this->selection > 2) {
			this->selection -= 3;
			updatePointer = true;
		}
	}

	if (hDown & KEY_A) {
		switch(this->selection) {
			case 0:
				/* Wallet. */
				this->player->wallet(Input::getInt(Lang::get("ENTER_WALLET_AMOUNT"), 99999, this->player->wallet(), true, true));
				Gui::DrawScreen(); // Redraw to update.
				break;

			case 1:
				/* Bank. */
				this->player->bank(Input::getInt(Lang::get("ENTER_BANK_AMOUNT"), 999999999, this->player->bank(), true, true));
				Gui::DrawScreen(); // Redraw to update.
				break;
		}
	}
}

void PlayerEditor::AppearanceLogic(u16 hDown, touchPosition touch) {
	if (updatePointer) Gui::pointerUpdate(playerButtons[this->selection].x+60, playerButtons[this->selection].y+12);

	if (hDown & KEY_B) {
		this->selection = 0;
		this->Mode = 0;
		Gui::DrawScreen();
		updatePointer = true;
	}

	if (hDown & KEY_UP) {
		if (this->selection > 0) {
			this->selection--;
			updatePointer = true;
		}
	}

	if (hDown & KEY_DOWN) {
		if (this->selection < 5) {
			this->selection++;
			updatePointer = true;
		}
	}

	if (hDown & KEY_RIGHT) {
		if (this->selection < 3) {
			this->selection += 3;
			updatePointer = true;
		}
	}

	if (hDown & KEY_LEFT) {
		if (this->selection < 6 && this->selection > 2) {
			this->selection -= 3;
			updatePointer = true;
		}
	}

	if (hDown & KEY_A) {
		u8 length = 0;
		const std::vector<std::string> gender = { Lang::get("MALE"), Lang::get("FEMALE") };

		switch(this->selection) {
			case 0:
				/* We need to check for the Name length here. */
				switch(save->getRegion()) {
					case WWRegion::EUR:
					case WWRegion::USA:
						length = 7;
						break;

					case WWRegion::JPN:
					case WWRegion::KOR:
						length = 6;
						break;
				}

				/* Name. */
				this->player->name(StringUtils::UTF8toUTF16(Input::getLine(Lang::get("ENTER_PLAYER_NAME"), length, StringUtils::UTF16toUTF8(this->player->name()), true)));
				Gui::DrawScreen(); // Redraw to update.
				break;

			case 1:
				/* Gender. */
				this->player->gender((u8)Overlays::SelectList(gender, this->player->gender(), Lang::get("SELECT_GENDER"), true, true));
				Gui::DrawScreen(); // Redraw to update.
				break;

			case 2:
				/* Tan. */
				this->player->tan((u8)Overlays::SelectList(TanLevel, this->player->tan(), Lang::get("SELECT_TAN"), true, true));
				Gui::DrawScreen(); // Redraw to update.
				break;

			case 3:
				/* Facetype. */
				this->player->face((u8)Overlays::SelectList(g_faceType, this->player->face(), Lang::get("SELECT_FACETYPE"), true, true));
				Gui::DrawScreen(); // Redraw to update.
				break;

			case 4:
				/* Hairstyle. */
				this->player->hairstyle((u8)Overlays::SelectList(g_hairStyle, this->player->hairstyle(), Lang::get("SELECT_HAIRSTYLE"), true, true));
				Gui::DrawScreen(); // Redraw to update.
				break;

			case 5:
				/* Haircolor. */
				this->player->haircolor((u8)Overlays::SelectList(g_hairColor, this->player->haircolor(), Lang::get("SELECT_HAIRCOLOR"), true, true));
				Gui::DrawScreen(); // Redraw to update.
				break;
		}
	}
}

void PlayerEditor::PatternLogic(u16 hDown, touchPosition touch) {
	if (updatePointer) Gui::pointerUpdate(patternPos[this->selection].x+10, patternPos[this->selection].y+10);

	if (hDown & KEY_B) {
		for (int i = 0; i < 8; i++) { setSpriteVisibility(this->allocatedPattern[i], false, false); }

		this->selection = 0;
		this->Mode = 0;
		Gui::DrawScreen();
		updatePointer = true;
	}

	if (hDown & KEY_RIGHT) {
		if (this->selection < 7) {
			this->selection++;
			Gui::DrawScreen();
			updatePointer = true;
		}
	}

	if (hDown & KEY_LEFT) {
		if (this->selection > 0) {
			this->selection--;
			Gui::DrawScreen();
			updatePointer = true;
		}
	}
}

void PlayerEditor::DecodePattern() {
	for (int i = 0; i < 8; i++) {
		if (!this->accessPattern) {
			this->allocatedPattern[i] = initSprite(false, SpriteSize_32x32, this->allocatedPattern[i]);
			prepareSprite(this->allocatedPattern[i], false, patternPos[i].x, patternPos[i].y, 0);
		}

		this->ptrn[i] = this->player->pattern(i);
		this->ptrnImg[i] = this->ptrn[i]->image();
		fillSpriteImage(this->allocatedPattern[i], false, 32, 0, 0, CoreUtils::patternimage(this->ptrnImg[i], 0x0));
		setSpriteVisibility(this->allocatedPattern[i], false, true);
	}

	this->accessPattern = true;
}

void PlayerEditor::FreePattern() {
	if (this->accessPattern) {
		for (int i = 0; i < 8; i++) {
			if (spritesSub[this->allocatedPattern[i]].gfx) oamFreeGfx(&oamSub, spritesSub[this->allocatedPattern[i]].gfx);
		}
	}
}