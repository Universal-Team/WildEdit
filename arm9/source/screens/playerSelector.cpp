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

#include "playerEditor.hpp"
#include "playerSelector.hpp"
#include "Sav.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);

PlayerSelector::PlayerSelector() {
	for (int player = 0; player < 4; player++) {
		if (save->player(player)->exist()) this->maxPlayer = player;
	}
}


void PlayerSelector::DrawPlayerBoxes(void) const {
	for (int i = 0; i < 4; i++) {
		if (i == this->selectedPlayer) drawRectangle(pos[i].x, pos[i].y, pos[i].w, pos[i].h, LIGHT_GRAY, true, true);
		else drawRectangle(pos[i].x, pos[i].y, pos[i].w, pos[i].h, GRAY, true, true);
	}
}

void PlayerSelector::Draw(void) const {
	Gui::DrawTop(true);
	printTextCentered("WildEdit - " + Lang::get("PLAYER_SELECTION"), 0, 0, true, true);
	DrawPlayerBoxes();
	printTextCentered(Lang::get("CURRENT_PLAYER") + std::to_string(this->selectedPlayer+1), 0, 172, true, true);
	Gui::DrawBottom(true);
}

void PlayerSelector::Logic(u16 hDown, touchPosition touch) {
	if (hDown & KEY_RIGHT) {
		this->selectedPlayer++;
		if (this->selectedPlayer > this->maxPlayer) this->selectedPlayer = 0;
		Gui::DrawScreen();
	}
	
	if (hDown & KEY_LEFT) {
		this->selectedPlayer--;
		if (this->selectedPlayer < 0) this->selectedPlayer = this->maxPlayer;
		Gui::DrawScreen();
	}

	if (hDown & KEY_A) {
		if (save->player(this->selectedPlayer)->exist()) {
			Gui::setScreen(std::make_unique<PlayerEditor>(save->player(this->selectedPlayer)));
			Gui::DrawScreen();
			Gui::showPointer(true);
		}
	}

	if (hDown & KEY_B) {
		Gui::screenBack();
		
		/* Display Save icon. */
		setSpriteVisibility(Gui::saveID, false, true);
		Gui::DrawScreen();
		Gui::showPointer(true);
		return;
	}
}