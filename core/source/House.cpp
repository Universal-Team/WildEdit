/*
*   This file is part of WildEdit-Core
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

#include "House.hpp"
#include "saveUtils.hpp"

constexpr uint32_t HouseSizeDebts[7] = { 19800, 120000, 298000, 598000, 728000, 848000, 948000 };

/*
	Return a room.

	uint8_t room: The room.
*/
std::unique_ptr<Room> House::room(uint8_t room) const {
	if (room > 4) return nullptr; // 0 - 4 allowed.

	return std::make_unique<Room>(this->HouseData, this->Offset + (room * 0x450));
}

/*
	House Debts.
*/
u32 House::debts() const { return SaveUtils::Read<u32>(this->housePointer(), 0x1590); };
void House::debts(u32 v) { SaveUtils::Write<u32>(this->housePointer(), 0x1590, v); };

/*
	House upgrade size.
*/
u8 House::size() const { return this->housePointer()[0x15A0] & 7; };
void House::size(u8 v) {
	if (v > 6) return;

	this->housePointer()[0x15A0] = ((this->size() & ~7) | (v & 7));
	this->debts(HouseSizeDebts[v]); // Should we set the House size debts after it, or not?
};

/* Unlock House Songs. */
void House::unlockSongs() {
	constexpr uint8_t SongList[9] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F };

	for (uint8_t i = 0; i < 9; i++) {
		this->housePointer()[0x1594 + i] = SongList[i];
	}
}