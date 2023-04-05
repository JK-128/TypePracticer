#include "Window.h"

std::vector<int> keyActions;

Window::Window(int width, int height, std::string title)
{
	m_width  = width;
	m_height = height;
	m_title  = title;

	if (!glfwInit())
		return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), 0, 0);

	glfwMakeContextCurrent(m_window);

	glfwSetKeyCallback(m_window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_STENCIL_TEST);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_exists = true;
}

bool Window::exists()
{
	return m_exists;
}


void Window::poll()
{
	glfwPollEvents();

	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		close();
	if (glfwWindowShouldClose(m_window))
		m_exists = false;
}

void Window::swap()
{
	glfwSwapBuffers(m_window);
}

void Window::close()
{
	glfwSetWindowShouldClose(m_window, true);
}

void Window::clear()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::draw()
{
	clear();
	swap();
	poll();
}

bool Window::keyPressed(int key)
{
	return (glfwGetKey(m_window, key) == GLFW_PRESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		keyActions.push_back(key);
}