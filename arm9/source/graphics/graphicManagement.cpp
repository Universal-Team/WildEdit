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

#include "graphicManagement.hpp"
#include "gui.hpp"

#include <nds.h>

/* Draw an Acre image. */
void GraphicManagement::DrawAcre(u8 AcreID, int x, int y, float ScaleX, float ScaleY, bool top, bool Layer) {
	const Image AcreData = loadImage("/graphics/acres/" + std::to_string(AcreID) + ".gfx"); // Load Image.
	drawImageScaled(x, y, ScaleX, ScaleY, AcreData, top, Layer, 0x20); // Draw Image.
}

/* Draw a villager image. */
void GraphicManagement::DrawVillager(u8 villagerID, int x, int y, bool top) {
	if (villagerID > 149) villagerID = 150; // 150 -> EMPTY.

	const Image villagerData = loadImage("/graphics/villagers/" + std::to_string(villagerID) + ".gfx"); // Load image.
	drawImage(x, y, villagerData, top, true, 0x20); // Draw image.
}

/* Draw a player face. */
void GraphicManagement::DrawFace(u8 facetype, int x, int y, bool top) {
	const Image faceData = loadImage("/graphics/faces/" + std::to_string(facetype) + ".gfx"); // Load image.
	drawImage(x, y, faceData, top, true, 0x20); // Draw image.
}