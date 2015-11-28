#include"Mesh.h"

Mesh::Mesh()
{
	m_VBO = 0;
	m_EBO = 0;
	m_VAO = 0;
	m_NoOfIndices = 0;
	m_NoOfVertices = 0;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
	vertices.clear();
	indices.clear();
}

void Mesh::GenerateBuffers(Vertex * pVerts, int numVerts, int *pIndices, int numIndices)
{
	m_NoOfIndices = numIndices;
	m_NoOfVertices = numVerts;

	//Generate Vertex Array
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, numVerts*sizeof(Vertex), pVerts, GL_STATIC_DRAW);

	//create buffer
	glGenBuffers(1, &m_EBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(int), pIndices, GL_STATIC_DRAW);

	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
}

void Mesh::Render(shared_ptr<GameObject> gameObject, shared_ptr<Camera> camera)
{
	shared_ptr<Material> material;

	mat4 MVPMatrix = gameObject->getModelMatrix() *camera->viewMatrix * camera->projMatrix;
	if (material->shader->currentShaderProgram > 0)
	{
		glUseProgram(material->shader->currentShaderProgram);
		GLint MVPLocation = glGetUniformLocation(material->shader->currentShaderProgram, "MVP");
		GLint modelLocation = glGetUniformLocation(material->shader->currentShaderProgram, "Model");
		GLint texture0Location = glGetUniformLocation(material->shader->currentShaderProgram, "texture0");
		GLint cameraPositionLocation = glGetUniformLocation(material->shader->currentShaderProgram, "cameraPosition");

		if (material->GetDiffuseMap() > 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, material->GetDiffuseMap());
			glUniform1i(texture0Location, 0);
		}

		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVPMatrix));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(gameObject->getModelMatrix()));
		glUniform3fv(cameraPositionLocation, 1, value_ptr(camera->Position()));

		material->CalculateLighting(shared_ptr<Light>(new Light()));

		glBindVertexArray(m_VAO);
		glBindBuffer(1, m_VBO);
		glBindBuffer(1, m_EBO);
		if (m_VAO > 0)
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}

}