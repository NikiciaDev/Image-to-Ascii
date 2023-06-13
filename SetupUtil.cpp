#include "SetupUtil.h"

namespace sul {
	bool isValidPath(const std::string path) {
		if ("png" != path.substr(path.length() - 3)) return false;
		std::fstream file(path);
		bool b = file.is_open();
		file.close();
		return b;
	}

	bool setup(std::string& pngPath, short& brightnessCalculationAlgorithm,
		double& roundingPercision, bool& useReversedAsciiTable, bool& copyToClipboard, short& pixelsPerPixel, bool& printToConsole) {
		std::string tempInput;
		char* end = nullptr;

		std::cout << "[ITA] Please input the path to the PNG you wish to convert.\n";
		std::cin >> pngPath;
		if (!sul::isValidPath(pngPath)) {
			std::cout << "[ITA] Path seems to be invalid!\n";
			return false;
		}

		std::cout << "[ITA] Please input the desired brightness calculation algorithm. (0 - 2)\n";
		std::cin >> brightnessCalculationAlgorithm;
		if (brightnessCalculationAlgorithm < 0 || brightnessCalculationAlgorithm > 3) {
			std::cout << "[ITA] Invalid brightness calculation algorithm!\n";
			return false;
		}

		std::cout << "[ITA] Please specify the rounding percision. (-1 = no rounding, 0.001 = round to thrid decimal)\n";
		std::cin >> tempInput;
		roundingPercision = strtod(tempInput.c_str(), &end);
		bool b = end != tempInput.c_str() && *end == '\0' && roundingPercision != HUGE_VAL;
		if (!b) {
			std::wcout << "[ITA] Please enter a valid percision value!\n";
			return false;
		}

		std::cout << "[ITA] What should the resolution divisor be? (-1 = no divisor)\n";
		std::cin >> pixelsPerPixel;
		if (pixelsPerPixel != -1 && (pixelsPerPixel < 4 || pixelsPerPixel % 2 != 0)) {
			std::cout << "[ITA] Invalid divisor!\n";
			return false;
		}

		std::cout << "[ITA] Would you like to use a brightness reversed ascii table? (Y/N)\n";
		std::cin >> tempInput;
		if (tempInput != "y" && tempInput != "Y" && tempInput != "n" && tempInput != "N") {
			std::cout << "[ITA] Please either input \"Y\" or \"N\"!\n";
			return false;
		}
		useReversedAsciiTable = (tempInput == "y" || tempInput == "Y");

		std::cout << "[ITA] Would you like to copy the string to your clipboard? (Y/N)\n";
		std::cin >> tempInput;
		if (tempInput != "y" && tempInput != "Y" && tempInput != "n" && tempInput != "N") {
			std::cout << "[ITA] Please either input \"Y\" or \"N\"!\n";
			return false;
		}
		copyToClipboard = (tempInput == "y" || tempInput == "Y");

		std::cout << "[ITA] Would you like to print it to the console? (Y/N)\n";
		std::cin >> tempInput;
		if (tempInput != "y" && tempInput != "Y" && tempInput != "n" && tempInput != "N") {
			std::cout << "[ITA] Please either input \"Y\" or \"N\"!\n";
			return false;
		}
		printToConsole = (tempInput == "y" || tempInput == "Y");

		return true;
	}
}