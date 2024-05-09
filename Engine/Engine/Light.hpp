#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "GLTools.hpp"


class Light
{
private:
	glm::vec3 _position = glm::vec3(0);

public:

	inline glm::vec3 getPosition() const { return this->_position; }
	inline void setPosition(const glm::vec3& position) { this->_position = position; }

	Light() {}
	Light(const glm::vec3& position) : _position(position) {}
	virtual ~Light() {}
};


#endif /* LIGHT_HPP */
