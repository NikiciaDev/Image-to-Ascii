#include "Console.h"

Console::~Console() {
	delete[] buffer;
}

Console::Console(const unsigned int width, const unsigned int height) : width(width), height(height), dwBytesWritten(0), positionInBuffer(0) {
	buffer = new wchar_t[((long long) width) * height];
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
}

void Console::setActiveScreen() {
	SetConsoleActiveScreenBuffer(hConsole);
}

void Console::pushOntoBuffer(const std::string& string) {
	for (int i = 0; i < width * height; i++) {
		if (i < string.size() && i + positionInBuffer < width * height) {
			buffer[positionInBuffer + i] = string[i];
			continue;
		}
		std::fill_n(buffer + positionInBuffer + i, width * height - positionInBuffer - i, 0);
		break;
	}
}

void Console::flushBuffer(const COORD coord) {
	WriteConsoleOutputCharacter(hConsole, buffer, width * height, coord, &dwBytesWritten);
	memset(buffer, 0, width * height);
	positionInBuffer = 0;
}

void Console::pushAndPrint(const std::string& string, const COORD coord) {
	pushOntoBuffer(string);
	flushBuffer(coord);
}

void Console::print(const std::string& string, const COORD coord) {
	wchar_t* charbuffer = new wchar_t[((long long) width) * height] { '\0' };

	for (int i = 0; i < width * height; i++) {
		if (i < string.size()) {
			charbuffer[i] = string[i];
			continue;
		}
		std::fill_n(charbuffer + i, width * height - i, 0);
		break;
	}

	WriteConsoleOutputCharacter(hConsole, charbuffer, width * height, coord, &dwBytesWritten);
	delete[] charbuffer;
}