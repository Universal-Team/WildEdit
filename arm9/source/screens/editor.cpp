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

#include "cardSaves.hpp"
#include "coreUtils.hpp"
#include "editor.hpp"
#include "fileBrowse.hpp"
#include "gui.hpp"
#include "lang.hpp"
#include "overlay.hpp"
#include "msg.hpp"
#include "Sav.hpp"

bool changes = false;
extern bool loadedFromCart;
extern bool exiting;

// Japanese | PAL.
const std::vector<std::string> titleNames = {
	"おいでよ どうぶつの森",
	"Wild World",
	"とびだせ どうぶつの森",
	"New Leaf",
	"とびだせ どうぶつの森 amiibo+",
	"Welcome amiibo",
};

extern bool touching(touchPosition touch, Structs::ButtonPos button);

Editor::Editor() { }

void Editor::SaveInitialize() {
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
	if (loadState == SaveState::Loaded) {
		Gui::DrawTop(true);
		printTextCentered("WildEdit - " + Lang::get("EDITOR"), 0, 0, true, true);

		/* Region test. */
		if (save) {
			if (save->getRegion() == WWRegion::EUR_REV1) {
				printTextCentered("Europe | USA", 0, 60, true, true);
			} else if (save->getRegion() == WWRegion::JPN_REV0) {
				printTextCentered("Japanese", 0, 60, true, true);
			} else if (save->getRegion() == WWRegion::KOR_REV1) {
				printTextCentered("Korean", 0, 60, true, true);
			} else if (save->getRegion() == WWRegion::UNKNOWN) {
				printTextCentered("Unknown", 0, 60, true, true);
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
	if (loadState == SaveState::Loaded) {
		if (hDown & KEY_B) {
			/* Hide save icon. */
			setSpriteVisibility(Gui::saveID, false, false);
			updateOam();
			this->loadState = SaveState::Unloaded;
		}
		
		if (hDown & KEY_DOWN) {
			if (this->Selection < 2) this->Selection++;
		}
		
		if (hDown & KEY_UP) {
			if (this->Selection > 0) this->Selection--;
		}

	} else {
		this->SaveInitialize();
	}
}