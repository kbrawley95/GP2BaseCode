#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Common.h"
#include "Vertices.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void update();

	void addChild(shared_ptr<GameObject> child);

	void loadDiffuseMap(const string& filename);

	void setPosition(const vec3& position)
	{
		m_Position = position;
	};

	void setRotation(const vec3& rotation)
	{
		m_Rotation = rotation;
	};

	void setScale(const vec3& scale)
	{
		m_Scale = scale;
	};

	int getNumberOfChildren()
	{
		return m_ChildGameObjects.size();
	};

	GameObject * getParent()
	{
		return m_ParentGameObject;
	};

	shared_ptr<GameObject> getChild(int i)
	{
		return m_ChildGameObjects.at(i);
	};

	GLuint getShaderProgram()
	{
		return m_ShaderProgram;
	};

	mat4& getModelMatrix()
	{
		return m_ModelMatrix;
	};

	GLuint getDiffuseMap()
	{
		return m_DiffuseMap;
	};
private:
	
	GLuint m_ShaderProgram;

	mat4 m_ModelMatrix;
	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;

	GLuint m_DiffuseMap;

	vector<shared_ptr<GameObject> > m_ChildGameObjects;
	GameObject * m_ParentGameObject;
};

#endif