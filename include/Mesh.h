#ifndef _MESH_H
#define _MESH_H

#include "Vertices.h"
#include "Common.h"
#include "Material.h"


class Mesh
{
public:
	vector<Vertex> vertices;
	vector<int> indices;

	int getNumVerts()
	{
		return vertices.size();
	};

	int getNumIndices()
	{
		return indices.size();
	};

	Mesh();
	~Mesh();
	

	int getNumberOfIndices()
	{
		return m_NoOfIndices;
	};

	int getNumberOfVetices()
	{
		return m_NoOfVertices;
	};

	GLuint getVertexArrayObject()
	{
		return m_VAO;
	};

	void Render(shared_ptr<GameObject> gameObject, shared_ptr<Camera> camera);
	void GenerateBuffers(Vertex * pVerts, int numVerts, int *pIndices, int numIndices);

private:

	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;

	GLuint m_NoOfIndices;
	GLuint m_NoOfVertices;


};


#endif