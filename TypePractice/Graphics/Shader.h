#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include "../Dependencies/glm/glm/glm.hpp"

class Shader
{
private:
	unsigned int m_vert;
	unsigned int m_frag;
	unsigned int m_program;

	char m_shaderlog[512];

public:
	Shader(std::string vertPath, std::string fragPath);

	std::string loadSource(std::string path);

	GLuint* get();

	void bind();

	void setMat4(std::string name, glm::mat4 value);
	void setVec4(std::string name, glm::vec4 value);
};

