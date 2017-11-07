#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../Dependencies/glew/glew.h"

namespace Rendering {
	// Load a .BMP file using our custom loader
	GLuint loadBMP_custom(const char * imagepath);

	// Load a .DDS file using GLFW's own loader
	GLuint loadDDS(const char * imagepath);

}

#endif