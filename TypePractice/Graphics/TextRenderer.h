#pragma once
#include "../Dependencies/glm/glm/glm.hpp"
#include "../Dependencies/glm/glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <GLFW/glfw3.h>
#include <map>

extern int windowWidth;
extern int windowHeight;

struct Character
{
	unsigned int textureID;
	unsigned int advance;

	glm::ivec2 size;
	glm::ivec2 bearing;
};

static std::map<char, Character> characters;

class TextRenderer
{
private:
	Shader* m_shader;

	FT_Library m_ft;
	FT_Face    m_face;

	std::string m_font = "Fonts/consola.ttf";

	unsigned int m_VAO;
	unsigned int m_VBO;


public:
	TextRenderer();

	void loadFont(std::string path = "");
	void renderText(std::string text, float x, float y, float scale = 1.0f, glm::vec4 color = glm::vec4(1.0f));

	~TextRenderer();
};

