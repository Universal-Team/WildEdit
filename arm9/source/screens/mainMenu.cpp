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

#include "mainMenu.hpp"

extern bool exiting;

void MainMenu::Draw(void) const {
	Gui::DrawTop(true);
	printTextCentered("WildEdit - MainMenu", 0, 1, true, true);
	Gui::DrawBottom(true);
}

void MainMenu::Logic(u16 hDown, touchPosition touch) {
	if (hDown & KEY_START) {
		exiting = true;
	}

	if (hDown & KEY_RIGHT) {
		if (this->selection < 1) this->selection++;
	}

	if (hDown & KEY_LEFT) {
		if (this->selection > 0) this->selection--;
	}
}