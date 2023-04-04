#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	void poll();
	void swap();
	void close();
	void clear();
	void draw();
};

