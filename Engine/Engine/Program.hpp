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
};


#endif /* PROGRAM_HPP */