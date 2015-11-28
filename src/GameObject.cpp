#include "GameObject.h"
#include "Shader.h"
#include "Texture.h"

GameObject::GameObject()
{

	m_ShaderProgram = 0;

	m_ModelMatrix = mat4(1.0f);
	m_Position = vec3(0.0f);
	m_Rotation = vec3(0.0f);
	m_Scale = vec3(1.0f);

	m_ChildGameObjects.clear();

	m_ParentGameObject = NULL;
	m_DiffuseMap = 0;
}

GameObject::~GameObject()
{
	glDeleteProgram(m_ShaderProgram);
	glDeleteTextures(1, &m_DiffuseMap);
	m_ChildGameObjects.clear();
}

void GameObject::update()
{
	mat4 parentModel(1.0f);
	if (m_ParentGameObject)
	{
		parentModel = m_ParentGameObject->getModelMatrix();
	}
	mat4 translationMatrix = translate(mat4(1.0f), m_Position);
	mat4 scaleMatrix = scale(mat4(1.0f), m_Scale);

	mat4 rotationMatrix = rotate(mat4(1.0f), m_Rotation.x, vec3(1.0f, 0.0f, 0.0f))*
		rotate(mat4(1.0f), m_Rotation.y, vec3(0.0f, 1.0f, 0.0f))*
		rotate(mat4(1.0f), m_Rotation.z, vec3(0.0f, 0.0f, 1.0f));

	m_ModelMatrix = scaleMatrix*rotationMatrix*translationMatrix;
	m_ModelMatrix *= parentModel;

	for (auto iter = m_ChildGameObjects.begin(); iter != m_ChildGameObjects.end(); iter++)
	{
		(*iter)->update();
	}
}

void GameObject::addChild(shared_ptr<GameObject> child)
{
	child->m_ParentGameObject = this;
	m_ChildGameObjects.push_back(child);
}

void GameObject::loadDiffuseMap(const string& filename)
{
	m_DiffuseMap = loadTextureFromFile(filename);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_2D);
}

