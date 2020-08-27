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

#include "cardSaves.hpp"
#include "config.hpp"
#include "coreUtils.hpp"
#include "flashcard.hpp"
#include "lang.hpp"
#include "msg.hpp"
#include "Sav.hpp"
#include "saveUtils.hpp"
#include "screenCommon.hpp"

#include <ctime> // For the time string.
#include <dirent.h> // For mkdir.

extern std::unique_ptr<Config> config;
bool loadedFromCart;
static std::string saveName = "";

bool CoreUtils::loadSave(const std::string saveFile) {
	save = nullptr;
	saveName = saveFile;
	FILE* in = fopen(saveName.c_str(), "rb");
	if (in) {
		fseek(in, 0, SEEK_END);
		u32 size = ftell(in);
		fseek(in, 0, SEEK_SET);
		std::shared_ptr<u8[]> saveData = std::shared_ptr<u8[]>(new u8[size]);
		fread(saveData.get(), 1, size, in);
		fclose(in);
		save = SaveUtils::getSave(saveData, size);

		/* Check if town exist. */
		if (save) {
			if (!save->town()->exist()) {
				/* Town does not exist. */
				save = nullptr;
				return false;
			}
		}

	} else {
		/* Savefile was not able to be opened. */
		return false;
	}

	if (!save) {
		/* Savefile is nullptr. */
		return false;
	}

	CoreUtils::createBackup(); // Create backup there.
	
	return true;
}

void CoreUtils::saveChanges() {
	if (save) {
		if (save->changesMade()) {
			save->Finish();
			FILE* out = fopen(saveName.c_str(), "rb+");
			fwrite(save->rawData().get(), 1, save->getLength(), out);
			fclose(out);
			if (loadedFromCart) restoreSave();
		}
	}
}

void CoreUtils::createBackup() {
	if (save) {
		if (config->createBackups()) {
			Msg::DisplayWaitMsg("Create Backup... Please wait."); // Rewrite to an appearing message until the backup was successfully done.
			char stringTime[15] = {0};
			time_t unixTime = time(NULL);
			struct tm* timeStruct = gmtime((const time_t*)&unixTime);
			std::strftime(stringTime, 14, "%Y%m%d%H%M%S", timeStruct);
			std::string path = (sdFound() ? "sd:/_nds/WildEdit/Backups/" : "fat:/_nds/WildEdit/Backups/") + std::string(stringTime);
			mkdir(path.c_str(), 0777); // Create directory.
			path += "/ACWW.sav";

			FILE *file = fopen(path.c_str(), "w");
			fwrite(save->rawData().get(), 1, save->getLength(), file);
			fclose(file);

			char message[200];
			snprintf(message, sizeof(message), Lang::get("BACKUP_RESULT").c_str(), path.c_str());
			Msg::DisplayWaitMsg(message);
		}
	}
}