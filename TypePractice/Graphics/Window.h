#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

extern std::vector<int> keyActions;

class Window
{
private:
	GLFWwindow* m_window;

	bool m_exists = false;

	int m_width;
	int m_height;

	std::string m_title;

public:
	Window(int width, int height, std::string title);
	
	bool exists();
	bool keyPressed(int key);

	void poll();
	void swap();
	void close();
	void clear();
	void draw();
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);