#include "Game.h"

//Functions

//Private functions

void Game::initGLFW () {
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "ERROR::GLFW_INIT_FAILED" << std::endl;
		glfwTerminate();
	}
}

void Game::initWindow (
	const char* title,
	bool resizable
) {
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

	if (this->window == nullptr) {
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << std::endl;
		glfwTerminate();
	}

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwSetFramebufferSizeCallback(this->window, Game::framebuffer_resize_callback);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(this->window); //IMPORTANT!!!
}

void Game::initGLEW () {
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::GLEW_INIT_FAILED" << std::endl;
		glfwTerminate();
	}
}

void Game::initOpenGLOptions () {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW); // gl counter clockwise

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Input
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatrices () {
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), 
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight, 
		this->nearPlane,
		this->farPlane
	);
}

void Game::initShaders () {
	this->shaders.push_back(new Shader(
		this->GL_VERSION_MAJOR,
		this->GL_VERSION_MINOR,
		(char*)"shaders/vertex_core.glsl", 
		(char*)"shaders/fragment_core.glsl"
	));
}

void Game::initTextures () {
	this->textures.push_back(new Texture("textures/pusheen.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("textures/pusheen_specular.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("textures/container.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("textures/container_specular.png", GL_TEXTURE_2D));
}

void Game::initMaterials () {
	this->materials.push_back(new Material(
		glm::vec3(0.1f), 
		glm::vec3(1.f), 
		glm::vec3(1.f), 
		0, 1
	));
}

void Game::initModels () {
	std::vector<Mesh*> meshes;
	meshes.push_back(new Mesh(
		new Pyramid(),
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)
	));

	meshes.push_back(new Mesh(
		new Quad(),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)
	));

	this->models.push_back(new Model(
		glm::vec3(0.f),
		this->materials[0],
		this->textures[TEX_CONTAINER],
		this->textures[TEX_CONTAINER_SPECULAR],
		meshes
	));

	this->models.push_back(new Model(
		glm::vec3(0.f, 1.f, 1.f),
		this->materials[0],
		this->textures[TEX_PUSHEEN],
		this->textures[TEX_PUSHEEN_SPECULAR],
		meshes
	));

	this->models.push_back(new Model(
		glm::vec3(2.f, 0.f, 2.f),
		this->materials[0],
		this->textures[TEX_CONTAINER],
		this->textures[TEX_CONTAINER_SPECULAR],
		meshes
	));

	for (auto*& i : meshes)
		delete i;
}

void Game::initLights () {
	this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

void Game::initUniforms () {
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
}

void Game::updateUniforms () {

	this->ViewMatrix = this->camera.getViewMatrix();
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");

	//Move, rotate and scale
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	//ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov), 
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight, 
		this->nearPlane,
		this->farPlane
	);

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");
}

//Constructors/Destructors
Game::Game (
	const char* title,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT, 
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	bool resizable
) : 
	WINDOW_WIDTH(WINDOW_WIDTH), 
	WINDOW_HEIGHT(WINDOW_HEIGHT), 
	GL_VERSION_MAJOR(GL_VERSION_MAJOR), 
	GL_VERSION_MINOR(GL_VERSION_MINOR),
	camera(glm::vec3(0.f, 0.f, 2.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{
	this->window = nullptr;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;

	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);

	this->fov = 60.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;

	this->dt = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX = 0.f;
	this->lastMouseY = 0.f;
	this->mouseX = 0.f;
	this->mouseY = 0.f;
	this->mouseOffsetX = 0.f;
	this->mouseOffsetY = 0.f;
	this->firstMouse = true;

	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initModels();
	this->initLights();
	this->initUniforms();
}

Game::~Game () {
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (auto*& i : this->shaders) delete i;
	for (auto*& i : this->textures) delete i;
	for (auto*& i : this->materials) delete i;
	//for (auto*& i : this->meshes) delete i;
	for (auto*& i : this->models) delete i;
	for (auto*& i : this->lights) delete i;
}

//Accessor
int Game::getWindowShouldClose () {
	return glfwWindowShouldClose(this->window);
}

//Modifiers
void Game::setWindowShouldClose () {
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

//Functions
void Game::updateDt () {
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}

void Game::updateMouseInput () {
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse) {
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	//Calc offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY;

	//Set last X and Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;
}

void Game::updateKeyboardInput () {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		this->camera.move(this->dt, FORWARD);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		this->camera.move(this->dt, BACKWARD);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		this->camera.move(this->dt, LEFT);
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		this->camera.move(this->dt, RIGHT);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		this->camera.move(this->dt, DOWN);
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		this->camera.move(this->dt, UP);
}


void Game::updateInput () {
	glfwPollEvents();
	this->updateKeyboardInput();
	this->updateMouseInput();
	this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}

void Game::update () {
	this->updateDt();
	this->updateInput();

	this->models[0]->rotate(glm::vec3(0.f, 1.f, 0.f));
	this->models[1]->rotate(glm::vec3(0.f, 1.f, 0.f));
	this->models[2]->rotate(glm::vec3(0.f, 1.f, 0.f));
}

void Game::render () {
	
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	this->updateUniforms();

	//Render models
	for (auto& i : this->models)
		i->render(this->shaders[SHADER_CORE_PROGRAM]);

	//End draw
	glfwSwapBuffers(window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//Static functions
void Game::framebuffer_resize_callback (GLFWwindow* window, int fbW, int fbH) {
	glViewport(0, 0, fbW, fbH);
}

