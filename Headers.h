#ifndef HEADERS_H
#define HEADERS_H

// Link statically with GLEW
#define GLEW_STATIC

// Remove compilation internal GLM errors
#define GLM_FORCE_RADIANS

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#ifdef WIN32
	// Include Windows
	#include <GL/glew.h>
#elif __APPLE__
	// Include Mac
	#define GL3_PROTOTYPES 1
	#include <OpenGL/gl3.h>
#else
	// Include UNIX/Linux
	#define GL3_PROTOTYPES 1
	#include "GL/glew.h"
#endif

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define PI 3.141591


#endif //HEADERS_H
