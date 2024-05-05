
#include "Program.hpp"
#include "StringTool.hpp"

void Program::printInfoProgramLog(GLuint obj)
{
	int infologLength = 0, charsWritten = 0;
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength <= 0) return;
	char* infoLog = new char[infologLength];
	glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
	std::cerr << "Program Info:" << std::endl;
	std::cerr << infoLog << std::endl;
	delete[] infoLog;
}

void Program::printInfoShaderLog(GLuint obj)
{
	int infologLength = 0, charsWritten = 0;
	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength <= 0) return;
	char* infoLog = new char[infologLength];
	glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
	std::cerr << "Shader Info:" << std::endl;
	std::cerr << infoLog << std::endl;
	delete[] infoLog;
}

void Program::loadShaders(const char* vertexPath, const char* fragmentPath, const char* geometryPath, const char* tessControlPath, const char* tessEvaluatePath)
{
	std::cout << "Loading: ";

	programID = glCreateProgram();

	// Vertex Shader
	std::cout << getFilenameFromAbsPath(vertexPath) << ", ";
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexCode = loadText(vertexPath);
	const char* vCode = vertexCode.c_str();
	glShaderSource(vertexID, 1, &vCode, NULL);
	glCompileShader(vertexID);
	printInfoShaderLog(vertexID);
	glAttachShader(programID, vertexID);

	// Tessellation Control Shader
	if (tessControlPath != nullptr) {
		std::cout << getFilenameFromAbsPath(tessControlPath) << ", ";
		tessControlID = glCreateShader(GL_TESS_CONTROL_SHADER);
		std::string tessControlCode = loadText(tessControlPath);
		const char* tcCode = tessControlCode.c_str();
		glShaderSource(tessControlID, 1, &tcCode, NULL);
		glCompileShader(tessControlID);
		printInfoShaderLog(tessControlID);
		glAttachShader(programID, tessControlID);
	}

	// Tessellation Evaluate Shader
	if (tessEvaluatePath != nullptr) {
		std::cout << getFilenameFromAbsPath(tessEvaluatePath) << ", ";
		tessEvaluateID = glCreateShader(GL_TESS_EVALUATION_SHADER);
		std::string tessEvaluateCode = loadText(tessEvaluatePath);
		const char* teCode = tessEvaluateCode.c_str();
		glShaderSource(tessEvaluateID, 1, &teCode, NULL);
		glCompileShader(tessEvaluateID);
		printInfoShaderLog(tessEvaluateID);
		glAttachShader(programID, tessEvaluateID);
	}

	// Geometry Shader
	if (geometryPath != nullptr) {
		std::cout << getFilenameFromAbsPath(geometryPath) << ", ";
		geometryID = glCreateShader(GL_GEOMETRY_SHADER);
		std::string geometryCode = loadText(geometryPath);
		const char* gCode = geometryCode.c_str();
		glShaderSource(geometryID, 1, &gCode, NULL);
		glCompileShader(geometryID);
		printInfoShaderLog(geometryID);
		glAttachShader(programID, geometryID);
	}

	// Fragment Shader
	std::cout << getFilenameFromAbsPath(fragmentPath) << ", ";
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentCode = loadText(fragmentPath);
	const char* fCode = fragmentCode.c_str();
	glShaderSource(fragmentID, 1, &fCode, NULL);
	glCompileShader(fragmentID);
	printInfoShaderLog(fragmentID);
	glAttachShader(programID, fragmentID);

	// Link Program
	glLinkProgram(programID);
	glUseProgram(programID);
	printInfoProgramLog(programID);
}
