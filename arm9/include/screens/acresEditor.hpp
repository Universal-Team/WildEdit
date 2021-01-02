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

#ifndef _WILDEDIT_ACRES_EDITOR_HPP
#define _WILDEDIT_ACRES_EDITOR_HPP

#include "Acre.hpp"
#include "screenCommon.hpp"
#include "structs.hpp"
#include "Town.hpp"
#include <vector>

class AcresEditor : public Screen {
protected:
	std::unique_ptr<Town> &town;
public:
	void Draw(void) const override;
	void Logic(u16 hDown, touchPosition touch) override;
	AcresEditor(std::unique_ptr<Town> &refTown);
	~AcresEditor();
private:
	std::unique_ptr<Acre> acres[36];

	int saveAcres[36] = { 0 };
	int previewAcre = 0;

	/* Draw stuff. */
	void DrawTop(void) const; // Draw Acre Image Selection.
	void DrawAcres() const; // Draw the Acres from the bottom screen.

	/* Selection stuff. */
	int Selection = 0; // Selected Acre.
	u8 selectedAcre = 0; // Acre ID.

	/* Update stuff. */
	void updateTop(); // Update the Top Screen.

	void reloadSaveAcre(int acre);
	void reloadTopAcre();

	const std::vector<Structs::ButtonPos> MapPos = {
		{ 32, 0, 32, 32 },
		{ 64, 0, 32, 32 },
		{ 96, 0, 32, 32 },
		{ 128, 0, 32, 32 },
		{ 160, 0, 32, 32 },
		{ 192, 0, 32, 32 },

		{ 32, 32, 32, 32 },
		{ 64, 32, 32, 32 },
		{ 96, 32, 32, 32 },
		{ 128, 32, 32, 32 },
		{ 160, 32, 32, 32 },
		{ 192, 32, 32, 32 },

		{ 32, 64, 32, 32 },
		{ 64, 64, 32, 32 },
		{ 96, 64, 32, 32 },
		{ 128, 64, 32, 32 },
		{ 160, 64, 32, 32 },
		{ 192, 64, 32, 32 },

		{ 32, 96, 32, 32 },
		{ 64, 96, 32, 32 },
		{ 96, 96, 32, 32 },
		{ 128, 96, 32, 32 },
		{ 160, 96, 32, 32 },
		{ 192, 96, 32, 32 },

		{ 32, 128, 32, 32 },
		{ 64, 128, 32, 32 },
		{ 96, 128, 32, 32 },
		{ 128, 128, 32, 32 },
		{ 160, 128, 32, 32 },
		{ 192, 128, 32, 32 },

		{ 32, 160, 32, 32 },
		{ 64, 160, 32, 32 },
		{ 96, 160, 32, 32 },
		{ 128, 160, 32, 32 },
		{ 160, 160, 32, 32 },
		{ 192, 160, 32, 32 }
	};
};

#endif