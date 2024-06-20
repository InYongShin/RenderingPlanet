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
	float yaw = -89.f, roll = 0, pitch = 0;
	float zNear = 0.1f;
	float zFar = 1000.f;
	glm::vec2 viewport = glm::vec2(0.f);

public:

	inline void setPosition(const glm::vec3& position) { this->position = position; }
	inline glm::vec3 getPosition() const { return this->position; }
	inline void setCenter(const glm::vec3& center) { this->center = center; }
	inline glm::vec3 getCenter() const { return this->center; }
	inline glm::vec3 getUpVector() const { return this->upVector; }
	inline float getFov() const { return this->fov; }
	inline void setFov(float fov) { this->fov = fov; }
	inline float getYaw() const { return this->yaw; }
	inline void setYaw(float yaw) { this->yaw = yaw; }
	inline float getRoll() const { return this->roll; }
	inline void setRoll(float roll) { this->roll = roll; }
	inline float getPitch() const { return this->pitch; }
	inline void setPitch(float pitch) { this->pitch = pitch; }
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
