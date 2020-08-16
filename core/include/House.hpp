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

#ifndef _WILDEDIT_CORE_HOUSE_HPP
#define _WILDEDIT_CORE_HOUSE_HPP

#include "types.hpp"
#include <memory>
#include <vector>

class Room {
protected:
	u32 Offset;
	std::shared_ptr<u8[]> data;
public:
	Room(std::shared_ptr<u8[]> roomData, u32 offset) : Offset(offset), data(roomData) { }
	Room(const Room& room) = delete;
	Room& operator=(const Room& room) = delete;
private:
	u8* roomPointer() const {
		return this->data.get() + this->Offset;
	}
};

class House {
protected:
	u32 Offset;
	std::shared_ptr<u8[]> data;
public:
	House(std::shared_ptr<u8[]> houseData, u32 offset) : Offset(offset), data(houseData) { }
	House(const House& house) = delete;
	House& operator=(const House& house) = delete;

	std::unique_ptr<Room> room(int room);
private:
	u8* housePointer() const {
		return this->data.get() + this->Offset;
	}
};

#endif