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
	Get and Set the Player ID.

	bool sender: If sender (true) or receiver (false).
*/
u16 Letter::playerid(bool sender) const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return SaveUtils::Read<u16>(this->letterPointer(), sender ? 0x26 : 0xE);

		case WWRegion::JPN:
			return SaveUtils::Read<u16>(this->letterPointer(), sender ? 0x20 : 0xC);

		case WWRegion::KOR:
			return SaveUtils::Read<u16>(this->letterPointer(), sender ? 0x32 : 0x12);

		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Letter::playerid(u16 v, bool sender) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u16>(this->letterPointer(), sender ? 0x26 : 0xE, v);
			break;

		case WWRegion::JPN:
			SaveUtils::Write<u16>(this->letterPointer(), sender ? 0x20 : 0xC, v);
			break;

		case WWRegion::KOR:
			SaveUtils::Write<u16>(this->letterPointer(), sender ? 0x32 : 0x12, v);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Get and Set the Player Name.

	bool sender: If sender (true) or receiver (false).
*/
std::u16string Letter::playername(bool sender) const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return StringUtils::ReadUTF8String(this->letterPointer(), sender ? 0x28 : 0x10, 8, this->SaveRegion);

		case WWRegion::JPN:
			return StringUtils::ReadUTF8String(this->letterPointer(), sender ? 0x22 : 0xE, 6, this->SaveRegion);

		case WWRegion::KOR:
			return StringUtils::ReadUTF16String(this->letterPointer(), sender ? 0x34 : 0x14, 6);

		case WWRegion::UNKNOWN:
			return StringUtils::UTF8toUTF16("?");
	}

	return StringUtils::UTF8toUTF16("?");
}
void Letter::playername(std::u16string v, bool sender) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			StringUtils::WriteUTF8String(this->letterPointer(), v, sender ? 0x28 : 0x10, 8, this->SaveRegion);
			break;

		case WWRegion::JPN:
			StringUtils::WriteUTF8String(this->letterPointer(), v, sender ? 0x22 : 0xE, 6, this->SaveRegion);
			break;

		case WWRegion::KOR:
			StringUtils::WriteUTF16String(this->letterPointer(), v, sender ? 0x34 : 0x14, 6);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Get and Set the Town ID.

	bool sender: If sender (true) or receiver (false).
*/
u16 Letter::townid(bool sender) const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return SaveUtils::Read<u16>(this->letterPointer(), sender ? 0x1C : 0x4);

		case WWRegion::JPN:
			return SaveUtils::Read<u16>(this->letterPointer(), sender ? 0x18 : 0x4);

		case WWRegion::KOR:
			return SaveUtils::Read<u16>(this->letterPointer(), sender ? 0x24 : 0x4);

		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Letter::townid(u16 v, bool sender) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u16>(this->letterPointer(), sender ? 0x1C : 0x4, v);
			break;

		case WWRegion::JPN:
			SaveUtils::Write<u16>(this->letterPointer(), sender ? 0x18 : 0x4, v);
			break;

		case WWRegion::KOR:
			SaveUtils::Write<u16>(this->letterPointer(), sender ? 0x24 : 0x4, v);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Get and Set the Town Name.

	bool sender: If sender (true) or receiver (false).
*/
std::u16string Letter::townname(bool sender) const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return StringUtils::ReadUTF8String(this->letterPointer(), sender ? 0x1E : 0x6, 8, this->SaveRegion);

		case WWRegion::JPN:
			return StringUtils::ReadUTF8String(this->letterPointer(), sender ? 0x1A : 0x6, 6, this->SaveRegion);

		case WWRegion::KOR:
			return StringUtils::ReadUTF16String(this->letterPointer(), sender ? 0x26 : 0x6, 6);

		case WWRegion::UNKNOWN:
			return StringUtils::UTF8toUTF16("?");
	}

	return StringUtils::UTF8toUTF16("?");
}
void Letter::townname(std::u16string v, bool sender) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			StringUtils::WriteUTF8String(this->letterPointer(), v, sender ? 0x1E : 0x2, 8, this->SaveRegion);
			break;

		case WWRegion::JPN:
			StringUtils::WriteUTF8String(this->letterPointer(), v, sender ? 0x1A : 0x2, 6, this->SaveRegion);
			break;

		case WWRegion::KOR:
			StringUtils::WriteUTF16String(this->letterPointer(), v, sender ? 0x26 : 0x2, 6);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Get and Set the Letter's intro part.
*/
std::u16string Letter::intro() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return StringUtils::ReadUTF8String(this->letterPointer(), 0x30, 24, this->SaveRegion);

		case WWRegion::JPN:
			return StringUtils::ReadUTF8String(this->letterPointer(), 0x2C, 10, this->SaveRegion);

		case WWRegion::KOR:
			return StringUtils::ReadUTF16String(this->letterPointer(), 0x44, 10);

		case WWRegion::UNKNOWN:
			return StringUtils::UTF8toUTF16("?");
	}

	return StringUtils::UTF8toUTF16("?");
}
void Letter::intro(std::u16string v) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			StringUtils::WriteUTF8String(this->letterPointer(), v, 0x30, 24, this->SaveRegion);
			break;

		case WWRegion::JPN:
			StringUtils::WriteUTF8String(this->letterPointer(), v, 0x2C, 10, this->SaveRegion);
			break;

		case WWRegion::KOR:
			StringUtils::WriteUTF16String(this->letterPointer(), v, 0x44, 10);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Get and Set the Letter's body part.
*/
std::u16string Letter::body() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return StringUtils::ReadUTF8String(this->letterPointer(), 0x48, 129, this->SaveRegion);

		case WWRegion::JPN:
			return StringUtils::ReadUTF8String(this->letterPointer(), 0x36, 64, this->SaveRegion);

		case WWRegion::KOR:
			return StringUtils::ReadUTF16String(this->letterPointer(), 0x58, 64);

		case WWRegion::UNKNOWN:
			return StringUtils::UTF8toUTF16("?");
	}

	return StringUtils::UTF8toUTF16("?");
}
void Letter::body(std::u16string v) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			StringUtils::WriteUTF8String(this->letterPointer(), v, 0x48, 129, this->SaveRegion);
			break;

		case WWRegion::JPN:
			StringUtils::WriteUTF8String(this->letterPointer(), v, 0x36, 64, this->SaveRegion);
			break;

		case WWRegion::KOR:
			StringUtils::WriteUTF16String(this->letterPointer(), v, 0x58, 64);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Get and Set the Letter's ending part.
*/
std::u16string Letter::end() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return StringUtils::ReadUTF8String(this->letterPointer(), 0xC9, 32, this->SaveRegion);

		case WWRegion::JPN:
			return StringUtils::ReadUTF8String(this->letterPointer(), 0x76, 16, this->SaveRegion);

		case WWRegion::KOR:
			return StringUtils::ReadUTF16String(this->letterPointer(), 0xD8, 16);

		case WWRegion::UNKNOWN:
			return StringUtils::UTF8toUTF16("?");
	}

	return StringUtils::UTF8toUTF16("?");
}
void Letter::end(std::u16string v) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			StringUtils::WriteUTF8String(this->letterPointer(), v, 0xC9, 32, this->SaveRegion);
			break;

		case WWRegion::JPN:
			StringUtils::WriteUTF8String(this->letterPointer(), v, 0x76, 16, this->SaveRegion);
			break;

		case WWRegion::KOR:
			StringUtils::WriteUTF16String(this->letterPointer(), v, 0xD8, 16);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Get and Set the Letter's Paper ID.
*/
u8 Letter::paperid() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return this->letterPointer()[0xED];

		case WWRegion::JPN:
			return this->letterPointer()[0x87];

		case WWRegion::KOR:
			return this->letterPointer()[0xF9];

		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Letter::paperid(u8 v) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u8>(this->letterPointer(), 0xED, v);
			break;

		case WWRegion::JPN:
			SaveUtils::Write<u8>(this->letterPointer(), 0x87, v);
			break;

		case WWRegion::KOR:
			SaveUtils::Write<u8>(this->letterPointer(), 0xF9, v);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Get and Set the Letter's flags.
*/
u8 Letter::flag() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return this->letterPointer()[0xEE];

		case WWRegion::JPN:
			return this->letterPointer()[0x88];

		case WWRegion::KOR:
			return this->letterPointer()[0xFA];

		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Letter::flag(u8 v) {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			SaveUtils::Write<u8>(this->letterPointer(), 0xEE, v);
			break;

		case WWRegion::JPN:
			SaveUtils::Write<u8>(this->letterPointer(), 0x88, v);
			break;

		case WWRegion::KOR:
			SaveUtils::Write<u8>(this->letterPointer(), 0xFA, v);
			break;

		case WWRegion::UNKNOWN:
			break;
	}
}

/*
	Return the Letter's Attachment item.
*/
std::unique_ptr<Item> Letter::item() const {
	switch(this->SaveRegion) {
		case WWRegion::EUR:
		case WWRegion::USA:
			return std::make_unique<Item>(this->LetterData, this->Offset + 0xF0);

		case WWRegion::JPN:
			return std::make_unique<Item>(this->LetterData, this->Offset + 0x8A);

		case WWRegion::KOR:
			return std::make_unique<Item>(this->LetterData, this->Offset + 0xFC);

		case WWRegion::UNKNOWN:
			return nullptr;
	}

	return nullptr;
}