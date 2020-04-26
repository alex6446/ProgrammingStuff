#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h> 

#include <vector>
#include "Vertex.h"


class Primitive {
private:

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	Primitive() {}
	virtual ~Primitive() {}
	
	//Functions
	void set (
		const Vertex* vertices, 
		const unsigned nrOfVertices, 
		const GLuint* indices,
		const unsigned nrOfIndices
	) {
		for (std::size_t i = 0; i < nrOfVertices; i++)
			this->vertices.push_back(vertices[i]);

		for (std::size_t i = 0; i < nrOfIndices; i++)
			this->indices.push_back(indices[i]);
	}

	inline Vertex* getVertices () { return this->vertices.data(); }
	inline GLuint* getIndices () { return this->indices.data(); }
	inline const unsigned getNrOfVertices () { return this->vertices.size(); }
	inline const unsigned getNrOfIndices () { return this->indices.size(); }

};

class Triangle : public Primitive {
public:

	Triangle () 
		: Primitive()
	{
		Vertex vertices[] = 
		{
			//Position 							//Color 						//Texcoords 				//Normals
			glm::vec3(-0.5f, 0.5f, 0.f),		glm::vec3(1.f, 0.f, 0.f), 		glm::vec2(0.f, 1.f), 		glm::vec3(0.f, 0.f, 1.f),	
			glm::vec3(-0.5f, -0.5f, 0.f),		glm::vec3(0.f, 1.f, 0.f), 		glm::vec2(0.f, 0.f), 		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f), 		glm::vec2(1.f, 0.f), 		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.f),			glm::vec3(1.f, 1.f, 0.f), 		glm::vec2(1.f, 1.f), 		glm::vec3(0.f, 0.f, 1.f)
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] = 
		{
			0, 1, 2
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}

};

class Quad : public Primitive {
public:

	Quad () 
		: Primitive()
	{
		Vertex vertices[] = 
		{
			//Position 							//Color 						//Texcoords 				//Normals
			glm::vec3(-0.5f, 0.5f, 0.f),		glm::vec3(1.f, 0.f, 0.f), 		glm::vec2(0.f, 1.f), 		glm::vec3(0.f, 0.f, 1.f),	
			glm::vec3(-0.5f, -0.5f, 0.f),		glm::vec3(0.f, 1.f, 0.f), 		glm::vec2(0.f, 0.f), 		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f), 		glm::vec2(1.f, 0.f), 		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.f),			glm::vec3(1.f, 1.f, 0.f), 		glm::vec2(1.f, 1.f), 		glm::vec3(0.f, 0.f, 1.f)
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] = 
		{
			0, 1, 2,
			0, 2, 3
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}

};

class Pyramid : public Primitive {
public:

	Pyramid ()
		: Primitive () 
	{
		Vertex vertices[] = 
		{
			//Position 							//Color 						//Texcoords 				//Normals
			glm::vec3(0.f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f), 		glm::vec2(0.5f, 1.f), 		glm::vec3(0.f, 0.f, 1.f),	
			glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f), 		glm::vec2(0.f, 0.f), 		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 0.f, 1.f), 		glm::vec2(1.f, 0.f), 		glm::vec3(0.f, 0.f, 1.f),

			glm::vec3(0.f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f), 		glm::vec2(0.5f, 1.f), 		glm::vec3(-1.f, 0.f, 0.f),	
			glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f), 		glm::vec2(0.f, 0.f), 		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f), 		glm::vec2(1.f, 0.f), 		glm::vec3(-1.f, 0.f, 0.f),

			glm::vec3(0.f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f), 		glm::vec2(0.5f, 1.f), 		glm::vec3(0.f, 0.f, -1.f),	
			glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 1.f, 0.f), 		glm::vec2(0.f, 0.f), 		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f), 		glm::vec2(1.f, 0.f), 		glm::vec3(0.f, 0.f, -1.f),

			glm::vec3(0.f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f), 		glm::vec2(0.5f, 1.f), 		glm::vec3(1.f, 0.f, 0.f),	
			glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(0.f, 1.f, 0.f), 		glm::vec2(0.f, 0.f), 		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f), 		glm::vec2(1.f, 0.f), 		glm::vec3(1.f, 0.f, 0.f),
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		this->set(vertices, nrOfVertices, nullptr, 0);
	}
};
