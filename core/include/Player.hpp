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

#ifndef _WILDEDIT_CORE_PLAYER_HPP
#define _WILDEDIT_CORE_PLAYER_HPP

#include "Item.hpp"
#include "Letter.hpp"
#include "Pattern.hpp"
#include "types.hpp"

#include <memory>
#include <vector>

class Item;
class Letter;
class Pattern;

class Player {
protected:
	std::shared_ptr<u8[]> PlayerData;
	u32 Offset;
	u8 Index;
	WWRegion SaveRegion;
public:
	Player(std::shared_ptr<u8[]> playerData, u32 playerOffset, WWRegion Region, u8 index) :
			PlayerData(playerData), Offset(playerOffset), Index(index), SaveRegion(Region) { };
	Player(const Player& player) = delete;
	Player& operator=(const Player& player) = delete;

	u8 face() const;
	void face(u8 v);

	u8 gender() const;
	void gender(u8 v);

	u8 tan() const;
	void tan(u8 v);

	u8 hairstyle() const;
	void hairstyle(u8 v);

	u8 haircolor() const;
	void haircolor(u8 v);

	u16 playerid() const;
	void playerid(u16 v);

	u16 townid() const;
	void townid(u16 v);

	std::u16string townname() const;
	void townname(std::u16string v);

	bool exist() const;

	std::u16string name() const;
	void name(std::u16string v);

	u32 wallet() const;
	void wallet(u32 v);

	u32 bank() const;
	void bank(u32 v);

	std::unique_ptr<Letter> letter(u8 slot) const;

	std::unique_ptr<Item> pocket(u8 slot) const;
	std::unique_ptr<Item> dresser(u8 slot) const;

	std::unique_ptr<Pattern> pattern(u8 slot) const;

	/* Dump & Inject. */
	void dumpPlayer(const std::string fileName);
	bool injectPlayer(const std::string fileName);

	u8 acornFestival() const;
	void acornFestival(u8 v);

	u8 bed() const;
	void bed(u8 v);
private:
	u8 *playerPointer() const { return this->PlayerData.get() + this->Offset; };

	u32 getPlayerSize() const {
		switch(this->SaveRegion) {
			case WWRegion::EUR:
			case WWRegion::USA:
				return 0x228C;

			case WWRegion::JPN:
				return 0x1D10;

			case WWRegion::KOR:
				return 0x249C;
		}

		return 0;
	};
};

#endif