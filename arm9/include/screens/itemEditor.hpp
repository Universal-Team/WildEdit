/*
*   This file is part of WildEdit
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

#ifndef _WILDEDIT_ITEM_EDITOR_HPP
#define _WILDEDIT_ITEM_EDITOR_HPP

#include "Item.hpp"
#include "Player.hpp"
#include "screenCommon.hpp"
#include "structs.hpp"
#include <vector>

class ItemEditor : public Screen {
protected:
	std::unique_ptr<Player> &player;
public:
	void Draw(void) const override;
	void Logic(u16 hDown, touchPosition touch) override;
	ItemEditor(std::unique_ptr<Player> &refPlayer);
	~ItemEditor();
private:
	std::unique_ptr<Item> pockets[15] = { nullptr };
	std::unique_ptr<Item> dresser[90] = { nullptr };
	int Selection = 0, Mode = 0, box = 0;

	/* Draws. */
	void DrawSubMenu() const;
	void DrawPocket() const;
	void DrawDresser() const;

	/* Logics. */
	void SubMenuLogic(u16 hDown, touchPosition touch);
	void PocketLogic(u16 hDown, touchPosition touch);
	void DresserLogic(u16 hDown, touchPosition touch);

	const std::vector<Structs::ButtonPos> mainButtons = {
		{ 80, 30, 88, 32 },
		{ 80, 80, 88, 32 },
		{ 80, 130, 88, 32 }
	};

	const std::vector<Structs::ButtonPos> pocketPos = {
		{ 25, 40, 30, 30 },
		{ 65, 40, 30, 30 },
		{ 105, 40, 30, 30 },
		{ 145, 40, 30, 30 },
		{ 185, 40, 30, 30 },
		{ 25, 80, 30, 30 },
		{ 65, 80, 30, 30 },
		{ 105, 80, 30, 30 },
		{ 145, 80, 30, 30 },
		{ 185, 80, 30, 30 },
		{ 25, 120, 30, 30 },
		{ 65, 120, 30, 30 },
		{ 105, 120, 30, 30 },
		{ 145, 120, 30, 30 },
		{ 185, 120, 30, 30 }
	};

	const std::vector<Structs::ButtonPos> dresserPos = {
		{ 25, 70, 30, 30 },
		{ 65, 70, 30, 30 },
		{ 105, 70, 30, 30 },
		{ 145, 70, 30, 30 },
		{ 185, 70, 30, 30 },
		{ 25, 140, 30, 30 },
		{ 65, 140, 30, 30 },
		{ 105, 140, 30, 30 },
		{ 145, 140, 30, 30 },
		{ 185, 140, 30, 30 }
	};
};

#endif