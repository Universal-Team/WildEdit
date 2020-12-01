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
	~PlayerEditor();
private:
	/* Draws. */
	void DrawSubMenu(void) const;
	void DrawPlayerScreen(void) const;
	void DrawAppearance(void) const;
	void DrawPattern(void) const;

	/* Logics. */
	void SubMenuLogic(u16 hDown, touchPosition touch);
	void PlayerLogic(u16 hDown, touchPosition touch);
	void AppearanceLogic(u16 hDown, touchPosition touch);
	void PatternLogic(u16 hDown, touchPosition touch);

	/* Pattern Misc stuff. */
	void FreePattern();
	void DecodePattern();

	int selection = 0, Mode = 0;
	bool accessPattern = false;
	int allocatedPattern[8] = {0};
	std::unique_ptr<Pattern> ptrn[8] = { nullptr };
	std::unique_ptr<PatternImage> ptrnImg[8] = { nullptr };

	const std::vector<Structs::ButtonPos> patternPos = {
		{ 16, 30, 32, 32 },
		{ 80, 30, 32, 32 },
		{ 144, 30, 32, 32 },
		{ 208, 30, 32, 32 },

		{ 16, 96, 32, 32 },
		{ 80, 96, 32, 32 },
		{ 144, 96, 32, 32 },
		{ 208, 96, 32, 32 }
	};

	const std::vector<Structs::ButtonPos> playerButtons = {
		{ 20, 30, 88, 32 },
		{ 20, 80, 88, 32 },
		{ 20, 130, 88, 32 },
		{ 148, 30, 88, 32 },
		{ 148, 80, 88, 32 },
		{ 148, 130, 88, 32 }
	};
};

#endif