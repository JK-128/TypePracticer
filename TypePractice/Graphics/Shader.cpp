#include "Shader.h"

Shader::Shader(std::string vertPath, std::string fragPath)
{
	int success;

	const char* vertString = loadSource(vertPath).c_str();
	const char* fragString = loadSource(fragPath).c_str();

	m_vert = glCreateShader(GL_VERTEX_SHADER);
	m_frag = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_vert, 1, &vertString, NULL);
	glShaderSource(m_frag, 1, &fragString, NULL);

	glCompileShader(m_vert);
	glGetShaderiv(m_vert, GL_COMPILE_STATUS, &success);

	if (!success) std::cout << "Error compiling vertex shader.\n";

	glCompileShader(m_frag);
	glGetShaderiv(m_frag, GL_COMPILE_STATUS, &success);

	if (!success) std::cout << "Error compiling fragment shader.\n";

	m_program = glCreateProgram();

	glAttachShader(m_program, m_vert);
	glAttachShader(m_program, m_frag);

	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);

	if (!success) std::cout << "Error linking shaders.\n";

	glDeleteShader(m_vert);
	glDeleteShader(m_frag);
}

std::string Shader::loadSource(std::string path)
{
	std::fstream file;
	file.open(path, std::ios::in);

	std::string content;
	std::string line;

	while (std::getline(file, line))
		content += line + "\n";

	file.close();

	return content;
}

GLuint* Shader::get()
{
	return &m_program;
}

void Shader::bind()
{
	glUseProgram(m_program);
}