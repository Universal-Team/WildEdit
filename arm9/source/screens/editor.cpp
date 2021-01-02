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

#include "cardSaves.hpp"
#include "coreUtils.hpp"
#include "editor.hpp"
#include "fileBrowse.hpp"
#include "gui.hpp"
#include "houseEditor.hpp"
#include "lang.hpp"
#include "msg.hpp"
#include "overlay.hpp"
#include "playerSelector.hpp"
#include "Sav.hpp"
#include "townEditor.hpp"

bool changes = false;
extern bool loadedFromCart;
extern bool exiting;

extern bool touching(touchPosition touch, Structs::ButtonPos button);

Editor::Editor() { };

void Editor::SaveInitialize() {
	Gui::showPointer(false);
	Gui::pointerUpdate(0, 0);

	this->saveName = Overlays::browseForSave();

	if (this->saveName != "") {
		if (!CoreUtils::loadSave(this->saveName)) {
			Msg::DisplayWarnMsg(Lang::get("INVALID_SAVEFILE"));

		} else {
			loadState = SaveState::Loaded;

			/* Clear Both Screens. */
			Gui::clearScreen(false, true);
			Gui::clearScreen(true, true);
			Gui::DrawScreen();

			/* Display Save icon. */
			setSpriteVisibility(Gui::saveID, false, true);
			setSpritePosition(Gui::saveID, false, 225, 172);
			Gui::showPointer(true);
			updateOam();
		}

	} else {
		exiting = true;
	}
}

void Editor::Saving() {
	CoreUtils::saveChanges();
	hasSaved = true;
}

void Editor::Draw(void) const {
	if (this->loadState == SaveState::Loaded) {
		Gui::DrawTop(true);
		printTextCentered("WildEdit - " + Lang::get("EDITOR"), 0, 0, true, true);

		/* Region test. */
		if (save) {
			switch(save->getRegion()) {
				case WWRegion::EUR:
					printTextCentered("Europe", 0, 60, true, true);
					break;

				case WWRegion::USA:
					printTextCentered("USA", 0, 60, true, true);
					break;

				case WWRegion::JPN:
					printTextCentered("Japanese", 0, 60, true, true);
					break;

				case WWRegion::KOR:
					printTextCentered("Korean", 0, 60, true, true);
					break;
			}
		}

		Gui::DrawBottom(true);

		for (int i = 0; i < 3; i++) {
			drawRectangle(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, GRAY, false, true);
		}

		printTextCentered(Lang::get("PLAYER"), 0, 40, false, true);
		printTextCentered(Lang::get("VILLAGER"), 0, 90, false, true);
		printTextCentered(Lang::get("TOWN"), 0, 140, false, true);
	}
}

void Editor::Logic(u16 hDown, touchPosition touch) {
	/* Only do Logic, if Save is loaded. */
	if (this->loadState == SaveState::Loaded) {
		if (updatePointer) Gui::pointerUpdate(mainButtons[this->Selection].x + 60, mainButtons[this->Selection].y + 12);

		if (hDown & KEY_B) {
			/* Hide save icon. */
			setSpriteVisibility(Gui::saveID, false, false);
			Gui::showPointer(false);
			updateOam();
			this->loadState = SaveState::Unloaded;
		}

		if (hDown & KEY_DOWN) {
			if (this->Selection < 2) {
				this->Selection++;
				updatePointer = true;
			}
		}

		if (hDown & KEY_START) this->Saving();

		if (hDown & KEY_UP) {
			if (this->Selection > 0) {
				this->Selection--;
				updatePointer = true;
			}
		}

		if (hDown & KEY_A) {
			switch(this->Selection) {
				case 0:
					/* Player. */
					Gui::setScreen(std::make_unique<PlayerSelector>());
					setSpriteVisibility(Gui::saveID, false, false);
					Gui::DrawScreen();
					Gui::showPointer(false);
					updateOam();
					break;

				case 1:
					/* Villager. */
					break;

				case 2:
					/* Town. */
					setSpriteVisibility(Gui::saveID, false, false);
					Gui::setScreen(std::make_unique<TownEditor>(save->town()));
					Gui::DrawScreen();
					updatePointer = true;
					updateOam();
					break;
			}
		}

		if (hDown & KEY_SELECT) {
			Gui::setScreen(std::make_unique<HouseEditor>());
			setSpriteVisibility(Gui::saveID, false, false);
			Gui::DrawScreen();
			Gui::showPointer(false);
			updateOam();
		}

	} else {
		this->SaveInitialize();
	}
}