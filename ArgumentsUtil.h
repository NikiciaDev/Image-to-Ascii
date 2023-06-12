#pragma once
#include <fstream>
#include <string>

namespace aul {
	bool isValidPath(std::string path);

	void parse(const int argc, char* argv[], std::string& pngPath, short& brightnessCalculationAlgorithm, bool& useReversedAsciiTable);
}