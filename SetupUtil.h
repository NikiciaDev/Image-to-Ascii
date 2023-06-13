#pragma once
#include <fstream>
#include <string>
#include <iostream>

namespace sul {
	bool isValidPath(std::string path);

	bool setup(std::string& pngPath, short& brightnessCalculationAlgorithm,
		double& roundingPercision, bool& useReversedAsciiTable, bool& copyToClipboard);
}