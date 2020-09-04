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

#include "Letter.hpp"
#include "saveUtils.hpp"
#include "stringUtils.hpp"

/*
	For now only notes.

		Korean:
			Begin: 0x1180. // 0x116C.
			IntroSize: 0x10 * 2 beginning at 0x1200. // 0x11EC.
			Bodysize: 0x40 * 2 beginning at 0x1213. // 0x1200.
			End: 0xA * 2 beginning at 0x1294. // 0x1280.
			Item: 0x12B8. // 0x12A4.
			LetterSize: 0x140.

		JPN:
			Start: 0x1114. // 0x1108.
			IntroSize: 0xA beginning at 0x1140. // 0x1134.
			BodySize: 0x40 beginning at 0x114A. // 0x113E.
			End: 0x10 beginning at 0x118A. // 0x117E.
			Item: 0x119E. // 0x1192.
			LetterSize: 0x8C.

		EUR / USA:
			Start: 0x1158(?). // 0x114C.
			IntroSize: 0xF beginning at 0x1188. // 0x117C.
			BodySize: 0x54 beginning at 0x11A0. // 0x1194.
			EndSize: 0x1A beginning at 0x1220. // 0x1214.
			Item: 0x1244. // 0x1238.
			LetterSize: 0xF4.
*/

u16 Letter::playerid() const {
	return 0;
}

std::u16string Letter::playername() const {
	return StringUtils::UTF8toUTF16("?");
}

u16 Letter::townid() const {
	return 0;
}

std::u16string Letter::townname() const {
	return StringUtils::UTF8toUTF16("?");
}

u8 Letter::playerindex() const {
	return 0;
}

std::u16string Letter::intro() const {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return StringUtils::ReadUTF8String(letterPointer(), 0x30, 0xF, this->region);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return StringUtils::ReadUTF8String(letterPointer(), 0x2C, 0xA, this->region);
		case WWRegion::KOR_REV1:
			return StringUtils::ReadUTF16String(letterPointer(), 0x80, 0xF);
		case WWRegion::UNKNOWN:
			return StringUtils::UTF8toUTF16("?");
	}

	return StringUtils::UTF8toUTF16("?");
}

std::u16string Letter::body() const {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return StringUtils::ReadUTF8String(letterPointer(), 0x48, 84, this->region);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return StringUtils::ReadUTF8String(letterPointer(), 0x36, 64, this->region);
		case WWRegion::KOR_REV1:
			return StringUtils::ReadUTF16String(letterPointer(), 0x93, 64); // 32 cause UTF-16.
		case WWRegion::UNKNOWN:
			return StringUtils::UTF8toUTF16("?");
	}

	return StringUtils::UTF8toUTF16("?");
}

std::u16string Letter::end() const {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return StringUtils::ReadUTF8String(letterPointer(), 0xC8, 0x1A, this->region);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return StringUtils::ReadUTF8String(letterPointer(), 0x76, 0x10, this->region);
		case WWRegion::KOR_REV1:
			return StringUtils::ReadUTF16String(letterPointer(), 0x114, 0x1A);
		case WWRegion::UNKNOWN:
			return StringUtils::UTF8toUTF16("?");
	}

	return StringUtils::UTF8toUTF16("?");
}

u8 Letter::nameindex() const {
	return 0;
}

u8 Letter::paperid() const {
	return 0;
}

u8 Letter::flag() const {
	return 0;
}

u8 Letter::senderid() const {
	return 0;
}

u8 Letter::lettertype() const {
	return 0;
}

std::unique_ptr<Item> Letter::item() const {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return std::make_unique<Item>(data, Offset + 0x1238);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return std::make_unique<Item>(data, Offset + 0x1192);
		case WWRegion::KOR_REV1:
			return std::make_unique<Item>(data, Offset + 0x12A4);
		case WWRegion::UNKNOWN:
			return nullptr;
	}

	return nullptr;
}