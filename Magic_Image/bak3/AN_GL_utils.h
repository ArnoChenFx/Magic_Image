#pragma once
#include <vector>
#include <string>

unsigned int loadImageToGPU(int textureSlot, const char* fileName);

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);