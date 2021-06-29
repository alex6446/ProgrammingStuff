#include "libs.h"
#include "Net.h"

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

std::vector<float> flowers;
GLuint ssbo;

Net* net;

void updateNetwork () {
	net->setLearningData(flowers.data(), flowers.size());
	net->startLearning(1000);
}

void updateRegions () {
	double *input = new double[2];
	double *output;
	int index = 0;
	glm::vec4 blue(46.f, 111.f, 209.f, 255.f);
	glm::vec4 green(5.f, 172.f, 114.f, 255.f);
	glm::vec4 rescol;
	glm::vec2 center = step / 2.f;
	for (int i = 0; i < gridsize.y; i++) {
		for (int j = 0; j < gridsize.x; j++) {
			input[0] = ((float)j * step.x + center.x) / 1000.f;
			input[1] = ((float)i * step.y + center.y) / 1000.f;
			output = net->compute(input);

			rescol = blue * glm::vec4(output[1]) + green * glm::vec4(output[0]);

			float divider = 255.f; 
			if (rescol.x > divider) divider = rescol.x; 
			if (rescol.y > divider) divider = rescol.y;
			if (rescol.z > divider) divider = rescol.z;
			if (rescol.w > divider) divider = rescol.w;

			divider = 255.f / divider;
			rescol *= glm::vec4(divider);

			regions[index++] = (char)rescol.x;
			regions[index++] = (char)rescol.y;
			regions[index++] = (char)rescol.z;
			regions[index++] = (char)rescol.w;

			delete output;
		}
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        int width, height;
        glfwGetCursorPos(window, &xpos, &ypos);
        glfwGetWindowSize(window, &width, &height);
        std::cout << xpos << " " << ypos << std::endl;
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
			flowers.push_back(xpos);
			flowers.push_back(ypos);
			flowers.push_back(0.f);
			flowers.push_back(1.f);
			net->setLearningData(flowers.data(), flowers.size());
        }
		else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
			flowers.push_back(xpos);
			flowers.push_back(ypos);
			flowers.push_back(1.f);	
			flowers.push_back(0.f);	
			net->setLearningData(flowers.data(), flowers.size());
		}
		net->startLearning(10000);
		updateRegions();

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * flowers.size(), flowers.data(), GL_STATIC_DRAW);
    	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    }
}


#include "Functions.h"

void updateInput (GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		net->reset();
}

int main () {

	// Init topology
	int topology[] = { 2, 5, 2 };
	//int topology[] = { 2, 8, 16, 10, 2 };
	int layers = sizeof(topology) / sizeof(int);
	net = new Net(topology, layers);

	gridsize = glm::vec2(200, 100);
	regions = new unsigned char[(int)gridsize.x * (int)gridsize.y * 4];

	//INIT GLFW
	glfwInit();

	const int WINDOW_WIDTH = 640;
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
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)gridsize.x, (int)gridsize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, regions);

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//GLuint ssbo;
	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * flowers.size(), flowers.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	
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

		// Update window size
		glfwGetWindowSize(window, &width, &height);
    	resolution.x = width;
    	resolution.y = height;
    	step = resolution / gridsize;

		// Teach nueral network
		net->startLearning(200);
		updateRegions();

		// Update texture
		glBindTexture(GL_TEXTURE_2D, texture0);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, (int)gridsize.x, (int)gridsize.y, GL_RGBA, GL_UNSIGNED_BYTE, regions);
		glBindTexture(GL_TEXTURE_2D, 0);

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
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);

		//Draw
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

		//End draw
		glfwSwapBuffers(window);
		glFlush();

		// Reset
		glBindVertexArray(0);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
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

