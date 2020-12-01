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

#include "LetterStorage.hpp"

/*
	Return a Letter from Player 1.

	u8 Slot: The Slot of the Storage.
*/
std::unique_ptr<Letter> LetterStorage::Player1(u8 Slot) const {
	if (Slot > this->LetterAmount() - 1) return nullptr;

	switch(this->Region) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Letter>(this->StorageData, this->Offset + (Slot * 0xF4), this->Region);

		case WWRegion::JPN:
			return std::make_unique<Letter>(this->StorageData, this->Offset + (Slot * 0x8C), this->Region);

		case WWRegion::KOR:
			return std::make_unique<Letter>(this->StorageData, this->Offset + (Slot * 0x100), this->Region);
	}

	return nullptr;
}

/*
	Return a Letter from Player 2.

	u8 Slot: The Slot of the Storage.
*/
std::unique_ptr<Letter> LetterStorage::Player2(u8 Slot) const {
	if (Slot > this->LetterAmount() - 1) return nullptr;

	switch(this->Region) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Letter>(this->StorageData, this->Offset + 0x477B + (Slot * 0xF4), this->Region);

		case WWRegion::JPN:
			return std::make_unique<Letter>(this->StorageData, this->Offset + 0x2903 + (Slot * 0x8C), this->Region);

		case WWRegion::KOR:
			return std::make_unique<Letter>(this->StorageData, this->Offset + 0x31FF +  (Slot * 0x100), this->Region);
	}

	return nullptr;
}

/*
	Return a Letter from Player 3.

	u8 Slot: The Slot of the Storage.
*/
std::unique_ptr<Letter> LetterStorage::Player3(u8 Slot) const {
	if (Slot > this->LetterAmount() - 1) return nullptr;

	switch(this->Region) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Letter>(this->StorageData, this->Offset + 0x8EF6 + (Slot * 0xF4), this->Region);

		case WWRegion::JPN:
			return std::make_unique<Letter>(this->StorageData, this->Offset + 0x5206 + (Slot * 0x8C), this->Region);

		case WWRegion::KOR:
			return std::make_unique<Letter>(this->StorageData, this->Offset + 0x63FE +  (Slot * 0x100), this->Region);
	}

	return nullptr;
}

/*
	Return a Letter from Player 4.

	u8 Slot: The Slot of the Storage.
*/
std::unique_ptr<Letter> LetterStorage::Player4(u8 Slot) const {
	if (Slot > this->LetterAmount() - 1) return nullptr;

	switch(this->Region) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Letter>(this->StorageData, this->Offset + 0xD671 + (Slot * 0xF4), this->Region);

		case WWRegion::JPN:
			return std::make_unique<Letter>(this->StorageData, this->Offset + 0x7B09 + (Slot * 0x8C), this->Region);

		case WWRegion::KOR:
			return std::make_unique<Letter>(this->StorageData, this->Offset + 0x95FD +  (Slot * 0x100), this->Region);
	}

	return nullptr;
}

/*
	Calculates the Letter Storage checksum.

	It is here, because editing the Letter Storage has nothing to do with the MAIN save.
*/
u16 LetterStorage::CalculateChecksum() {
	u32 size = 0;

	switch(this->Region) {
		case WWRegion::EUR:
		case WWRegion::USA:
			size = 0x11DF2;
			break;

		case WWRegion::JPN:
			size = 0xA412;
			break;

		case WWRegion::KOR:
			size = 0xC802;
			break;
	}

	u16 checksum = 0;
	for (u16 i = 0; i < (size / 2); i++) {
		checksum += *reinterpret_cast<u16 *>(this->StorageData.get() + (this->Offset / 2) + i);
	}

	return (u16) -checksum;
}

/*
	Return, if the checksum is valid.
*/
bool LetterStorage::ChecksumValid() {
	return (this->CalculateChecksum() == (*reinterpret_cast<uint16_t *>(this->StorageData.get() + 0x3FFFF)));
}

/*
	Fix the checksum.
*/
void LetterStorage::FixChecksum() {
	*reinterpret_cast<uint16_t *>(this->StorageData.get() + 0x3FFFF) = this->CalculateChecksum();
}