#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLTools.hpp"
#include "SceneManager.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

#include <vector>
#include <string>


class Window
{
private:
	std::string _title = "";
	int _width = 0;
	int _height = 0;

	GLFWwindow* GLwindow = nullptr;

	glm::vec2 mousePt = glm::vec2(0.f);

	bool isCreated = false;
	bool isInitialized = false;

	float _moveSpeed = 0.5f;

private:
	bool initGL();

public:

	void setCallbackFunc()
	{
		glfwSetWindowUserPointer(this->GLwindow, this);
		glfwSetMouseButtonCallback(this->GLwindow, s_buttonCallback);
		glfwSetScrollCallback(this->GLwindow, s_scrollCallback);
		glfwSetCursorPosCallback(this->GLwindow, s_cursorCallback);
		glfwSetKeyCallback(this->GLwindow, s_keyCallback);
	}

	void cursorCallback(const glm::vec2& pt)
	{
		if( glfwGetMouseButton(this->GLwindow, GLFW_MOUSE_BUTTON_1))
		{
			glm::vec2 offset = pt - this->mousePt;

			Camera& camera = SceneManager::getInstance()->getCamera();
			
			float yaw = camera.getYaw() + offset.x;
			camera.setYaw(yaw);

			float pitch = camera.getPitch() - offset.y;
			if (pitch >  89.0f) pitch = 89.0f;
			if (pitch < -89.0f) pitch = -89.0f;
			camera.setPitch(pitch);

			glm::vec3 direction = glm::vec3(0.f, 0.f, 1.f);
			direction.x = cos(glm::radians(camera.getYaw())) * cos(glm::radians(camera.getPitch()));
			direction.y = sin(glm::radians(camera.getPitch()));
			direction.z = sin(glm::radians(camera.getYaw())) * cos(glm::radians(camera.getPitch()));
			camera.setCenter(camera.getPosition() + glm::normalize(direction));
		}
		this->mousePt = pt;
	}
	void buttonCallback(int button, int action, int mods)
	{
		double x, y;
		glfwGetCursorPos(this->GLwindow, &x, &y);
		this->mousePt = glm::vec2(x,y);

		// if( action == GLFW_PRESS ) pushFunc( button );
		// else if( action == GLFW_RELEASE) pullFunc( button );
	}
	void scrollCallback(double x, double y) {
		/*glm::vec3 d = viewers[0]->camera.position - viewers[0]->camera.center;
		float dist = glm::length(d);
		dist *= powf(0.99f,float(y));
		viewers[0]->camera.position = viewers[0]->camera.center + dist*normalize(d);*/

		Camera& camera = SceneManager::getInstance()->getCamera();
		float fov = camera.getFov() * powf(.99f, float(y));
		camera.setFov(fov);
	}
	void keyCallback(int key, int scan, int action, int mods)
	{
		if (action == GLFW_PRESS) std::cout << key << std::endl;
		Camera& camera = SceneManager::getInstance()->getCamera();
		if (key == 87) // w
		{
			glm::vec3 frontDir = glm::normalize(camera.getCenter() - camera.getPosition());
			
			glm::vec3 position = camera.getPosition() + frontDir * glm::vec3(_moveSpeed);
			camera.setPosition(position);

			glm::vec3 center = camera.getCenter() + frontDir * glm::vec3(_moveSpeed);
			camera.setCenter(center);
		}
		else if (key == 83) // s
		{
			glm::vec3 frontDir = glm::normalize(camera.getCenter() - camera.getPosition());

			glm::vec3 position = camera.getPosition() - frontDir * glm::vec3(_moveSpeed);
			camera.setPosition(position);

			glm::vec3 center = camera.getCenter() - frontDir * glm::vec3(_moveSpeed);
			camera.setCenter(center);
		}
		else if (key == 65) // a
		{
			glm::vec3 frontDir = glm::normalize(camera.getCenter() - camera.getPosition());
			glm::vec3 up = camera.getUpVector();
			glm::vec3 leftDir = glm::cross(up, frontDir);

			glm::vec3 position = camera.getPosition() + leftDir * glm::vec3(_moveSpeed);
			camera.setPosition(position);
			
			glm::vec3 center = camera.getCenter() + leftDir * glm::vec3(_moveSpeed);
			camera.setCenter(center);
		}
		else if (key == 68) // d
		{
			glm::vec3 frontDir = glm::normalize(camera.getCenter() - camera.getPosition());
			glm::vec3 up = camera.getUpVector();
			glm::vec3 rightDir = glm::cross(frontDir, up);
			
			glm::vec3 position = camera.getPosition() + rightDir * glm::vec3(_moveSpeed);
			camera.setPosition(position);
			
			glm::vec3 center = camera.getCenter() + rightDir * glm::vec3(_moveSpeed);
			camera.setCenter(center);
		}
		else if (key == 69) // e
		{
			glm::vec3 position = camera.getPosition() + (camera.getUpVector() * glm::vec3(_moveSpeed));
			camera.setPosition(position);

			glm::vec3 center = camera.getCenter() + (camera.getUpVector() * glm::vec3(_moveSpeed));
			camera.setCenter(center);
		}
		else if (key == 81) // q
		{
			glm::vec3 position = camera.getPosition() + (camera.getUpVector() * glm::vec3(-_moveSpeed));
			camera.setPosition(position);

			glm::vec3 center = camera.getCenter() + (camera.getUpVector() * glm::vec3(-_moveSpeed));
			camera.setCenter(center);
		}
	}
	static void s_cursorCallback(GLFWwindow* window, double x, double y)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->cursorCallback(glm::vec2(x,y));
	}
	static void s_buttonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->buttonCallback(button, action, mods);
	}
	static void s_scrollCallback(GLFWwindow* window, double x, double y)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->scrollCallback(x,y);
	}
	static void s_keyCallback(GLFWwindow* window, int key, int scan, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->keyCallback(key, scan, action, mods);
	}

	inline GLFWwindow* getWindow() const { return this->GLwindow; }
	inline void setWindow(GLFWwindow* window) { this->GLwindow = window; }

	inline std::string getTitle() const { return this->_title; }
	inline int getWidth() const { return this->_width; }
	inline int getHeight() const { return this->_height; }

	bool isNeedCreation() const { return !this->isCreated; }
	bool isNeedInitialization() const { return !this->isInitialized; }

	bool createWindow();
	void display() const;

	void clear();

	Window() {}
	Window(const std::string& title, int width, int height)
		: _title(title), _width(width), _height(height) 
	{
		setCallbackFunc();
	}

	virtual ~Window() { clear(); }
};

#endif /* WINDOW_HPP */
