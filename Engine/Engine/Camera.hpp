#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GLTools.hpp"


class Camera
{
private:
	glm::vec3 position = glm::vec3(0.f);
	glm::vec3 center = glm::vec3(0.f);

	glm::vec3 upVector = glm::vec3(0.f,1.f,0.f);

	float fov = 45.f * glm::pi<float>() / 180.f;
	float zNear = 0.1f;
	float zFar = 1000.f;
	glm::vec2 viewport = glm::vec2(0.f);

public:

	inline void setPosition(const glm::vec3& position) { this->position = position; }
	inline void setViewport(const glm::vec2& viewport) { this->viewport = viewport; }

	glm::mat4 projMat() const {
		return glm::perspective(fov, viewport.x / viewport.y, zNear, zFar);
	}
	glm::mat4 viewMat() const {
		return glm::lookAt(position, center, upVector);
	}

	Camera() {}
	virtual ~Camera() {}
};


#endif /* CAMERA_HPP */
