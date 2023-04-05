#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>

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
};

