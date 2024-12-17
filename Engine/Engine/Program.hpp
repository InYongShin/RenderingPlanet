#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "GLTools.hpp"

#include <iostream>

class Program
{
private:
	GLuint programID = 0;
	GLuint vertexID = 0;
	GLuint fragmentID = 0;
	GLuint geometryID = 0;
	GLuint tessControlID = 0;
	GLuint tessEvaluateID = 0;

	void printInfoProgramLog(GLuint obj);
	void printInfoShaderLog(GLuint obj);

public:
	void use() const;

	inline bool isUsable() const { return programID > 0; }

	void loadShaders(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr,
					 const char* tessControlPath = nullptr, const char* tessEvaluatePath = nullptr);

	void clear();

	Program() {}
	Program(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr,
		const char* tessControlPath = nullptr, const char* tessEvaluatePath = nullptr)
	{
		loadShaders(vertexPath, fragmentPath, geometryPath, tessControlPath, tessEvaluatePath);
	}
	virtual ~Program() { clear(); }

	void setUniform(const std::string& name, float v) const {
		glUniform1f(glGetUniformLocation(programID, name.c_str()), v);
	}
	void setUniform(const std::string& name, int v) const {
		glUniform1i(glGetUniformLocation(programID, name.c_str()), v);
	}
	void setUniform(const std::string& name, const glm::vec2& v) const {
		glUniform2f(glGetUniformLocation(programID, name.c_str()), v.x, v.y);
	}
	void setUniform(const std::string& name, const glm::vec3& v) const {
		glUniform3f(glGetUniformLocation(programID, name.c_str()), v.x, v.y, v.z);
	}
	void setUniform(const std::string& name, const glm::vec4& v) const {
		glUniform4f(glGetUniformLocation(programID, name.c_str()), v.x, v.y, v.z, v.w);
	}
	void setUniform(const std::string& name, const glm::mat3& v) const {
		glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, value_ptr(v));
	}
	void setUniform(const std::string& name, const glm::mat4& v) const {
		glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, value_ptr(v));
	}
	void setUniform(const std::string& name, const float* v, uint32_t count) const {
		glUniform1fv(glGetUniformLocation(programID, name.c_str()), count, v);
	}
	void setUniform(const std::string& name, const int* v, uint32_t count) const {
		glUniform1iv(glGetUniformLocation(programID, name.c_str()), count, v);
	}
	void setUniform(const std::string& name, const glm::vec2* v, uint32_t count) const {
		glUniform2fv(glGetUniformLocation(programID, name.c_str()), count, (float*)v);
	}
	void setUniform(const std::string& name, const glm::vec3* v, uint32_t count) const {
		glUniform3fv(glGetUniformLocation(programID, name.c_str()), count, (float*)v);
	}
	void setUniform(const std::string& name, const glm::vec4* v, uint32_t count) const {
		glUniform4fv(glGetUniformLocation(programID, name.c_str()), count, (float*)v);
	}
	void setUniform(const std::string& name, const glm::mat3* v, uint32_t count) const {
		glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), count, GL_FALSE, (float*)v);
	}
	void setUniform(const std::string& name, const glm::mat4* v, uint32_t count) const {
		glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), count, GL_FALSE, (float*)v);
	}

};


#endif /* PROGRAM_HPP */