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

#include "Player.hpp"
#include "saveUtils.hpp"
#include "stringUtils.hpp"

// Face.
u8 Player::face() {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return playerPointer()[0x223C] & 0xF;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return playerPointer()[0x1CC6] & 0xF;
		case WWRegion::KOR_REV1:
			return playerPointer()[0x243C] & 0xF;
		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Player::face(u8 v) {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x223C, (playerPointer()[0x223C] & 0xF0) | (v & 0xF));
			break;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x1CC6, (playerPointer()[0x1CC6] & 0xF0) | (v & 0xF));
			break;
		case WWRegion::KOR_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x243C, (playerPointer()[0x243C] & 0xF0) | (v & 0xF));
			break;
		case WWRegion::UNKNOWN:
			break;
	}
}

// Tan.
u16 Player::tan() {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return playerPointer()[0x223D] & 0xF;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return playerPointer()[0x1CC7] & 0xF;
		case WWRegion::KOR_REV1:
			return playerPointer()[0x243D] & 0xF;
		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Player::tan(u16 v) {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x223D, (playerPointer()[0x223D] & 0xF0) | (v & 0xF));
			break;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x1CC7, (playerPointer()[0x1CC7] & 0xF0) | (v & 0xF));
			break;
		case WWRegion::KOR_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x243D, (playerPointer()[0x243D] & 0xF0) | (v & 0xF));
			break;
		case WWRegion::UNKNOWN:
			break;
	}
}

// Gender.
u8 Player::gender() {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return playerPointer()[0x228A];
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return playerPointer()[0x1CFB];
		case WWRegion::KOR_REV1:
			return playerPointer()[0x249A];
		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Player::gender(u8 v) {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x228A, v);
			break;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x1CFB, v);
			break;
		case WWRegion::KOR_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x249A, v);
		case WWRegion::UNKNOWN:
			break;
	}
}

// HairStyle.
u8 Player::hairstyle() {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return playerPointer()[0x223C] >> 4;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return playerPointer()[0x1CC6] >> 4;
		case WWRegion::KOR_REV1:
			return playerPointer()[0x243C] >> 4;;
		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Player::hairstyle(u8 v) {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x223C, (playerPointer()[0x223C] & 0xF0) | (v << 4));
			break;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x1CC6, (playerPointer()[0x1CC6] & 0xF0) | (v << 4));
			break;
		case WWRegion::KOR_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x243C, (playerPointer()[0x243C] & 0xF0) | (v << 4));
		case WWRegion::UNKNOWN:
			break;
	}
}

// HairColor.
u8 Player::haircolor() {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return playerPointer()[0x223D] >> 4;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return playerPointer()[0x1CC7] >> 4;
		case WWRegion::KOR_REV1:
			return playerPointer()[0x243D] >> 4;
		case WWRegion::UNKNOWN:
			return 0;
	}
	return 0;
}
void Player::haircolor(u8 v) {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x223D, (playerPointer()[0x223D] & 0xF) | (v << 4));
			break;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x1CC7, (playerPointer()[0x1CC7] & 0xF) | (v << 4));
			break;
		case WWRegion::KOR_REV1:
			SaveUtils::Write<u8>(this->playerPointer(), 0x243D, (playerPointer()[0x243D] & 0xF) | (v << 4));
			break;
		case WWRegion::UNKNOWN:
			break;
	}
}

// Eye Color. Does not exist.
u8 Player::eyecolor() {
	return 0;
}
void Player::eyecolor(u8 v) { }

// Badges. Does not exist.
u8 Player::badge(int badge) {
	return 0;
}
void Player::badge(int badge, u8 v) { }

// Player ID. Is that right? Check that!
u16 Player::playerid() {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return SaveUtils::Read<u16>(playerPointer(), 0x2280);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return SaveUtils::Read<u16>(playerPointer(), 0x1D04);
		case WWRegion::KOR_REV1:
			return SaveUtils::Read<u16>(playerPointer(), 0x248C);
		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Player::playerid(u16 v) {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			SaveUtils::Write<u16>(playerPointer(), 0x2280, v);
			break;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			SaveUtils::Write<u16>(playerPointer(), 0x1D04, v);
			break;
		case WWRegion::KOR_REV1:
			SaveUtils::Write<u16>(playerPointer(), 0x248C, v);
			break;
		case WWRegion::UNKNOWN:
			break;
	}
}

// Town ID. Is that right? Check that!
u16 Player::townid() {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return SaveUtils::Read<u16>(playerPointer(), 0x2276);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return SaveUtils::Read<u16>(playerPointer(), 0x1CFC);
		case WWRegion::KOR_REV1:
			return SaveUtils::Read<u16>(playerPointer(), 0x247E);
		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Player::townid(u16 v) {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			SaveUtils::Write<u16>(playerPointer(), 0x2276, v);
			break;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			SaveUtils::Write<u16>(playerPointer(), 0x1CFC, v);
			break;
		case WWRegion::KOR_REV1:
			SaveUtils::Write<u16>(playerPointer(), 0x247E, v);
			break;
		case WWRegion::UNKNOWN:
			break;
	}
}

// Town Name.
std::u16string Player::townname() {
	return StringUtils::UTF8toUTF16("?");
}
void Player::townname(std::u16string v) { }

// Player Exist.
bool Player::exist() {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return SaveUtils::Read<u16>(playerPointer(), 0x2280) != 0;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return SaveUtils::Read<u16>(playerPointer(), 0x1D04) != 0; // Seems right?
		case WWRegion::KOR_REV1:
			return SaveUtils::Read<u16>(playerPointer(), 0x248C) != 0; // Seems right?
		case WWRegion::UNKNOWN:
			return false;
	}

	return false;
}

// Player Name.
std::u16string Player::name() {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return StringUtils::ReadUTF8String(playerPointer(), 0x2282, 7, this->region);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return StringUtils::ReadUTF8String(playerPointer(), 0x1D06, 6, this->region);
		case WWRegion::KOR_REV1:
			return StringUtils::ReadUTF16String(playerPointer(), 0x248E, 6, u'\uFFFF');
		case WWRegion::UNKNOWN:
			return StringUtils::UTF8toUTF16("?");
	}

	return StringUtils::UTF8toUTF16("?");
}
void Player::name(std::u16string v) {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			StringUtils::WriteUTF8String(playerPointer(), v, 0x2282, 7, this->region);
			break;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			StringUtils::WriteUTF8String(playerPointer(), v, 0x1D06, 6, this->region);
			break;
		case WWRegion::KOR_REV1:
			StringUtils::WriteUTF16String(playerPointer(), v, 0x248E, 6);
			break;
		case WWRegion::UNKNOWN:
			break;
	}
}

// Wallet Amount.
u32 Player::wallet() {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return SaveUtils::Read<u32>(playerPointer(), 0x1B40);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return SaveUtils::Read<u32>(playerPointer(), 0x16C4);
		case WWRegion::KOR_REV1:
			return SaveUtils::Read<u32>(playerPointer(), 0x1C10); // Right.
		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Player::wallet(u32 v) {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			SaveUtils::Write<u32>(playerPointer(), 0x1B40, v);
			break;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			SaveUtils::Write<u32>(playerPointer(), 0x16C4, v);
			break;
		case WWRegion::KOR_REV1:
			SaveUtils::Write<u32>(playerPointer(), 0x1C10, v);
			break;
		case WWRegion::UNKNOWN:
			break;
	}
}

// Bank Amount.
u32 Player::bank() {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return SaveUtils::Read<u32>(playerPointer(), 0x21E4);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return SaveUtils::Read<u32>(playerPointer(), 0x1C70);
		case WWRegion::KOR_REV1:
			return SaveUtils::Read<u32>(playerPointer(), 0x23E0);
		case WWRegion::UNKNOWN:
			return 0;
	}

	return 0;
}
void Player::bank(u32 v) {
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			SaveUtils::Write<u32>(playerPointer(), 0x21E4, v);
			break;
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			SaveUtils::Write<u32>(playerPointer(), 0x1C70, v);
			break;
		case WWRegion::KOR_REV1:
			SaveUtils::Write<u32>(playerPointer(), 0x23E0, v);
			break;
		case WWRegion::UNKNOWN:
			break;
	}
}

// Island Medals. Does not exist.
u32 Player::islandmedals() {
	return 0;
}
void Player::islandmedals(u32 v) { }

// Coupons. Does not exist.
u32 Player::coupons() {
	return 0;
}
void Player::coupons(u32 v) { }

// Player Pocket.
std::unique_ptr<Item> Player::pocket(int slot) {
	if (slot > 14) return nullptr;
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return std::make_unique<Item>(data, offset + 0x1B22 + slot * 2);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return std::make_unique<Item>(data, offset + 0x16A6 + slot * 2);
		case WWRegion::KOR_REV1:
			return std::make_unique<Item>(data, offset + 0x1BF2 + slot * 2);
		case WWRegion::UNKNOWN:
			return nullptr;
	}

	return nullptr;
}

// Player Dresser.
std::unique_ptr<Item> Player::dresser(int slot) {
	if (slot > 89) return nullptr;
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return std::make_unique<Item>(data, 0x15430 + 0xB4 * Index + slot * 2);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return std::make_unique<Item>(data, 0x11764 + 0xB4 * Index + slot * 2);
		case WWRegion::KOR_REV1:
			return std::make_unique<Item>(data, 0x16800 + 0xB4 * Index + slot * 2);
		case WWRegion::UNKNOWN:
			return nullptr;
	}

	return nullptr;
}

// Player Pattern.
std::unique_ptr<Pattern> Player::pattern(int slot) {
	if (slot > 9) return nullptr;
	switch(this->region) {
		case WWRegion::USA_REV0:
		case WWRegion::USA_REV1:
		case WWRegion::EUR_REV1:
			return std::make_unique<Pattern>(data, offset + 0 + slot * 0x228, this->region);
		case WWRegion::JPN_REV0:
		case WWRegion::JPN_REV1:
			return std::make_unique<Pattern>(data, offset + 0 + slot * 0x220, this->region);
		case WWRegion::KOR_REV1:
			return std::make_unique<Pattern>(data, offset + 0 + slot * 0x234, this->region);
		case WWRegion::UNKNOWN:
			return nullptr;
	}
	
	return nullptr;
	
}

// TPC Image. Does not exist.
u8* Player::tpcImage() {
	return nullptr;
}

/* Other Offsets:
Player Bed: playerPointer()[0x1C9E] // JPN.
*/