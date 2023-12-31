#include "SetupUtil.h"

namespace sul {
	bool isValidPath(const std::string path) {
		if ("png" != path.substr(path.length() - 3)) return false;
		std::fstream file(path);
		bool b = file.is_open();
		file.close();
		return b;
	}

	bool isNumber(const std::string string) {
		if (string.size() == 0) return false;
		bool hadDot = false;
		unsigned short s = 0;
		for (char c : string) {
			if (std::isdigit(c) || (s == 0 && (c == '-' || c == '+')) || c == '.' && !hadDot) {
				if (c == '.') hadDot = true;
				s++;
				continue;
			}
			return false;
		}
		return true;
	}

	bool setup(std::string& pngPath, short& brightnessCalculationAlgorithm,
		double& roundingPercision, bool& useReversedAsciiTable, bool& copyToClipboard, short& pixelsPerPixel, bool& printToConsole) {
		std::string tempInput;
		char* end = nullptr;

		std::cout << "[ITA] Please input the path to the PNG you wish to convert.\n";
		std::cin >> pngPath;
		if (!sul::isValidPath(pngPath)) {
			std::cout << "[ITA] Path seems to be invalid! Spaces are not allowed!\n";
			return false;
		}

		std::cout << "[ITA] Please input the desired brightness calculation algorithm. (0 - 2)\n";
		std::cin >> tempInput;
		if (isNumber(tempInput)) brightnessCalculationAlgorithm = std::stoi(tempInput);
		if (!isNumber(tempInput) || brightnessCalculationAlgorithm < 0 || brightnessCalculationAlgorithm > 3) {
			std::cout << "[ITA] Invalid brightness calculation algorithm!\n";
			return false;
		}

		std::cout << "[ITA] Please specify the rounding percision. (-1 = no rounding, 0.001 = round to thrid decimal)\n";
		std::cin >> tempInput;
		if (isNumber(tempInput)) {
			roundingPercision = std::stold(tempInput);
		}
		if(!isNumber(tempInput) || (roundingPercision != -1 && roundingPercision < 0)){
			std::wcout << "[ITA] Please enter a valid percision value!\n";
			return false;
		}

		std::cout << "[ITA] What should the resolution divisor be? A common divisor is required for width and height! (-1 = no divisor)\n";
		std::cin >> tempInput;
		if (isNumber(tempInput)) pixelsPerPixel = std::stoi(tempInput);
		if (!isNumber(tempInput) || pixelsPerPixel != -1 && (pixelsPerPixel < 4 || pixelsPerPixel % 2 != 0)) {
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
		std::cout << "\n";

		return true;
	}
}