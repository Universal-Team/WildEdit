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
*          Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*          Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#ifndef _WILDEDIT_CARD_SAVES_HPP
#define _WILDEDIT_CARD_SAVES_HPP

#include "auxspi.hpp"

#define cardSave "sd:/_nds/WildEdit/backups/card.sav"

extern auxspi_extra card_type;
extern sNDSHeader nds;
extern char gamename[13];
extern char gameid[5];

bool isValidTid(char* tid);

bool updateCardInfo(void);
bool updateCardInfo(sNDSHeader* nds, char* gameid, char* gamename, auxspi_extra* card_type);

void dumpSave(void);
bool restoreSave(void);

#endif