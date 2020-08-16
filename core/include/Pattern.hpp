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

#ifndef _WILDEDIT_CORE_PATTERN_HPP
#define _WILDEDIT_CORE_PATTERN_HPP

#include "PatternImage.hpp"
#include "Player.hpp"
#include "types.hpp"

#include <memory>
#include <vector>

class Player;
class Pattern {
protected:
	u32 Offset;
	std::shared_ptr<u8[]> data;
	WWRegion region;
public:
	Pattern(std::shared_ptr<u8[]> patternData, u32 offset, WWRegion Region) : Offset(offset), data(patternData), region(Region) { }
	Pattern(const Pattern& pattern) = delete;
	Pattern& operator=(const Pattern& pattern) = delete;

	std::u16string name();
	void name(std::u16string v);
	u16 creatorid();
	void creatorid(u16 v);
	std::u16string creatorname();
	void creatorname(std::u16string v);
	u8 creatorGender();
	void creatorGender(u8 v);
	u16 origtownid();
	void origtownid(u16 v);
	std::u16string origtownname();
	void origtownname(std::u16string v);
	u8 designtype();
	void designtype(u8 v);

	// Pattern Misc.
	void ownPattern(std::unique_ptr<Player> player);
	void dumpPattern(const std::string fileName);
	void injectPattern(const std::string fileName);

	// Pattern Image.
	u8* patternData(const int pattern);
	std::array<u8, 16> customPalette();
	std::shared_ptr<PatternImage> image(const int pattern);
private:
	u8* patternPointer() const {
		return data.get() + Offset;
	}
};

#endif