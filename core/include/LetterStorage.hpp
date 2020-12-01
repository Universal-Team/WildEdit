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

#ifndef _WILDEDIT_CORE_LETTER_STORAGE_HPP
#define _WILDEDIT_CORE_LETTER_STORAGE_HPP

#include "letter.hpp"
#include "types.hpp"

class LetterStorage {
protected:
	std::shared_ptr<u8[]> StorageData;
	u32 Offset;
	WWRegion Region;
public:
	LetterStorage(std::shared_ptr<u8[]> storageData, u32 offset, WWRegion region) :
		StorageData(storageData), Offset(offset), Region(region) { };

	/* Player Letters. */
	std::unique_ptr<Letter> Player1(uint8_t Slot) const;
	std::unique_ptr<Letter> Player2(uint8_t Slot) const;
	std::unique_ptr<Letter> Player3(uint8_t Slot) const;
	std::unique_ptr<Letter> Player4(uint8_t Slot) const;

	/* Checksum things. */
	u16 CalculateChecksum();
	bool ChecksumValid();
	void FixChecksum();
private:
	/* Return amount of letters per player. */
	uint8_t LetterAmount() const {
		switch(this->Region) {
			case WWRegion::EUR:
			case WWRegion::USA:
			case WWRegion::JPN:
				return 75;

			case WWRegion::KOR:
				return 50;
		}

		return 0;
	};
};

#endif