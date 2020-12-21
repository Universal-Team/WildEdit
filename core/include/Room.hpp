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

#ifndef _WILDEDIT_CORE_ROOM_HPP
#define _WILDEDIT_CORE_ROOM_HPP

#include "Item.hpp"
#include "types.hpp"
#include <memory>

class Room {
protected:
	std::shared_ptr<u8[]> RoomData;
	u32 Offset;
public:
	Room(std::shared_ptr<u8[]> roomData, u32 offset) :
		RoomData(roomData), Offset(offset) { };
	Room(const Room& room) = delete;
	Room& operator=(const Room& room) = delete;

	std::unique_ptr<Item> Furniture(bool topLayer, u8 slot) const;
	std::unique_ptr<Item> Carpet() const;
	std::unique_ptr<Item> Wallpaper() const;
	std::unique_ptr<Item> Song() const;
private:
	u8 *roomPointer() const { return this->RoomData.get() + this->Offset; };
};

#endif