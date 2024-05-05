#ifndef STRINGTOOL_HPP
#define STRINGTOOL_HPP

#include <string>
#include <iostream>
#include <fstream>

inline std::string backToFrontSlash(const std::string& path) {
	std::string result = path;
	for (size_t i = 0; i < result.length(); i++) {
		if (result[i] == '\\') result[i] = '/';
	}
	return result;
}

inline std::string getFilenameFromAbsPath(const std::string& absPath) {
	size_t slashPos = absPath.find_last_of('/');
	if (slashPos == std::string::npos) return absPath;
	if (slashPos == absPath.length()-1) return "";
	return absPath.substr(slashPos+1);
}

inline std::string loadText(const std::string& filename) {
	std::ifstream t(backToFrontSlash(filename));
	if (!t.is_open()) {
		std::cerr << "[ERROR] Text file: " << getFilenameFromAbsPath(filename) << " is not found\n";
		return "";
	}
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	return str;
}


#endif /* STRINGTOOL_HPP */
