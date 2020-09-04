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

#ifndef _WILDEDIT_CORE_LETTER_HPP
#define _WILDEDIT_CORE_LETTER_HPP

#include "item.hpp"
#include "types.hpp"

#include <memory>
#include <vector>

class Item;
class Letter {
protected:
	std::shared_ptr<u8[]> data;
	u32 Offset;
	WWRegion region;
public:
	~Letter() {}
	Letter(std::shared_ptr<u8[]> dt, u32 offset, WWRegion letterreg) : data(dt), Offset(offset), region(letterreg) { }
	Letter(const Letter& letter) = delete;
	Letter& operator=(const Letter& letter) = delete;

	u16 playerid() const;
	std::u16string playername() const;
	u16 townid() const;
	std::u16string townname() const;
	u8 playerindex() const;

	std::u16string intro() const;
	std::u16string body() const;
	std::u16string end() const;

	u8 nameindex() const;
	u8 paperid() const;
	u8 flag() const;
	u8 senderid() const;
	u8 lettertype() const;

	std::unique_ptr<Item> item() const;
private:
	u8 *letterPointer() const {
		return data.get() + Offset;
	}
};

#endif