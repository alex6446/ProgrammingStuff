#include "libs.h"
#include "NeuralNet/Net.h"

Vertex vertices[] = 
{
	//Position 							//Color 		 			//Texcoords
	glm::vec3(-1.f, 1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),  	
	glm::vec3(-1.f, -1.f, 0.f),		glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),  
	glm::vec3(1.f, -1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),  
	glm::vec3(1.f, 1.f, 0.f),		glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f)
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = 
{
	0, 1, 2,
	0, 2, 3
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

int width;
int height;
glm::vec2 resolution;

glm::vec2 gridsize;
glm::vec2 step;
unsigned char* regions;
GLuint texture0;

bool mouseActive;

Net* net;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    	mouseActive = true;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    	mouseActive = false;
}


#include "Functions.h"

void updateInput (GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		int regsize = (int)gridsize.x * (int)gridsize.y * 4;
		for (int i = 0; i < regsize; i++)
			regions[i] = 0;
	}
}

void updateMouse (GLFWwindow* window) {
	if (mouseActive) {
		double xpos, ypos;
        int width, height;
        glfwGetCursorPos(window, &xpos, &ypos);
        glfwGetWindowSize(window, &width, &height);

        int cordposX = xpos / step.x;
        int cordposY = ypos / step.y;
		int index = cordposY * (int)gridsize.x + cordposX;
		index *= 4;
		regions[index++] = 155;
		regions[index++] = 155;
		regions[index++] = 155;
		regions[index++] = 255;

        
        // Update texture
		glBindTexture(GL_TEXTURE_2D, texture0);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, (int)gridsize.x, (int)gridsize.y, GL_RGBA, GL_UNSIGNED_BYTE, regions);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

int main () {

	// Init topology
	int topology[] = { 2, 5, 2 };
	int layers = sizeof(topology) / sizeof(int);
	net = new Net(topology, layers);

	gridsize = glm::vec2(28, 28);

	mouseActive = false;

	int regsize = (int)gridsize.x * (int)gridsize.y * 4;
	regions = new unsigned char[regsize];
	for (int i = 0; i < regsize; i++)
		regions[i] = 0;

	//INIT GLFW
	glfwInit();

	const int WINDOW_WIDTH = 480;
	const int WINDOW_HEIGHT = 480;
	int framebufferWidth = 0;
	int framebufferHeight = 0;
	GLFWwindow* window = createWindow(
		WINDOW_WIDTH, 
		WINDOW_HEIGHT, 
		framebufferWidth,
		framebufferHeight
	);

	//INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)
	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << std::endl;
		glfwTerminate();
	}

	OpenGLOptions();

	//SHADER INIT
	GLuint core_program;
	if (!loadShaders(core_program))
		glfwTerminate();


	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	createBuffers(VAO, VBO, EBO);

	setVertexAttribPtr();

	//BIND VAO 0
	glBindVertexArray(0);

	//TEXTURE0
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)gridsize.x, (int)gridsize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, regions);

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// Set uniforms
	glUseProgram(core_program);
    glUniform2fv(glGetUniformLocation(core_program, "resolution"), 1, glm::value_ptr(resolution));
	glUseProgram(0);

	//MAIN LOOP
	while (!glfwWindowShouldClose(window)) {

		//UPDATE INPUT
		glfwPollEvents();

		//UPDATE ---------------------
		updateInput(window);
		updateMouse(window);

		glBindTexture(GL_TEXTURE_2D, texture0);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, (int)gridsize.x, (int)gridsize.y, GL_RGBA, GL_UNSIGNED_BYTE, regions);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Update window size
		glfwGetWindowSize(window, &width, &height);
    	resolution.x = width;
    	resolution.y = height;
    	step = resolution / gridsize;

		// Teach nueral network
		//net->startLearning(200);
		//updateRegions();

		//DRAW --------------------------
		//Clear
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		//Use a program
		glUseProgram(core_program);

    	// Update uniforms
    	glUniform2fv(glGetUniformLocation(core_program, "resolution"), 1, glm::value_ptr(resolution));
		glUniform1i(glGetUniformLocation(core_program, "texture0"), 0);

		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

		// Texture bing
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);

		//Bind vertex array object
		glBindVertexArray(VAO);

		//Draw
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

		//End draw
		glfwSwapBuffers(window);
		glFlush();

		// Reset
		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();

	//Delete program
	glDeleteProgram(core_program);

	//Delete VAO and Buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	return 0;
} 

