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

#include "Item.hpp"
#include "types.hpp"
#include <memory>
#include <vector>

class Item;

class Letter {
protected:
	std::shared_ptr<u8[]> LetterData;
	u32 Offset;
	WWRegion SaveRegion;
public:
	~Letter() { };
	Letter(std::shared_ptr<u8[]> dt, u32 offset, WWRegion letterreg) :
		LetterData(dt), Offset(offset), SaveRegion(letterreg) { };
	Letter(const Letter& letter) = delete;
	Letter& operator=(const Letter& letter) = delete;

	u16 playerid(bool sender) const;
	void playerid(u16 v, bool sender);

	std::u16string playername(bool sender) const;
	void playername(std::u16string v, bool sender);

	u16 townid(bool sender) const;
	void townid(u16 v, bool sender);

	std::u16string townname(bool sender) const;
	void townname(std::u16string v, bool sender);

	std::u16string intro() const;
	void intro(std::u16string v);

	std::u16string body() const;
	void body(std::u16string v);

	std::u16string end() const;
	void end(std::u16string v);

	u8 paperid() const;
	void paperid(u8 v);

	u8 flag() const;
	void flag(u8 v);

	u8 senderid() const;
	void senderid(u8 v);

	u8 lettertype() const;
	void lettertype(u8 v);

	std::unique_ptr<Item> item() const;
private:
	u8 *letterPointer() const { return this->LetterData.get() + this->Offset; };
};

#endif