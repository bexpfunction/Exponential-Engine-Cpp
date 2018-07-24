#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Prototype methods
//Window resize callback method
void GL_Framebuffer_Resize_Callback(GLFWwindow *wnd, int width, int height);
void ProcessInput(GLFWwindow *wnd);

int main() {

	//GLFW init and window settings
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create the window
	GLFWwindow *window = glfwCreateWindow(800, 600, "Exponential Engine", NULL, NULL);
	if (window == NULL) {
		std::cout << "Error!!! Failed to create GL window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Initialize GLAD for OpenGL pointers to call OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD!!!" << std::endl;
		return -1;
	}

	//Create the glViewport
	glViewport(0, 0, 800, 600);

	//Set framebuffer resize callback method
	glfwSetFramebufferSizeCallback(window, GL_Framebuffer_Resize_Callback);

	//Main loop
	while (!glfwWindowShouldClose(window)) {
		//Process input
		ProcessInput(window);

		//Render

		//Swap buffers and poll events(GLFW)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Quit
	glfwTerminate();
	return 0;
}

void GL_Framebuffer_Resize_Callback(GLFWwindow * wnd, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow * wnd)
{
	if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(wnd, true);
	}
}
