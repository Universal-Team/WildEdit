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

#ifndef _WILDEDIT_CORE_TOWN_HPP
#define _WILDEDIT_CORE_TOWN_HPP

#include "Acre.hpp"
#include "Item.hpp"
#include "Pattern.hpp"
#include "types.hpp"

#include <memory>
#include <vector>

class Acre;
class Item;
class Pattern;

class Town {
protected:
	std::shared_ptr<u8[]> TownData;
	WWRegion SaveRegion;
public:
	Town(std::shared_ptr<u8[]> townData, WWRegion Region) :
		TownData(townData), SaveRegion(Region) { };
	Town(const Town& town) = delete;
	Town& operator=(const Town& town) = delete;

	u8 grasstype() const;
	void grasstype(u8 v);

	std::u16string name() const;
	void name(std::u16string v);

	std::unique_ptr<Acre> acre(u8 acre) const;

	std::unique_ptr<Item> item(u16 index) const;

	bool exist() const;

	u32 turnipPrices(bool isAM, u8 day) const;
	void turnipPrices(bool isAM, u8 day, u32 v);

	std::unique_ptr<Pattern> townflag() const;

	bool itemBuried(u16 index) const;
	void itemBuried(u16 index, bool buried);

	std::unique_ptr<Item> recycleItem(u8 slot) const;
	std::unique_ptr<Item> lostFoundItem(u8 slot) const;
private:
	u8 *townPointer() const { return this->TownData.get(); };
};

#endif