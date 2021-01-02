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

#include "checksum.hpp"
#include "Sav.hpp"
#include <cstring>

/* Get Player data. */
std::unique_ptr<Player> Sav::player(u8 player) const {
	if (player > 3) return nullptr; // Player goes out of scope.

	switch (this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Player>(this->SaveData, 0x000C + (player * 0x228C), this->SaveRegion, player);

		case WWRegion::JPN:
			return std::make_unique<Player>(this->SaveData, 0x000C + (player * 0x1D10), this->SaveRegion, player);

		case WWRegion::KOR:
			return std::make_unique<Player>(this->SaveData, 0x0014 + (player * 0x249C), this->SaveRegion, player);
	}

	return nullptr;
}

/* Get Villager data. */
std::unique_ptr<Villager> Sav::villager(u8 villager) const {
	if (villager > 7) return nullptr; // Villager goes out of scope.

	switch (this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Villager>(this->SaveData, 0x8A3C + (villager * 0x700), this->SaveRegion);

		case WWRegion::JPN:
			return std::make_unique<Villager>(this->SaveData, 0x744C + (villager * 0x5C0), this->SaveRegion);

		case WWRegion::KOR:
			return std::make_unique<Villager>(this->SaveData, 0x9284 + (villager * 0x7EC), this->SaveRegion);
	}

	return nullptr;
}

/* Get Town data. */
std::unique_ptr<Town> Sav::town() const { return std::make_unique<Town>(this->SaveData, this->SaveRegion); };

/* Get Letter Storage Data. */
std::unique_ptr<LetterStorage> Sav::letterstorage() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<LetterStorage>(this->SaveData, 0x2E20C, this->SaveRegion);

		case WWRegion::JPN:
			return std::make_unique<LetterStorage>(this->SaveData, 0x35BEC, this->SaveRegion);

		case WWRegion::KOR:
			return std::make_unique<LetterStorage>(this->SaveData, 0x337FC, this->SaveRegion);
	}

	return nullptr;
}

/* Get House Data. */
std::unique_ptr<House> Sav::house() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<House>(this->SaveData, 0xE558);

		case WWRegion::JPN:
			return std::make_unique<House>(this->SaveData, 0xC554);

		case WWRegion::KOR:
			return std::make_unique<House>(this->SaveData, 0xF52C);
	}

	return nullptr;
}

/* Last call before writing to file. Update Checksum. */
void Sav::Finish(void) {
	switch (this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			Checksum::UpdateChecksum(this->SaveRegion, this->savePointer(), 0x15FE0 / sizeof(u16));
			memcpy(this->savePointer() + 0x15FE0, this->savePointer(), 0x15FE0); // Copy SaveData to the second save copy.
			break;

		case WWRegion::JPN:
			Checksum::UpdateChecksum(this->SaveRegion, this->savePointer(), 0x12224 / sizeof(u16));
			memcpy(this->savePointer() + 0x12224, this->savePointer(), 0x12224); // Copy SaveData to the second save copy.
			break;

		case WWRegion::KOR:
			Checksum::UpdateChecksum(this->SaveRegion, this->savePointer(), 0x173FC / sizeof(u16));
			memcpy(this->savePointer() + 0x173FC, this->savePointer(), 0x173FC); // Copy SaveData to the second save copy.
			break;
	}
}