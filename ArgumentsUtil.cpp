#include "ArgumentsUtil.h"
#include <iostream>

namespace aul {
	bool isValidPath(const std::string path) {
		if ("png" != path.substr(path.length() - 3)) return false;
		std::fstream file(path);
		bool b = file.is_open();
		file.close();
		return b;
	}

	void parse(const int argc, char* argv[], std::string& pngPath, short& brightnessCalculationAlgorithm, bool& useReversedAsciiTable) {
		bool hadPath = false;
		for (int i = 0; i < argc; i++) {
			std::string s = argv[i];
			if (!hadPath) {
				if (isValidPath(s)) {
					hadPath = true;
					pngPath = s;
				}
			}
			if (s.find("brightnessCalculationAlgorithm=") != std::string::npos) {
				brightnessCalculationAlgorithm = s[s.length() - 1] - '0';
			}else if (s.find("useReversedAsciiTable=") != std::string::npos) {
				useReversedAsciiTable = s[s.length() - 1] - '0';
			}
		}
		if (!hadPath) exit(-1);
	}
}