#pragma once
#include <vector>
#include <string>
#include "mi_opengl_global.h"

MI_OPENGL_EXPORT unsigned int loadImageToGPU(int textureSlot, const char* fileName);

MI_OPENGL_EXPORT unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);