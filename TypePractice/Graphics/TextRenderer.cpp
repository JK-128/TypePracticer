#include "TextRenderer.h"

int windowWidth;
int windowHeight;

TextRenderer::TextRenderer()
{
	if (FT_Init_FreeType(&m_ft))
	{
		std::cout << "Could not initialise freetype.\n";
		return;
	}

	loadFont();

	m_shader = new Shader("Shaders/textVert.glsl", "Shaders/textFrag.glsl");
	m_shader->bind();

	glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);

	m_shader->setMat4("projection", projection);

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TextRenderer::loadFont(std::string path)
{
	if (path == "") path = m_font;

	if (FT_New_Face(m_ft, path.c_str(), 0, &m_face))
	{
		std::cout << "Could not load font.\n";
		return;
	}

	FT_Set_Pixel_Sizes(m_face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 0; c < 128; c++) 
	{
		if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
		{
			std::cout << "Failed to load glyph: " << c << "\n";
			continue;
		}

		unsigned int texture;

		auto bitmap = m_face->glyph->bitmap;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bitmap.width, bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			m_face->glyph->advance.x,
			glm::ivec2(bitmap.width, bitmap.rows),
			glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top)
		};

		characters.insert(std::pair<char, Character>(c, character));
	}

	FT_Done_Face(m_face);
	FT_Done_FreeType(m_ft);
}

void TextRenderer::renderText(std::string text, float x, float y, float scale, glm::vec4 color)
{
	m_shader->bind();
	m_shader->setVec4("textColor", color);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_VAO);
	glDepthFunc(GL_ALWAYS);

	std::string::const_iterator c;

	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];

		float xpos = x + ch.bearing.x * scale;
		float ypos = y - (ch.size.y - ch.bearing.y) * scale;
		float w    = ch.size.x * scale;
		float h    = ch.size.y * scale;

		float vertices[6][4] = {
			{xpos    , ypos + h, 0.0f, 0.0f},
			{xpos    , ypos    , 0.0f, 1.0f},
			{xpos + w, ypos    , 1.0f, 1.0f},
			{xpos    , ypos + h, 0.0f, 0.0f},
			{xpos + w, ypos    , 1.0f, 1.0f},
			{xpos + w, ypos + h, 1.0f, 0.0f}
		};

		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.advance >> 6) * scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDepthFunc(GL_LESS);
}

TextRenderer::~TextRenderer()
{
	delete m_shader;
}