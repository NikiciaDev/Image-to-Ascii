#include "PNG.h"
#include <iostream>

PNG::~PNG() {
	delete pixels;
}

PNG::PNG(const char* path) {
	file = std::ifstream(path);

	unsigned char buf[8];
	file.seekg(16);
	file.read(reinterpret_cast<char*>(&buf), 8);
	width = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + (buf[3] << 0);
	height = (buf[4] << 24) + (buf[5] << 16) + (buf[6] << 8) + (buf[7] << 0);

	sqPixels = width * height;

	//pixels = new unsigned char[((long long) sqPixels) * 3];
	//file.read((char*) pixels, ((long long) sqPixels) * 3);

	file.close();
}