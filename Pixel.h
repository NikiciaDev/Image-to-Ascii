#pragma once
#include <string>

class Pixel {
public:
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;

	Pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

	std::string toString();
};