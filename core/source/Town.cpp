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

#include "saveUtils.hpp"
#include "stringUtils.hpp"
#include "Town.hpp"

/*
	Get and Set the Grasstype.
*/
u8 Town::grasstype() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return this->townPointer()[0x2200];

		case WWRegion::JPN:
		case WWRegion::KOR:
			return 0;
	}

	return 0;
}
void Town::grasstype(u8 v) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u8>(this->townPointer(), 0x2200, v);
			break;

		case WWRegion::JPN:
		case WWRegion::KOR:
			break;
	}
}

/*
	Get and Set the Town Name.
*/
std::u16string Town::name() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return StringUtils::ReadUTF8String(this->townPointer(), 0x0004, 8, this->SaveRegion);

		case WWRegion::JPN:
			return StringUtils::ReadUTF8String(this->townPointer(), 0x0004, 6, this->SaveRegion);

		case WWRegion::KOR:
			return StringUtils::ReadUTF16String(this->townPointer(), 0x0004, 6);
	}

	return StringUtils::UTF8toUTF16("?");
}
void Town::name(std::u16string v) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			StringUtils::WriteUTF8String(this->townPointer(), v, 0x0004, 8, this->SaveRegion);
			break;

		case WWRegion::JPN:
			StringUtils::WriteUTF8String(this->townPointer(), v, 0x0004, 6, this->SaveRegion);
			break;

		case WWRegion::KOR:
			StringUtils::WriteUTF16String(this->townPointer(), v, 0x0004, 6);
			break;
	}
}

/*
	Return a Town Acre.

	u8 acre: Acre Index.
*/
std::unique_ptr<Acre> Town::acre(u8 acre) const {
	if (acre > 35) return nullptr; // Acre Index goes out of scope.

	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Acre>(this->TownData, 0xC330 + acre * 1);

		case WWRegion::JPN:
			return std::make_unique<Acre>(this->TownData, 0xA32C + acre * 1);

		case WWRegion::KOR:
			return std::make_unique<Acre>(this->TownData, 0xD304 + acre * 1);
	}

	return nullptr;
}

/*
	Return a Town Map Item.

	u16 index: The Town Map Item index.
*/
std::unique_ptr<Item> Town::item(u16 index) const {
	if (index > 4095) return nullptr; // Item Index goes out of scope.

	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Item>(this->TownData, 0xC354 + index * 2);

		case WWRegion::JPN:
			return std::make_unique<Item>(this->TownData, 0xA350 + index * 2);

		case WWRegion::KOR:
			return std::make_unique<Item>(this->TownData, 0xD328 + index * 2);
	}

	return nullptr;
}

/*
	Return if Town exist.
*/
bool Town::exist() const {
	if (SaveUtils::Read<u16>(this->townPointer(), 0x2) == 0x0 || SaveUtils::Read<u16>(this->townPointer(), 0x2) == 0xFFFF) return false;
	return true;
}

/*
	Get and Set the Turnip price.
*/
u8 Town::turnipPrice() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return this->townPointer()[0x15F5D];

		case WWRegion::JPN:
			return this->townPointer()[0x121A3];

		case WWRegion::KOR:
			return this->townPointer()[0x17370];
	}

	return 0;
}
void Town::turnipPrice(u8 v) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u8>(this->townPointer(), 0x15F5D, v);
			break;

		case WWRegion::JPN:
			SaveUtils::Write<u8>(this->townPointer(), 0x121A3, v);
			break;

		case WWRegion::KOR:
			SaveUtils::Write<u8>(this->townPointer(), 0x17370, v);
			break;
	}
}

/*
	Return the Townflag pattern.
*/
std::unique_ptr<Pattern> Town::townflag() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Pattern>(this->TownData, 0x15930, this->SaveRegion);

		case WWRegion::JPN:
			return std::make_unique<Pattern>(this->TownData, 0x11C5C, this->SaveRegion);

		case WWRegion::KOR:
			return std::make_unique<Pattern>(this->TownData, 0x16D0C, this->SaveRegion);
	}

	return nullptr;
}

/*
	Get and Set, if item is buried.

	u16 index: Town Map Item index.
*/
bool Town::itemBuried(u16 index) const {
	if (index > 4095) return false;

	u32 offset = 0;
	switch(this->SaveRegion) {
		case WWRegion::JPN:
			offset = 0xC350 + ((index / 256) * 256 + (index % 256)) / 8;
			break;

		case WWRegion::EUR:
		case WWRegion::USA:
			offset = 0xE354 + ((index / 256) * 256 + (index % 256)) / 8;
			break;

		case WWRegion::KOR:
			offset = 0xF328 + ((index / 256) * 256 + (index % 256)) / 8;
			break;
	}

	return SaveUtils::GetBit(this->townPointer(), offset, (index % 256) % 8);
}
void Town::itemBuried(u16 index, bool buried) {
	if (index > 4095) return;

	/* Check, if already buried or not. */
	if (this->itemBuried(index) == buried) return; // No need to set again.

	u32 offset = 0;
	switch(this->SaveRegion) {
		case WWRegion::JPN:
			offset = 0xC350 + ((index / 256) * 256 + (index % 256)) / 8;
			break;

		case WWRegion::EUR:
		case WWRegion::USA:
			offset = 0xE354 + ((index / 256) * 256 + (index % 256)) / 8;
			break;

		case WWRegion::KOR:
			offset = 0xF328 + ((index / 256) * 256 + (index % 256)) / 8;
			break;
	}

	std::unique_ptr<Item> item = this->item(index);

	if (item->itemtype() == ItemType::Empty) return; // Do not allow buried on empty spots.

	/* Write buried state. */
	SaveUtils::SetBit(this->townPointer(), offset, (index % 256) % 8, buried);
}

/*
	Return the Recycle bin (or whatever you would call that box inside the Townhall there) Items.

	u8 slot: The slot of the item.
*/
std::unique_ptr<Item> Town::recycleItem(u8 slot) const {
	if (slot > 14) return nullptr; // Item Index goes out of scope.

	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Item>(this->TownData, 0x15EDE + slot * 2);

		case WWRegion::JPN:
			return std::make_unique<Item>(this->TownData, 0x12132 + slot * 2);

		case WWRegion::KOR:
			return std::make_unique<Item>(this->TownData, 0x172DE + slot * 2);
	}

	return nullptr;
}

/*
	Return the Lost and Found Items.

	u8 slot: The slot of the item.
*/
std::unique_ptr<Item> Town::lostFoundItem(u8 slot) const {
	if (slot > 14) return nullptr; // Item Index goes out of scope.

	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Item>(this->TownData, 0x15EC0 + slot * 2);

		case WWRegion::JPN:
			return std::make_unique<Item>(this->TownData, 0x12114 + slot * 2);

		case WWRegion::KOR:
			return std::make_unique<Item>(this->TownData, 0x172C0 + slot * 2);
	}

	return nullptr;
}