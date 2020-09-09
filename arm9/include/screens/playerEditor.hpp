/*
*   This file is part of WildEdit
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

#ifndef _WILDEDIT_PLAYER_EDITOR_HPP
#define _WILDEDIT_PLAYER_EDITOR_HPP

#include "Pattern.hpp"
#include "PatternImage.hpp"
#include "Player.hpp"
#include "screenCommon.hpp"

#include "structs.hpp"
#include <vector>

class PlayerEditor : public Screen {
protected:
	std::unique_ptr<Player> player;
public:
	void Draw(void) const override;
	void Logic(u16 hDown, touchPosition touch) override;
	PlayerEditor(std::unique_ptr<Player> refPlayer);
private:
	void DrawSubMenu(void) const;
	void SubMenuLogic(u16 hDown, touchPosition touch);

	void DrawPlayerScreen(void) const;
	void PlayerLogic(u16 hDown, touchPosition touch);

	void DrawPattern(void) const;
	void PatternLogic(u16 hDown, touchPosition touch);

	void FreePattern();
	void DecodePattern();
	
	int selection = 0;
	int Mode = 0; // Screen Mode.
	
	int allocatedPattern[8] = {0};
	std::unique_ptr<Pattern> ptrn[8] = {nullptr};
	std::unique_ptr<PatternImage> ptrnImg[8] = {nullptr};

	std::vector<Structs::ButtonPos> mainButtons = {
		{80, 30, 88, 32, -1}, // Player.
		{80, 80, 88, 32, -1}, // Items.
		{80, 130, 88, 32, -1} // Appearance.
	};

	const std::vector<Structs::ButtonPos> patternPos = {
		{16, 30, 32, 32, -1},
		{80, 30, 32, 32, -1},
		{144, 30, 32, 32, -1},
		{208, 30, 32, 32, -1},

		{16, 96, 32, 32, -1},
		{80, 96, 32, 32, -1},
		{144, 96, 32, 32, -1},
		{208, 96, 32, 32, -1}
	};

	std::vector<Structs::ButtonPos> playerButtons = {
		{20, 30, 88, 32, -1}, // Wallet.
		{20, 80, 88, 32, -1}, // ?.
		{20, 130, 88, 32, -1}, // ?.
		{148, 30, 88, 32, -1}, // ?.
		{148, 80, 88, 32, -1}, // ?.
		{148, 130, 88, 32, -1} // ?.
	};
};

#endif