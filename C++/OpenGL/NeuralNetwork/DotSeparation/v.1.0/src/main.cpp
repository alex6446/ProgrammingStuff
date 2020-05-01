#include "libs.h"
#include "Net.h"

Vertex vertices[] = 
{
	//Position 							//Color 		 		
	glm::vec3(-1.f, 1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),  	
	glm::vec3(-1.f, -1.f, 0.f),		glm::vec3(0.f, 1.f, 0.f),  
	glm::vec3(1.f, -1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),  
	glm::vec3(1.f, 1.f, 0.f),		glm::vec3(1.f, 1.f, 0.f)
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = 
{
	0, 1, 2,
	0, 2, 3
};

std::vector<float> regions;
glm::vec2 gridsize;
std::vector<float> flowers;

Net* net;
glm::vec2 resolution;
glm::vec2 step;
void framebuffer_resize_callback (GLFWwindow* window, int fbW, int fbH) {
	glViewport(0, 0, fbW, fbH);
}
GLuint ssbo;

void updateNetwork () {
	net->setLearningData(flowers.data(), flowers.size());
	net->startLearning(1000);
}

void updateRegions () {
	double *input = new double[2];
	double *output;
	int index = 0;
	glm::vec2 center = step / 2.f;
	for (int i = 0; i < gridsize.x; i++) {
		for (int j = 0; j < gridsize.y; j++) {
			input[0] = ((float)i * step.x + center.x) / 100.f;
			input[1] = ((float)j * step.y + center.y) / 100.f;
			output = net->compute(input);
			if (output[0] < output[1])
				regions[index] = 0; // Blue
			else
				regions[index] = 1; // Green
			delete output;
			index++;
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
        //std::cout << width << " " << height << std::endl;
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
		//glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(float) * flowers.size(), &flowers[0]);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * flowers.size(), flowers.data(), GL_STATIC_DRAW);
    	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    }
}

unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

#include "Functions.h"

void updateInput (GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		net->reset();
}

int main () {

	/*flowers.push_back(300.f);
	flowers.push_back(150.f);
	flowers.push_back(1.f);
	flowers.push_back(0.f);

	flowers.push_back(200.f);
	flowers.push_back(100.f);
	flowers.push_back(0.f);
	flowers.push_back(1.f);

	flowers.push_back(400.f);
	flowers.push_back(150.f);
	flowers.push_back(1.f);
	flowers.push_back(0.f);

	flowers.push_back(300.f);
	flowers.push_back(100.f);
	flowers.push_back(0.f);
	flowers.push_back(1.f);

	flowers.push_back(350.f);
	flowers.push_back(50.f);
	flowers.push_back(1.f);
	flowers.push_back(0.f);

	flowers.push_back(200.f);
	flowers.push_back(50.f);
	flowers.push_back(0.f);
	flowers.push_back(1.f);

	flowers.push_back(550.f);
	flowers.push_back(100.f);
	flowers.push_back(1.f);
	flowers.push_back(0.f);

	flowers.push_back(100.f);
	flowers.push_back(100.f);
	flowers.push_back(0.f);
	flowers.push_back(1.f);*/

	// Init topology
	int topology[] = { 2, 5, 2 };
	int layers = sizeof(topology) / sizeof(int);
	net = new Net(topology, layers);

	//updateNetwork();
	//net->setLearningData(flowers.data(), flowers.size());
	//net->startLearning(800000);

	gridsize = glm::vec2(50, 20);
	regions.assign(gridsize.x*gridsize.y, 1.f);
	std::cout << regions.size() << std::endl;

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

	//GLuint ssbo;
	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * flowers.size(), flowers.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glUniform1fv(glGetUniformLocation(core_program, "regions"), regions.size(), regions.data());
	
	glUseProgram(core_program);

	int width, height;
    glfwGetWindowSize(window, &width, &height);
    resolution.x = width ;
    resolution.y = height;
    step = resolution / gridsize;
    glUniform2fv(glGetUniformLocation(core_program, "step"), 1, glm::value_ptr(step));
    glUniform2fv(glGetUniformLocation(core_program, "resolution"), 1, glm::value_ptr(resolution));
    glUniform2fv(glGetUniformLocation(core_program, "gridsize"), 1, glm::value_ptr(gridsize));


	glUseProgram(0);

	updateRegions();

	//MAIN LOOP
	while (!glfwWindowShouldClose(window)) {

		//UPDATE INPUT
		glfwPollEvents();

		//UPDATE
		updateInput(window);

		net->startLearning(200);
		updateRegions();

		//DRAW
		//Clear
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		//Use a program
		glUseProgram(core_program);
		
    	glfwGetWindowSize(window, &width, &height);
    	resolution.x = width;
    	resolution.y = height;
    	step = resolution / gridsize;
    	glUniform2fv(glGetUniformLocation(core_program, "step"), 1, glm::value_ptr(step));
    	glUniform2fv(glGetUniformLocation(core_program, "resolution"), 1, glm::value_ptr(resolution));
    	glUniform1fv(glGetUniformLocation(core_program, "regions"), regions.size(), regions.data());

		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

		//glBindBuffer(GL_SHADER_STORAGE_BUFFER, pixBBO);
		//glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(float) * regions.size(), regions.data());
    	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);



		//Bind vertex array object

		glBindVertexArray(VAO);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);

		//Draw
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

		//End draw
		glfwSwapBuffers(window);
		glFlush();


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

	return 0;
} 

