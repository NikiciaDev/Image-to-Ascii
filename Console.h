#pragma once
#include <windows.h>
#include <string>

class Console {
private:
	const unsigned int width, height;
	unsigned int positionInBuffer;
	wchar_t* buffer;
	DWORD dwBytesWritten;
	HANDLE hConsole;

public:
	Console(const unsigned int width, const unsigned int height);

	// Activates the console object.
	void setActiveScreen();

	// Pushes a string onto the buffer.
	void pushOntoBuffer(const std::string& string);

	// Flushes the buffer to the console at the given coordinates.
	void flushBuffer(const COORD coord);

	// Pushes the given string onto the buffer and flushes it.
	void pushAndPrint(const std::string& string, const COORD coord);

	// Prints a string to the console at the given coordinates using a new buffer.
	void print(const std::string& string, const COORD coord);
};