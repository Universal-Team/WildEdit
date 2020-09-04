/*
*   This file is part of WildEdit-Core
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

#ifndef _WILDEDIT_CORE_ITEMUTILS_HPP
#define _WILDEDIT_CORE_ITEMUTILS_HPP

#include "types.hpp"
#include <string>

/*
	We should sort that out for AC:WW only Category Items for WildEdit here.
	Type of the Item.
*/

enum class ItemType {
	Empty,
	Furniture,
	Gyroid,
	Diary,
	Clothes,
	Song,
	Paper,
	Trash,
	Shell,
	Fruit,
	Turnip,
	Catchable,
	QuestItem,
	Item,
	RaffleTicket,
	WallpaperCarpet,
	Fossil,
	Tool,
	Tree,
	Weed,
	Flower,
	Rock,
	MoneyRock,
	Signboard,
	Money,
	HouseObject,
	Building,
	ParchedFlower,
	WateredFlower,
	Pattern,
	WiltedFlower,
	Occupied,
	Invalid
};

namespace ItemUtils {
	std::string getName(u16 ID); // Get an Item's name.
}

#endif