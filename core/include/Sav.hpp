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

#ifndef _WILDEDIT_CORE_SAV_HPP
#define _WILDEDIT_CORE_SAV_HPP

#include "Player.hpp"
#include "Sav.hpp"
#include "Town.hpp"
#include "types.hpp"
#include "Villager.hpp"

#include <string>

class Player;
class Town;
class Villager;

class Sav {
protected:
	std::shared_ptr<u8[]> saveData;
	WWRegion region;
	u32 size;
public:
	Sav(std::shared_ptr<u8[]> dt, WWRegion Region, u32 ssize) : saveData(dt), region(Region), size(ssize) { }
	Sav(const Sav& sav) = delete;
	Sav& operator=(const Sav& sav) = delete;

	void Finish(void);
	std::unique_ptr<Player> player(int player, int index = 0) const;
	std::unique_ptr<Villager> villager(int villager) const;
	std::unique_ptr<Town> town() const;

	WWRegion getRegion() { return region; }

	int maxVillager() const { return 7; }

	void changesMade(bool v) { if (v != this->changes) this->changes = v; }
	bool changesMade() const { return this->changes; }

	/* return Sav stuff. */
	u32 getLength() const { return this->size; }
	std::shared_ptr<u8[]> rawData() const { return this->saveData; }
private:
	bool changes = false;
	u8 *savePointer() const {
		return this->saveData.get();
	}
};

#endif