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

#include "Room.hpp"

/*
	Returns a Furniture of a room.

	bool topLayer: If on a furniture or not (AKA Layer 2).
	u8 slot: Item slot.
*/
std::unique_ptr<Item> Room::Furniture(bool topLayer, u8 slot) const {
	return std::make_unique<Item>(this->RoomData, this->Offset + (topLayer ? 0x200 : 0) + (slot * 2));
};

/*
	Return the Room's Carpet.
*/
std::unique_ptr<Item> Room::Carpet() const { return std::make_unique<Item>(this->RoomData, this->Offset + 0x448); };

/*
	Return the Room's Wallpaper.
*/
std::unique_ptr<Item> Room::Wallpaper() const { return std::make_unique<Item>(this->RoomData, this->Offset + 0x44A); };

/*
	Return the Room's Song.
*/
std::unique_ptr<Item> Room::Song() const { return std::make_unique<Item>(this->RoomData, this->Offset + 0x44C); };