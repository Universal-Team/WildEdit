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
	std::shared_ptr<u8[]> PatternData;
	u32 Offset;
	WWRegion SaveRegion;
public:
	Pattern(std::shared_ptr<u8[]> patternData, u32 offset, WWRegion Region) :
		PatternData(patternData), Offset(offset), SaveRegion(Region) { };
	Pattern(const Pattern& pattern) = delete;
	Pattern& operator=(const Pattern& pattern) = delete;

	std::u16string name() const;
	void name(std::u16string v);

	u16 creatorid() const;
	void creatorid(u16 v);

	std::u16string creatorname() const;
	void creatorname(std::u16string v);

	u8 creatorGender() const;
	void creatorGender(u8 v);

	u16 origtownid() const;
	void origtownid(u16 v);

	std::u16string origtownname() const;
	void origtownname(std::u16string v);

	u8 designtype() const;
	void designtype(u8 v);

	/* Pattern Misc. */
	void ownPattern(std::unique_ptr<Player> player);
	void dumpPattern(const std::string fileName);
	void injectPattern(const std::string fileName);

	/* Pattern Image. */
	std::unique_ptr<PatternImage> image() const;
private:
	u8 *patternPointer() const { return this->PatternData.get() + this->Offset; };

	u32 getPatternSize() const {
		switch(this->SaveRegion) {
			case WWRegion::EUR:
			case WWRegion::USA:
				return 0x228;

			case WWRegion::JPN:
				return 0x220;

			case WWRegion::KOR:
				return 0x234;

			case WWRegion::UNKNOWN:
				return 0;
		}

		return 0;
	};
};

#endif