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

#ifndef _WILDEDIT_GRAPHIC_MANAGEMENT_HPP
#define _WILDEDIT_GRAPHIC_MANAGEMENT_HPP

#include <nds.h>
#include <stdio.h>
#include <string>

namespace GraphicManagement {
	void DrawVillager(u8 villagerID, int x, int y, bool top = true);
	void DrawAcre(u8 AcreID, int x, int y, float ScaleX = 1, float ScaleY = 1, bool top = true, bool Layer = true);
	void DrawFace(u8 facetype, int x, int y, bool top);
};

#endif