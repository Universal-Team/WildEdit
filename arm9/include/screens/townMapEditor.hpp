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

#ifndef _WILDEDIT_TOWN_MAP_EDITOR_HPP
#define _WILDEDIT_TOWN_MAP_EDITOR_HPP

#include "Item.hpp"
#include "screenCommon.hpp"
#include "structs.hpp"
#include "Town.hpp"
#include <vector>

class TownMapEditor : public Screen {
protected:
	std::unique_ptr<Town> &town;
public:
	void Draw(void) const override;
	void Logic(u16 hDown, touchPosition touch) override;
	TownMapEditor(std::unique_ptr<Town> &refTown);
	~TownMapEditor();
private:
	/* TEMP. */
	std::unique_ptr<Item> MapItems[4096];
	std::unique_ptr<Acre> townAcres[36];
	u16 TempItem;

	/* Main Draws. */
	void DrawMain(void) const;
	void DrawTempItem(void) const;

	/* Main Logics. */
	void MainLogic(u16 hDown, touchPosition touch);
	void TempLogic(u16 hDown, touchPosition touch);

	/* Mostly selection stuff. */
	int Mode = 0;
	int selection = 0;
	int selectionMode = 0;
	int currentPosX = 0;
	int currentPosY = 0;
	int currentAcre = 0;
	int MapSelection = 0;
	int PositionX = 0;
	int PositionY = 0;
	int topAcres[16] = {0};

	/* Functions. */
	void DrawPosition(void) const;
	void DrawCurrentPos();
	void updateTopGrid();
	void updateBottomGrid();
	void DrawTownMapEditor() const;
	void convertToPosition();
	void convertToSelection();
	void updateAcreImage();
	void DrawInformation() const;
	void injectTo(int MapSlot);

	int SelectionToAcre(int i) const;
	void DrawGrid(void) const;

	const std::vector<Structs::ButtonPos> TempPos = {
		{ 80, 30, 88, 32 }, // Manually.
		{ 80, 80, 88, 32 }, // Selection.
		{ 80, 130, 88, 32 } // ?
	};

	/* Top Town Map Acre pos. */
	const std::vector<Structs::ButtonPos> TopPos = {
		{ 10, 30, 32, 32 }, { 42, 30, 32, 32 }, { 74, 30, 32, 32 }, { 106, 30, 32, 32 },
		{ 10, 62, 32, 32 }, { 42, 62, 32, 32 }, { 74, 62, 32, 32 }, { 106, 62, 32, 32 },
		{ 10, 94, 32, 32 }, { 42, 94, 32, 32 }, { 74, 94, 32, 32 }, { 106, 94, 32, 32 },
		{ 10, 126, 32, 32 }, { 42, 126, 32, 32 }, { 74, 126, 32, 32 }, { 106, 126, 32, 32 }
	};
};

#endif