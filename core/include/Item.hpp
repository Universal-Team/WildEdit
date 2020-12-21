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

#ifndef _WILDEDIT_CORE_ITEM_HPP
#define _WILDEDIT_CORE_ITEM_HPP

#include "itemUtils.hpp"
#include "types.hpp"
#include <memory>
#include <vector>

/*
	0: DOWN; 1: RIGHT; 2: UP; 3: LEFT.
*/
enum class FurnitureDirection : uint8_t {
	Down,
	Right,
	Up,
	Left,
	None
};

class Item {
protected:
	std::shared_ptr<u8[]> ItemData;
	u32 Offset;
public:
	Item(std::shared_ptr<u8[]> itemData, u32 offset) :
		ItemData(itemData), Offset(offset) { };
	Item(const Item& item) = delete;
	Item& operator=(const Item& item) = delete;

	u16 id() const;
	void id(u16 v);

	u16 houseid() const;
	void houseid(u16 v);

	std::string name() const;

	ItemType itemtype() const;

	FurnitureDirection rotation() const;
	void rotation(FurnitureDirection Direction);
private:
	u8 *itemPointer() const { return this->ItemData.get() + this->Offset; };
};

#endif