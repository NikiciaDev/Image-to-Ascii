#pragma once
#include <fstream>
#include <string>
#include <iostream>

namespace sul {
	bool isValidPath(const std::string path);

	bool isNumber(const std::string string);

	bool setup(std::string& pngPath, short& brightnessCalculationAlgorithm,
		double& roundingPercision, bool& useReversedAsciiTable, bool& copyToClipboard, short& pixelsPerPixel, bool& printToConsole);
}