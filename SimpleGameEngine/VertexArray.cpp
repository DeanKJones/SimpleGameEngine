#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verticesP,
	unsigned int nbVerticesP,
	const unsigned int* indicesP,
	unsigned int nbIndicesP) :
	nbVertices(nbVerticesP), nbIndices(nbIndicesP),
	vertexBuffer(0), indexBuffer(0), vertexArray(0)
{
	// Create Vertex Array
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Create Vertex Buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, nbVertices * 3.0 * sizeof(float), verticesP, GL_STATIC_DRAW);

	// Create Index Buffer
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbIndicesP * sizeof(unsigned int), indicesP, GL_STATIC_DRAW);

	// Specify The Vertex Attributes
	// (For Now, Assume One Vertex Format)
	// Position is 3 Floats starting at offset 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
}

void VertexArray::setActive()
{
	glBindVertexArray(vertexArray);
}