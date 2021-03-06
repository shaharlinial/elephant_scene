#include "texelLoader.h"
#include <iostream>

TexelLoader::TexelLoader() {};

unsigned char* TexelLoader::loadTexel(std::string filePath) {
	int i;
	FILE* f = nullptr;

	errno_t status = fopen_s(&f, filePath.c_str(), "rb");
	if (status != 0) {
		return nullptr;
	}
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

											   // extract image height and width from header
	width = *(int*)&info[18];
	height = *(int*)&info[22];

	int size = 3 * width * height;
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	for (i = 0; i < size; i += 3)
	{
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}

	texel = data;
}

GLsizei TexelLoader::getWidth() {
	return width;
}
GLsizei TexelLoader::getHeight() {
	return height;
}