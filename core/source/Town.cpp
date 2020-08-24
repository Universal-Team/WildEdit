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

#include "saveUtils.hpp"
#include "stringUtils.hpp"
#include "Town.hpp"

/* Grasstype. */
u8 Town::grasstype() const {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return townPointer()[0x2200];
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
		case WWRegion::KOR_REV1:
		case WWRegion::UNKNOWN:
			return 0;
	}
	
	return 0;
}
void Town::grasstype(u8 v) {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			SaveUtils::Write<u8>(this->townPointer(), 0x2200, v);
			break;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
		case WWRegion::KOR_REV1:
		case WWRegion::UNKNOWN:
			break;
	}
}

/* Town Name. */
std::u16string Town::name() const {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return StringUtils::ReadUTF8String(townPointer(), 0x0004, 8, this->region);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return StringUtils::ReadUTF8String(townPointer(), 0x0004, 6, this->region);
		case WWRegion::KOR_REV1:
			return StringUtils::ReadUTF16String(townPointer(), 0x0004, 6);
		case WWRegion::UNKNOWN:
			return StringUtils::UTF8toUTF16("?");
	}

	return StringUtils::UTF8toUTF16("?");
}
void Town::name(std::u16string v) {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			StringUtils::WriteUTF8String(townPointer(), v, 0x0004, 8, this->region);
			break;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			StringUtils::WriteUTF8String(townPointer(), v, 0x0004, 6, this->region);
			break;
		case WWRegion::KOR_REV1:
			StringUtils::WriteUTF16String(townPointer(), v, 0x0004, 6);
			break;
		case WWRegion::UNKNOWN:
			break;
	}
}

/* Town Acre. */
std::unique_ptr<Acre> Town::acre(int acre) const {
	if (acre > 35) return nullptr; // Acre Index goes out of scope.
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return std::make_unique<Acre>(data, 0xC330 + acre * 1);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return std::make_unique<Acre>(data, 0xA32C + acre * 1);
		case WWRegion::KOR_REV1:
			return std::make_unique<Acre>(data, 0xD304 + acre * 1);
		case WWRegion::UNKNOWN:
			return nullptr;
	}

	return nullptr;
}

/* Town Item. */
std::unique_ptr<Item> Town::item(u32 index) const {
	if (index > 4095) return nullptr; // Item Index goes out of scope.
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return std::make_unique<Item>(data, 0xC354 + index * 2);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return std::make_unique<Item>(data, 0xA350 + index * 2);
		case WWRegion::KOR_REV1:
			return std::make_unique<Item>(data, 0xD329 + index * 2);
		case WWRegion::UNKNOWN:
			return nullptr;
	}

	return nullptr;
}

/* Return if Town exist. */
bool Town::exist() const {
	if (SaveUtils::Read<u16>(townPointer(), 0x2) == 0x0 || SaveUtils::Read<u16>(townPointer(), 0x2) == 0xFFFF)	return false;
	return true;
}

/* Turnip prices. TODO? I'm not sure where they exist yet. */
u32 Town::turnipPrices(bool isAM, int day) const {
	return 0;
}
void Town::turnipPrices(bool isAM, int day, u32 v) { }

/* Town Flag. */
std::unique_ptr<Pattern> Town::townflag() const {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return std::make_unique<Pattern>(this->data, 0x15930, this->region);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return std::make_unique<Pattern>(this->data, 0x11C5C, this->region);
		case WWRegion::KOR_REV1:
			return std::make_unique<Pattern>(this->data, 0x16D0C, this->region);
		case WWRegion::UNKNOWN:
			return nullptr;
	}

	return nullptr;
}