#include "GlobalHeader.h"

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
	GLFWwindow *pWindow = glfwCreateWindow(1280, 720, "Exponential Engine", NULL, NULL);
	if (pWindow == NULL) {
		std::cout << "Error!!! Failed to create GL window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(pWindow);

	//Initialize GLAD for OpenGL pointers to call OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD!!!" << std::endl;
		return -1;
	}


	//Create the glViewport
	glViewport(0, 0, 1280, 720);

	//Set framebuffer resize callback method
	glfwSetFramebufferSizeCallback(pWindow, GL_Framebuffer_Resize_Callback);

	//Set wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	std::cout << "Initialization complete!!!" << std::endl;
	//End initialization

	////////////////////////////////TEST SCENE STUFF///////////////////////////////////////////////
	//Test shader
	Shader testShader("../Shaders/Sprite/SpriteVertex.glsl", "../Shaders/Sprite/SpriteFragment.glsl");
	glm::vec2 testSpPos(0.0f, 0.0f);
	glm::vec2 testSpSiz(0.1f, 0.1f);
	Sprite testSprite(testSpPos, testSpSiz);
	testSprite.SetShader(&testShader);

	/////////////////////////////////////////////////////////////////////////////////////////////////

	float yOffset = 0.0f, xOffset = 0.0f;
	float angle = 0.0f;
	
	//Main loop
	while (!glfwWindowShouldClose(pWindow)) {
		//Process input
		ProcessInput(pWindow);

		//Render the screen
		//clear
		glClearColor(0.1f, 0.25f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//draw
		testSpPos.x = xOffset / 2.0f;
		testSpPos.y = yOffset / 2.0f;
		testSprite.SetPosition(testSpPos);
		testSprite.Draw();

		//Swap buffers and poll events(GLFW)
		glfwSwapBuffers(pWindow);
		glfwPollEvents();

		angle += 0.1f;
		if (angle > 360.0f) angle = 0.0f;
		xOffset = cos(angle*3.1415f / 180.0f);
		yOffset = sin(angle*3.1415f / 180.0f);
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
