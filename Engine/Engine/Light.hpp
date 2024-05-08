#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "GLTools.hpp"


class Light
{
private:
	glm::vec3 position = glm::vec3(0);

public:

	Light() {}
	virtual ~Light() {}
};


#endif /* LIGHT_HPP */
