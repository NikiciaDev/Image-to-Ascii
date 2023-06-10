#include <windows.h>
#include "Console.h"

int main() {
	Console console(120, 40);
	console.setActiveScreen();

	while (true) {
		console.pushAndPrint("Hello Word!", {0, 0});
	}
	
	return 0;
}