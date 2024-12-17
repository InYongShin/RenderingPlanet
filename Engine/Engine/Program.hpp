#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "GLTools.hpp"

#include <map>
#include <variant>
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

	using UniformValue = std::variant<float, int, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4>;
	std::map<std::string, UniformValue> uniformMap;

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

    void setUniform(const std::string& name, float v) {
        uniformMap[name] = v;
    }
    void setUniform(const std::string& name, int v) {
        uniformMap[name] = v;
    }
    void setUniform(const std::string& name, const glm::vec2& v) {
        uniformMap[name] = v;
    }
    void setUniform(const std::string& name, const glm::vec3& v) {
        uniformMap[name] = v;
    }
    void setUniform(const std::string& name, const glm::vec4& v) {
        uniformMap[name] = v;
    }
    void setUniform(const std::string& name, const glm::mat3& v) {
        uniformMap[name] = v;
    }
    void setUniform(const std::string& name, const glm::mat4& v) {
        uniformMap[name] = v;
    }

    // TODO: Uniform Array
    // void setUniform(const std::string& name, const float* v, uint32_t count) {
    //     uniformMap[name] = std::vector<float>(v, v + count);
    // }
    // void setUniform(const std::string& name, const int* v, uint32_t count) {
    //     uniformMap[name] = std::vector<int>(v, v + count);
    // }
    // void setUniform(const std::string& name, const glm::vec2* v, uint32_t count) {
    //     uniformMap[name] = std::vector<glm::vec2>(v, v + count);
    // }
    // void setUniform(const std::string& name, const glm::vec3* v, uint32_t count) {
    //     uniformMap[name] = std::vector<glm::vec3>(v, v + count);
    // }
    // void setUniform(const std::string& name, const glm::vec4* v, uint32_t count) {
    //     uniformMap[name] = std::vector<glm::vec4>(v, v + count);
    // }
    // void setUniform(const std::string& name, const glm::mat3* v, uint32_t count) {
    //     uniformMap[name] = std::vector<glm::mat3>(v, v + count);
    // }
    // void setUniform(const std::string& name, const glm::mat4* v, uint32_t count) {
    //     uniformMap[name] = std::vector<glm::mat4>(v, v + count);
    // }

    void applyUniforms() const;

};


#endif /* PROGRAM_HPP */