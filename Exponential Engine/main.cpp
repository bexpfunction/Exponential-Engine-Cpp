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

	//Set wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	std::cout << "Initialization complete!!!" << std::endl;
	//End initialization

	////////////////////////////////TEST SCENE STUFF///////////////////////////////////////////////
	//Test shader
	Shader testShader("../Shaders/FlatColorVertex.glsl", "../Shaders/FlatColorFragment.glsl");

	//Test triangle vertices
	float vertices[] = {
		0.5f, 0.5f, 0.0f,		//Top right				- 0
		0.5f, -0.5f, 0.0f,		//Bottom right			- 1
		-0.5f, -0.5f, 0.0f,		//Bottom left			- 2
		-0.5f, 0.5f, 0.0f,		//Top left				- 3
		//Additional test
		-1.0f, -0.5f, 0.0f,		//Bottom most left		- 4
		1.0f, -0.5f, 0.0f		//Bottom most right		- 5
	};

	int indices[] = {
		0, 1, 2,
		3, 0, 2,
		3, 2, 4,
		0, 1, 5
	};
	
	//VBO and VAO
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bind vertex arrays
	glBindVertexArray(VAO);

	//Then bind buffers to vertex arrays
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Then bind data to buffers
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Then bind element array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Set vertex attribute pointers offsets
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Unbind vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//Unbind vao
	glBindVertexArray(0);

	/////////////////////////////////////////////////////////////////////////////////////////////////

	float yOffset = 0.0f;
	float angle = 0.0f;
	
	//Main loop
	while (!glfwWindowShouldClose(window)) {
		//Process input
		ProcessInput(window);

		//Render the screen
		//clear
		glClearColor(0.1f, 0.25f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//draw
		testShader.use();
		testShader.setFloat("offset", yOffset);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		//Swap buffers and poll events(GLFW)
		glfwSwapBuffers(window);
		glfwPollEvents();

		angle += 0.1f;
		if (angle > 360.0f) angle = 0.0f;
		yOffset = sin(angle*3.1415 / 180.0f);
	}

	//Dealloc all buffers and objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

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
