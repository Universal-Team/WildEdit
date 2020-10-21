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

/*
	NOTES for Wild World:

	- The last 3-4 bytes of a savecopy CAN change when storing Letters into the Letter Storage for WHATEVER Reason.

		Should we add a check for that? Like.. ignore the last 3 - 4 bytes?
		Also how to handle it.. when updating the checksum?

		Unsure yet, research and experimenting needs to be made.
*/


/*
	Return the SaveType from a Buffer and load.

	std::shared_ptr<u8[]> dt: The save buffer.
	u32 length: The size of the buffer.
*/
std::unique_ptr<Sav> SaveUtils::getSave(std::shared_ptr<u8[]> dt, u32 length) {
	switch (length) {
		case 0x40000:
		case 0x4007A:
		case 0x8007A:
			if (memcmp(dt.get(), dt.get() + 0x12224, 0x12224) == 0) {
				return std::make_unique<Sav>(dt, WWRegion::JPN, length);

			} else if (memcmp(dt.get(), dt.get() + 0x15FE0, 0x15FE0) == 0) {
				return std::make_unique<Sav>(dt, WWRegion::EUR_USA, length);

			} else if (memcmp(dt.get(), dt.get() + 0x173FC, 0x173FC) == 0) {
				return std::make_unique<Sav>(dt, WWRegion::KOR, length);

			} else {
				return nullptr;
			}

		case 0x80000:
			return SaveUtils::check080000(dt, length);

	default:
		return nullptr;
	}
}

/*
	Because 0x80000 can be an AC:NL & AC:WW save, check it here!

	std::shared_ptr<u8[]> dt: The save buffer.
	u32 length: The size of the buffer.
*/
std::unique_ptr<Sav> SaveUtils::check080000(std::shared_ptr<u8[]> dt, u32 length) {
	/* Check for AC:WW Japanese. */
	if (memcmp(dt.get(), dt.get() + 0x12224, 0x12224) == 0) {
		return std::make_unique<Sav>(dt, WWRegion::JPN, length);

	/* Check for AC:WW Europe | USA. */
	} else if (memcmp(dt.get(), dt.get() + 0x15FE0, 0x15FE0) == 0) {
		return std::make_unique<Sav>(dt, WWRegion::EUR_USA, length);

	/* Check for AC:WW Korean. */
	} else if (memcmp(dt.get(), dt.get() + 0x173FC, 0x173FC) == 0) {
		return std::make_unique<Sav>(dt, WWRegion::KOR, length);

	} else {
		/* No save checks matches, return nullptr. */
		return nullptr;
	}
}

/* Credits: PKSM-Core: https://github.com/FlagBrew/PKSM-Core/blob/master/source/utils/flagUtil.cpp. */

/*
	Get a bit.

	const u8 *data: The save buffer.
	u32 offset: The offset.
	u8 bitIndex: The index of the bit.
*/
bool SaveUtils::GetBit(const u8 *data, u32 offset, u8 bitIndex) {
	bitIndex &= 7; // ensure bit access is 0-7.
	return (data[offset] >> bitIndex & 1) != 0;
}

/*
	Set a bit.

	const u8 *data: The save buffer.
	u32 offset: The offset.
	u8 bitIndex: The index of the bit.
	bool bit: if the bit is 1 (true) or 0 (false).
*/
void SaveUtils::SetBit(u8 *data, u32 offset, u8 bitIndex, bool bit) {
	bitIndex &= 7; // ensure bit access is 0-7.
	data[offset] &= ~(1 << bitIndex);
	data[offset] |= (bit ? 1 : 0) << bitIndex;

	if (save) save->setChangesMade();
}