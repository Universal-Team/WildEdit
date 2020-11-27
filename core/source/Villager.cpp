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
#include "Villager.hpp"

/*
	Get and Set the Villager ID.
*/
u8 Villager::id() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return villagerPointer()[0x6CB];

		case WWRegion::JPN:
			return villagerPointer()[0x595];

		case WWRegion::KOR:
			return villagerPointer()[0x79F];

		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Villager::id(u8 v) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x6CB, v);
			break;

		case WWRegion::JPN:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x595, v);
			break;

		case WWRegion::KOR:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x79F, v);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Return if the Villager exist.
*/
bool Villager::exist() const {
	if (this->SaveRegion == WWRegion::UNKNOWN) return false;

	if (this->id() == 0xFF)	return false;
	return true;
}

/*
	Get and Set for the Villager Personality.
*/
u8 Villager::personality() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return villagerPointer()[0x6CA];

		case WWRegion::JPN:
			return villagerPointer()[0x594];

		case WWRegion::KOR:
			return villagerPointer()[0x79E];

		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Villager::personality(u8 v) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x6CA, v);
			break;

		case WWRegion::JPN:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x594, v);
			break;

		case WWRegion::KOR:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x79E, v);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Get and Set for the Villager Song.

	This is an uint8_t index on Wild World.
	This needs still to be researched.
*/
u8 Villager::song() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return this->villagerPointer()[0x6D0];

		case WWRegion::JPN:
			return this->villagerPointer()[0x59A];

		case WWRegion::KOR:
			return this->villagerPointer()[0x7A4];

		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Villager::song(u8 sng) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x6D0, sng);
			break;

		case WWRegion::JPN:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x59A, sng);
			break;

		case WWRegion::KOR:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x7A4, sng);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Return the Villager Shirt.
*/
std::unique_ptr<Item> Villager::shirt() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Item>(this->VillagerData, this->Offset + 0x6EC);

		case WWRegion::JPN:
			return std::make_unique<Item>(this->VillagerData, this->Offset + 0x5AE);

		case WWRegion::KOR:
			return std::make_unique<Item>(this->VillagerData, this->Offset + 0x7C2);

		case WWRegion::UNKNOWN:
			return nullptr;
	}

	return nullptr;
}

/*
	Get and Set for the Villager Wallpaper.

	This is an uint8_t index on Wild World.
*/
u8 Villager::wallpaper() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return this->villagerPointer()[0x6EE];

		case WWRegion::JPN:
			return this->villagerPointer()[0x5B0];

		case WWRegion::KOR:
			return this->villagerPointer()[0x7C4];

		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Villager::wallpaper(u8 wlp) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x6EE, wlp);
			break;

		case WWRegion::JPN:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x5B0, wlp);
			break;

		case WWRegion::KOR:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x7C4, wlp);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Get and Set for the Villager Carpet.

	This is an uint8_t index on Wild World.
*/
u8 Villager::carpet() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return this->villagerPointer()[0x6EF];

		case WWRegion::JPN:
			return this->villagerPointer()[0x5B1];

		case WWRegion::KOR:
			return this->villagerPointer()[0x7C5];

		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Villager::carpet(u8 crp) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x6EF, crp);
			break;

		case WWRegion::JPN:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x5B1, crp);
			break;

		case WWRegion::KOR:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x7C5, crp);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Get and Set for the Villager Umbrella.

	This is an uint8_t index on Wild World.
*/
u8 Villager::umbrella() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return this->villagerPointer()[0x6F4];

		case WWRegion::JPN:
			return this->villagerPointer()[0x544];

		case WWRegion::KOR:
			return this->villagerPointer()[0x7CA];

		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Villager::umbrella(u8 umbr) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x6F4, umbr);
			break;

		case WWRegion::JPN:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x544, umbr);
			break;

		case WWRegion::KOR:
			SaveUtils::Write<u8>(this->villagerPointer(), 0x7CA, umbr);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Return the Villager Furniture.

	u8 slot: The Furniture index.
*/
std::unique_ptr<Item> Villager::furniture(u8 slot) const {
	if (slot > 9) return nullptr;

	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Item>(this->VillagerData, this->Offset + 0x6AC + slot * 2);

		case WWRegion::JPN:
			return std::make_unique<Item>(this->VillagerData, this->Offset + 0x578 + slot * 2);

		case WWRegion::KOR:
			return std::make_unique<Item>(this->VillagerData, this->Offset + 0x77C + slot * 2);

		case WWRegion::UNKNOWN:
			return nullptr;
	}

	return nullptr;
}