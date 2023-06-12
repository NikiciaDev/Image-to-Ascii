#include "SetupUtil.h"

namespace sul {
	bool isValidPath(const std::string path) {
		if ("png" != path.substr(path.length() - 3)) return false;
		std::fstream file(path);
		bool b = file.is_open();
		file.close();
		return b;
	}
}