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

#ifndef _WILDEDIT_CORE_SAV_HPP
#define _WILDEDIT_CORE_SAV_HPP

#include "House.hpp"
#include "LetterStorage.hpp"
#include "Player.hpp"
#include "Sav.hpp"
#include "Town.hpp"
#include "types.hpp"
#include "Villager.hpp"

#include <string>

class House;
class LetterStorage;
class Player;
class Town;
class Villager;

class Sav {
protected:
	std::shared_ptr<u8[]> SaveData;
	u32 SaveSize;
	WWRegion SaveRegion;
	bool Changes;
public:
	Sav(std::shared_ptr<u8[]> data, WWRegion Region, u32 ssize) :
		SaveData(data), SaveSize(ssize), SaveRegion(Region) { };
	Sav(const Sav& sav) = delete;
	Sav& operator=(const Sav& sav) = delete;

	/* Call this when finished editing. */
	void Finish(void);

	/* Get Sav Contents. */
	std::unique_ptr<Player> player(u8 player) const;
	std::unique_ptr<Villager> villager(u8 villager) const;
	std::unique_ptr<Town> town() const;
	std::unique_ptr<LetterStorage> letterstorage() const;
	std::unique_ptr<House> house() const;

	WWRegion getRegion() const { return this->SaveRegion; };

	/* Get max Values. */
	int maxVillager() const { return 7; };

	/* Set Changes made and such. */
	void setChangesMade(bool v = true) { if (v != this->Changes) this->Changes = v; };
	bool changesMade() const { return this->Changes; };

	/* return Sav stuff. */
	u32 getLength() const { return this->SaveSize; };
	std::shared_ptr<u8[]> rawData() const { return this->SaveData; };

	u8 *savePointer() const { return this->SaveData.get(); };
};

#endif