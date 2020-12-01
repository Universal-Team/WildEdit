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

#ifndef _WILDEDIT_PLAYER_SELECTOR_HPP
#define _WILDEDIT_PLAYER_SELECTOR_HPP

#include "screenCommon.hpp"
#include "structs.hpp"

#include <vector>

class PlayerSelector : public Screen {
public:
	void Draw(void) const override;
	void Logic(u16 hDown, touchPosition touch) override;
	PlayerSelector();
private:
	void DrawPlayerBoxes(void) const;
	int maxPlayer = 0;
	int selectedPlayer = 0;

	const std::vector<Structs::ButtonPos> pos = {
		{ 20, 35, 100, 50 },
		{ 140, 35, 100, 50 },

		{ 20, 105, 100, 50 },
		{ 140, 105, 100, 50 }
	};
};

#endif