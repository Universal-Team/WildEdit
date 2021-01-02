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

#include "cardSaves.hpp"
#include "config.hpp"
#include "coreUtils.hpp"
#include "flashcard.hpp"
#include "lang.hpp"
#include "msg.hpp"
#include "Sav.hpp"
#include "saveUtils.hpp"
#include "screenCommon.hpp"

#include <algorithm> // For std::max.
#include <ctime> // For the time string.
#include <dirent.h> // For mkdir.

extern std::unique_ptr<Config> config;
bool loadedFromCart;
static std::string saveName = "";

bool CoreUtils::loadSave(const std::string saveFile) {
	save = nullptr;
	saveName = saveFile;
	FILE *in = fopen(saveName.c_str(), "rb");

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

			FILE *out = fopen(saveName.c_str(), "rb+");
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

static constexpr u16 PatternPalette[] = {
	0x801f, 0x99df, 0x82bf, 0x83ff, 0x83f5, 0x83ea, 0x83e0, 0xaaa0, 0xd540, 0xfc00, 0xfc0a, 0xfc15, 0xfc1f, 0x8000, 0xffff,
	0xbdff, 0xbedf, 0xbf9f, 0xbfff, 0xbffb, 0xbff5, 0xbfef, 0xc2aa, 0xd60a, 0xfdef, 0xfdf6, 0xfdfc, 0xfdff, 0x8000, 0xffff,
	0x8014, 0x80d4, 0x81d4, 0x8294, 0x828e, 0x8286, 0x8280, 0x9140, 0xa880, 0xd000, 0xd006, 0xd00e, 0xd014, 0x8000, 0xffff,
	0x8260, 0xb72b, 0xeff6, 0xb660, 0xd32a, 0xebf5, 0xd540, 0xea05, 0xfeab, 0xfc00, 0xfda9, 0xed26, 0xd883, 0xc400, 0xffff,
	0x81d5, 0xa2ba, 0xc77f, 0x9c3f, 0xb53f, 0xce5f, 0xfc15, 0xfd9a, 0xff3f, 0xceff, 0xba5b, 0xa597, 0x90f3, 0x804f, 0xffff,
	0x801f, 0x815f, 0xaedf, 0xd7bf, 0x804f, 0x9934, 0xb61a, 0xceff, 0xfeab, 0xff10, 0xff95, 0xfffa, 0xb5ad, 0x8000, 0xffff,
	0x83e0, 0xa3e8, 0xc7f1, 0xebfa, 0xfc00, 0xfd08, 0xfe31, 0xff5a, 0x801f, 0xa11f, 0xc63f, 0xeb5f, 0xb5ad, 0x8000, 0xffff,
	0x80c0, 0xa188, 0xc270, 0xe358, 0x804f, 0x9534, 0xae3a, 0xc71f, 0x82da, 0x9f3c, 0xbf7e, 0xdfdf, 0xb5ad, 0x8000, 0xffff,

	0xfc00, 0x801f, 0x83ff, 0xfd08, 0xa11f, 0xa3ff, 0xfe31, 0xc63f, 0xc7ff, 0xff5a, 0xeb5f, 0xebff, 0xb5ad, 0x8000, 0xffff,
	0x83e0, 0xfc00, 0xfc1f, 0xa3e8, 0xfd08, 0xfd1f, 0xc7f1, 0xfe31, 0xfe3f, 0xebfa, 0xff5a, 0xff5f, 0xb5ad, 0x8000, 0xffff,
	0x801f, 0x81ff, 0x83ff, 0x83f0, 0x83e0, 0xbe00, 0xfc00, 0xfc0f, 0xfe5f, 0x82da, 0x8057, 0x804b, 0xb5ad, 0x8000, 0xffff,
	0xb242, 0xa9e1, 0x9e22, 0x9a66, 0xa699, 0x9e59, 0xa637, 0x9a3a, 0xa5d5, 0x9971, 0x950d, 0xffb0, 0xf726, 0xe280, 0xffff,
	0xf37a, 0xef36, 0xf7bc, 0xfbde, 0xbdd0, 0xb632, 0xb1f0, 0xae13, 0xda6e, 0x94bf, 0x83ff, 0xfc92, 0xde60, 0x8000, 0xffff,
	0xffff, 0xf7be, 0xef7c, 0xe73a, 0xdad8, 0xd296, 0xca54, 0xc213, 0xb5b1, 0xad6f, 0xa52d, 0x98cb, 0x9089, 0x8848, 0x8006,
	0xffff, 0xf7bd, 0xef7b, 0xe739, 0xdad6, 0xd294, 0xca52, 0xc210, 0xb5ad, 0xad6b, 0xa529, 0x98c6, 0x9084, 0x8842, 0x8000,
	0xbe3f, 0x801f, 0x81ff, 0x83ff, 0x8200, 0x83e0, 0xfc00, 0xfe60, 0xfc1a, 0xfdbf, 0x8013, 0x825f, 0xcaff, 0x8000, 0xffff
};

Image CoreUtils::patternimage(std::unique_ptr<PatternImage> &img, u16 paletteOffset) {
	if (!img) return { 0, 0, {}, {}, 0 };
	Image image = { 32, 32, std::vector<u8>(32 * 32), std::vector<u16>(15), paletteOffset };

	/* Get bitmap data from the Pattern Image. */
	for (int i = 0; i < 0x200; i++) {
		image.bitmap.data()[i * 2] = std::max<u8>(0, img->getPixel(i).left - 1); // Left pixel.
		image.bitmap.data()[i * 2 + 1] = std::max<u8>(0, img->getPixel(i).right - 1); // Right pixel.
	}

	/* Get Palette colors from the Pattern Image. */
	for (int i = 0; i < 15; i++) image.palette.data()[i] = PatternPalette[(img->getWWPaletteIndex() * 15) + i];

	return image;
}