#ifndef SCENE_HPP
#define SCENE_HPP

#include "GLTools.hpp"
#include "Model.hpp"
#include "Planet.hpp"

#include <vector>
#include <iostream>

class Scene
{
private:

protected:
	std::string _title = "";

	glm::vec4 backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	virtual void initialize() = 0;

public:

	inline std::string getTitle() const { return this->_title; }

	inline void setBackgroundColor(const glm::vec4& color) { this->backgroundColor = color; }
	inline glm::vec4 getBackgroundColor() const { return this->backgroundColor; }

	virtual void update() = 0;
	virtual void drawContents() const = 0;

	void clear();

	Scene() {}
	Scene(const std::string& title) : _title(title) {}
	virtual ~Scene() { clear(); }
};


#endif /* SCENE_HPP */
