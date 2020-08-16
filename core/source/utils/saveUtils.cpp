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

#include "saveUtils.hpp"
#include "types.hpp"

// Return the Save class from a Buffer and load.
std::unique_ptr<Sav> SaveUtils::getSave(std::shared_ptr<u8[]> dt, u32 length) {
	switch (length) {
		case 0x40000:
		case 0x4007A:
		case 0x8007A:
			// Check for AC:WW Saves and check their region.
			if (memcmp(dt.get(), dt.get() + 0x12224, 0x12224) == 0) {
				return std::make_unique<Sav>(dt, WWRegion::JPN_REV0, length);
			} else if (memcmp(dt.get(), dt.get() + 0x15FE0, 0x15FE0) == 0) {
				return std::make_unique<Sav>(dt, WWRegion::EUR_REV1, length);
			} else if (memcmp(dt.get(), dt.get() + 0x173FC, 0x173FC) == 0) {
				return std::make_unique<Sav>(dt, WWRegion::KOR_REV1, length);
			} else {
				return nullptr;
			}

		case 0x80000:
			return SaveUtils::check080000(dt, length);
	default:
		return nullptr;
	}
}

// Because 0x80000 can be an AC:NL & AC:WW save, check it here!
std::unique_ptr<Sav> SaveUtils::check080000(std::shared_ptr<u8[]> dt, u32 length) {
	// Check for AC:WW Japanese.
	if (memcmp(dt.get(), dt.get() + 0x12224, 0x12224) == 0) {
		return std::make_unique<Sav>(dt, WWRegion::JPN_REV0, length);
		// Check for AC:WW Europe | USA.
	} else if (memcmp(dt.get(), dt.get() + 0x15FE0, 0x15FE0) == 0) {
		return std::make_unique<Sav>(dt, WWRegion::EUR_REV1, length);
		// Check for AC:WW Korean.
	} else if (memcmp(dt.get(), dt.get() + 0x173FC, 0x173FC) == 0) {
		return std::make_unique<Sav>(dt, WWRegion::KOR_REV1, length);
	} else {
		// No save checks matches, return nullptr.
		return nullptr;
	}
}