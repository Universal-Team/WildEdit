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

#include "saveUtils.hpp"
#include "types.hpp"

/*
	NOTES for Wild World:

	- The last 3-4 bytes of a savecopy CAN change when storing Letters into the Letter Storage for WHATEVER Reason.

		Should we add a check for that? Like.. ignore the last 3 - 4 bytes?
		Also how to handle it.. when updating the checksum?

		Unsure yet, research and experimenting needs to be made.
*/

const uint8_t GameCodes[4] = { 0xC5, 0x8A, 0x32, 0x32 }; // The Gamecodes.
const int SavCopyOffsets[4] = { 0x15FE0, 0x15FE0, 0x12224, 0x173FC }; // The Savcopy offsets.

/*
	Return the SaveType from a Buffer and load.

	std::shared_ptr<u8[]> dt: The save buffer.
	u32 length: The size of the buffer.
*/
std::unique_ptr<Sav> SaveUtils::getSave(std::shared_ptr<u8[]> dt, u32 length) {
	switch (length) {
		case 0x40000:
		case 0x4007A:
		case 0x80000:
		case 0x8007A:
			for (uint8_t i = 0; i < 4; i++) {
				if (dt.get()[0] == GameCodes[i] && dt.get()[SavCopyOffsets[i]] == GameCodes[i]) {
					return std::make_unique<Sav>(dt, (WWRegion)i, length);
				}
			}

			return nullptr; // If doesn't go through, it's invalid, hence nullptr.

		default:
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

/*
	Write a Nibble to the Savefile.

	u8 *Buffer: The Buffer.
	u32 offset: The offset where to write to.
	bool first: If Nibble1 (0 - 3) or Nibble2 (4 - 7). (true is Nibble1, false is Nibble2).
	u8 data: The data what to write.
	const bool SaveWrite: If changesMade should be set to true.
	*/
void SaveUtils::WriteNibble(u8 *Buffer, u32 offset, bool first, u8 data, const bool SaveWrite) {
	if (data > 0xF) return;

	if (first) reinterpret_cast<Byte *>(Buffer + offset)->Nibble1 = data; // 0 - 3.
	else reinterpret_cast<Byte *>(Buffer + offset)->Nibble2 = data; // 4 - 7.

	if (SaveWrite) {
		if (save) save->setChangesMade(true);
	}
}