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

#include "acresEditor.hpp"
#include "graphicManagement.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);

AcresEditor::AcresEditor(std::unique_ptr<Town> &refTown) : town(refTown) {
	/* Get Acres. */
	for (int i = 0; i < 36; i++) {
		this->acres[i] = refTown->acre(i);

		this->saveAcres[i] = maxSpriteSub + i;
		this->saveAcres[i] = initSprite(false, SpriteSize_32x32, this->saveAcres[i]);
		prepareSprite(this->saveAcres[i], false, MapPos[i].x, MapPos[i].y, 0);
		setSpriteVisibility(this->saveAcres[i], false, true);
		fillSpriteImage(this->saveAcres[i], false, 32, 0, 0, loadImage("/graphics/acres/" + std::to_string(this->acres[i]->id()) + ".gfx"));
	}

	this->previewAcre = maxSpriteMain;
	this->previewAcre = initSprite(true, SpriteSize_32x32, this->previewAcre);

	oamSet(
		(&oamMain), // Main/Sub display.
		this->previewAcre, // Oam entry to set.
		90, 70, // Position.
		0, // Priority.
		spritesMain[this->previewAcre].paletteAlpha, // Alpha for bmp sprite.
		spritesMain[this->previewAcre].size,
		spritesMain[this->previewAcre].format,
		spritesMain[this->previewAcre].gfx,
		1,
		true, // Double.
		false, // Don't hide the sprite.
		false, false, // vflip, hflip.
		false // Apply mosaic.
	);

	oamRotateScale(&oamMain, 1, 0, 1 << 7, 1 << 7);
	fillSpriteImage(this->previewAcre, true, 32, 0, 0, loadImage("/graphics/acres/" + std::to_string(this->selectedAcre) + ".gfx"));
}

AcresEditor::~AcresEditor() {
	/* Free allocated acres. */
	for (int i = 0; i < 36; i++) {
		if (spritesSub[this->saveAcres[i]].gfx) {
			oamFreeGfx(&oamSub, spritesSub[this->saveAcres[i]].gfx);
			setSpriteVisibility(this->saveAcres[i], false, false);
		}
	}

	prepareSprite(this->previewAcre, true, 90, 70, 0);

	if (spritesMain[this->previewAcre].gfx) {
		oamFreeGfx(&oamMain, spritesMain[this->previewAcre].gfx);
		setSpriteVisibility(this->previewAcre, true, false);
	}

	updateOam();
}

void AcresEditor::reloadSaveAcre(int acre) {
	fillSpriteImage(this->saveAcres[acre], false, 32, 0, 0, loadImage("/graphics/acres/" + std::to_string(this->acres[acre]->id()) + ".gfx"));
	oamUpdate(&oamSub);
}

void AcresEditor::reloadTopAcre() {
	fillSpriteImage(this->previewAcre, true, 32, 0, 0, loadImage("/graphics/acres/" + std::to_string(this->selectedAcre) + ".gfx"));
	oamUpdate(&oamMain);
}


void AcresEditor::DrawTop(void) const {
	printTextCentered("WildEdit - " + Lang::get("ACRE_EDITOR"), 0, 0, true, true);
	printTextCentered(Lang::get("ACRE_ID") + std::to_string(this->selectedAcre), 0, 150, true, true);
}

void AcresEditor::Draw(void) const {
	Gui::DrawTop(true);
	this->DrawTop();
	Gui::DrawBottom(false);
}

void AcresEditor::updateTop() {
	Gui::clearScreen(true, true);
	DrawTop();
	this->reloadTopAcre();
}

void AcresEditor::Logic(u16 hDown, touchPosition touch) {
	u16 held = keysDownRepeat();
	if (updatePointer) Gui::pointerUpdate(MapPos[this->Selection].x+14, MapPos[this->Selection].y+14);

	if (hDown & KEY_B) {
		Gui::screenBack();
		setSpriteVisibility(Gui::saveID, false, true);
		Gui::DrawScreen();
		updatePointer = true;
		return;
	}

	/* Set current Acre. */
	if (hDown & KEY_A) {
		this->acres[this->Selection]->id(this->selectedAcre);
		this->reloadSaveAcre(this->Selection);
	}

	/* Display current Acre on Top. */
	if (hDown & KEY_Y) {
		this->selectedAcre = this->acres[this->Selection]->id();
		updateTop();
	}

	if (hDown & KEY_TOUCH) {
		for (int i = 0; i < 36; i++) {
			if (touching(touch, MapPos[i])) {
				this->Selection = i;
				updatePointer = true;
			}
		}
	}

	if (held & KEY_RIGHT) {
		if (this->Selection < 35) {
			this->Selection++;
			updatePointer = true;
		}
	}

	if (held & KEY_LEFT) {
		if (this->Selection > 0) {
			this->Selection--;
			updatePointer = true;
		}
	}

	if (held & KEY_UP) {
		if (this->Selection > 5) {
			this->Selection -= 6;
			updatePointer = true;
		}
	}

	if (held & KEY_DOWN) {
		if (this->Selection < 30) {
			this->Selection += 6;
			updatePointer = true;
		}
	}

	/* Top Screen Acre Selection. */
	if (held & KEY_L) {
		if (this->selectedAcre > 0) {
			this->selectedAcre--;
			this->updateTop();
		}
	}

	if (held & KEY_R) {
		if (this->selectedAcre < 130) {
			this->selectedAcre++;
			this->updateTop();
		}
	}
}