#include"Mesh.h"

Mesh::Mesh()
{
	m_VBO = 0;
	m_EBO = 0;
	m_VAO = 0;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
	vertices.clear();
	indices.clear();
}

