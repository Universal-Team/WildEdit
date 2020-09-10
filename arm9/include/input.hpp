#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <string>

namespace Input {
	std::string getLine2(std::string Text, std::string currentString = "", bool showPointer = true, bool redrawScreen = true);
	std::string getLine(std::string Text, unsigned maxLength, std::string currentString = "", bool showPointer = true, bool redrawScreen = true);

	int getInt2(std::string Text, int currentValue = 0, bool showPointer = true, bool redrawScreen = true);
	int getInt(std::string Text, unsigned max, int currentValue = 0, bool showPointer = true, bool redrawScreen = true);
}

#endif