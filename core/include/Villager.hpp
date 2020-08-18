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

#ifndef _WILDEDIT_CORE_VILLAGER_HPP
#define _WILDEDIT_CORE_VILLAGER_HPP

#include "Item.hpp"
#include "types.hpp"

#include <memory>
#include <vector>

class Item;
class Villager {
protected:
	std::shared_ptr<u8[]> data;
	WWRegion region;
	u32 offset;
public:
	Villager(std::shared_ptr<u8[]> villagerData, u32 villagerOffset, WWRegion Region) : data(villagerData), region(Region), offset(villagerOffset) { }
	Villager(const Villager& villager) = delete;
	Villager& operator=(const Villager& villager) = delete;

	u32 getVillagerSize() const {
		switch(this->region) {
			case WWRegion::USA_REV0:
			case WWRegion::USA_REV1:
			case WWRegion::EUR_REV1:
				return 0x700;
			case WWRegion::JPN_REV0:
			case WWRegion::JPN_REV1:
				return 0x5C0;
			case WWRegion::KOR_REV1:
				return 0x7EC;
			case WWRegion::UNKNOWN:
				return 0;
		}
		return 0;
	}

	u16 id();
	void id(u16 v);
	bool exist();
	u8 personality();
	void personality(u8 v);
	
	// Items.
	u8 song();
	void song(u8 sng);
	std::unique_ptr<Item> shirt();
	u8 wallpaper();
	void wallpaper(u8 wlp);
	u8 carpet();
	void carpet(u8 crp);
	u8 umbrella();
	void umbrella(u8 umbr);
	
	std::unique_ptr<Item> furniture(int slot);
private:
	u8* villagerPointer() const {
		return data.get() + offset;
	}
};

#endif