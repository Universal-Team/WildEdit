#include "lang.hpp"
#include "stringDB.hpp"

nlohmann::json appJson;
/* Player. */
std::vector<std::string> g_faceType, g_hairColor, g_hairStyle;
/* Villager. */
std::vector<std::string> g_personality;
/* House / Room stuff. */
std::vector<std::string> g_roomnames, g_houseSizes;

void loadToVector(std::string path, std::vector<std::string> &vec) {
	char *line = nullptr;
	size_t len = 0;
	vec.clear();

	FILE *in = fopen(path.c_str(), "r");

	if (in) {
		while(__getline(&line, &len, in) != -1) {
			if (line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
			vec.push_back(line);
		}

		fclose(in);
	}
}

std::string Lang::get(const std::string &key) {
	if (!appJson.contains(key)) return "";

	return appJson.at(key).get_ref<const std::string&>();
}

const std::string langs[] = { "de", "en", "es", "fr", "it", "lt", "pt", "jp" };

void Lang::load(int lang) {
	loadToVector("nitro:/lang/strings/facetype.txt", g_faceType);
	loadToVector("nitro:/lang/strings/haircolor.txt", g_hairColor);
	loadToVector("nitro:/lang/strings/hairstyle.txt", g_hairStyle);
	loadToVector("nitro:/lang/strings/personalities.txt", g_personality);
	loadToVector("nitro:/lang/strings/rooms.txt", g_roomnames);
	loadToVector("nitro:/lang/strings/houseupgrades.txt", g_houseSizes);

	/* Load app strings. */
	FILE *file = fopen(("nitro:/lang/"+langs[lang]+"/app.json").c_str(), "rt");

	if (file) {
		appJson = nlohmann::json::parse(file, nullptr, false);
		fclose(file);
	}

	StringDB::LoadItemDatabase();
	StringDB::LoadVillagerDatabase();
}