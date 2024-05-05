#ifndef GLTOOLS_HPP
#define GLTOOLS_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

inline void glErr(const std::string& message) {
	GLint err = glGetError();
	if (err != GL_NO_ERROR) {
		printf("%08X ", err);
		std::cerr << "GL Error: " << message << std::endl;
	}
}


#endif /* GLTOOLS_HPP */
