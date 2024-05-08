#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GLTools.hpp"


class Camera
{
private:
	glm::vec3 position = glm::vec3(0.f);
	glm::vec3 center = glm::vec3(0.f);

	glm::vec3 upVector = glm::vec3(0.f,1.f,0.f);

public:


	Camera() {}
	virtual ~Camera() {}
};


#endif /* CAMERA_HPP */
