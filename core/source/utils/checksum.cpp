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

#include "checksum.hpp"
#include "saveUtils.hpp"
#include "types.hpp"

#include <cstring>
#include <string>

/*
	Calculate Animal Crossing: Wild World's Checksum.

	const u16 *buffer: The save buffer.
	u64 size: The size which should be calculated.
	u16 checksumOffset: The offset of the checksum.
*/
u16 Checksum::Calculate(const u16 *buffer, u64 size, u16 checksumOffset) {
	if ((checksumOffset & 1) == 1) return 0; // checksumOffset must be 16-bit aligned!

	u16 checksum = 0;
	for (u16 i = 0; i < size; i++) {
		if (i == checksumOffset) continue;
		checksum += buffer[i];
	}

	return (u16) -checksum;
}

/*
	Verify Animal Crossing: Wild World's Checksum.

	const u16 *buffer: The save buffer.
	u64 size: The size which should be verified.
	u16 currentChecksum: The current checksum.
	u16 checksumOffset: The offset of the checksum.
*/
bool Checksum::Verify(const u16 *buffer, u64 size, u16 currentChecksum, u16 checksumOffset) {
	return Checksum::Calculate(buffer, size, checksumOffset) == currentChecksum;
}

/*
	Update Animal Crossing: Wild World's Checksum.

	WWRegion region: The save region.
	u8 *saveBuffer: The save buffer.
	u64 size: The size which should be updated.
*/
void Checksum::UpdateChecksum(WWRegion region, u8 *saveBuffer, u64 size) {
	switch(region) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u16>(saveBuffer, 0x15FDC, Checksum::Calculate(reinterpret_cast<u16 *>(saveBuffer), size, 0xAFEE));
			break;

		case WWRegion::JPN:
			SaveUtils::Write<u16>(saveBuffer, 0x12220, Checksum::Calculate(reinterpret_cast<u16 *>(saveBuffer), size, 0x9110));
			break;

		case WWRegion::KOR:
			SaveUtils::Write<u16>(saveBuffer, 0x173F8, Checksum::Calculate(reinterpret_cast<u16 *>(saveBuffer), size, 0xB9FC));
			break;
	}
}