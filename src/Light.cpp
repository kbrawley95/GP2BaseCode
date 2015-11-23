#include "Light.h"


Light::Light()
{
	m_direction = vec3(0.0f, 0.0f, 1.0f);
	m_ambientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_diffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_specularLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_specularPower = 25.0f;
}

Light::~Light()
{

}

void Light::CalculateLighting(Camera& camera, shared_ptr<GameObject>& gameObject)
{
	GLint ambientLightColourLocation = glGetUniformLocation(gameObject->getShaderProgram(), "ambientLightColour");
	GLint ambientMaterialColourLocation = glGetUniformLocation(gameObject->getShaderProgram(), "ambientMaterialColour");

	GLint diffuseLightColourLocation = glGetUniformLocation(gameObject->getShaderProgram(), "diffuseLightColour");
	GLint diffuseLightMaterialLocation = glGetUniformLocation(gameObject->getShaderProgram(), "diffuseMaterialColour");
	GLint lightDirectionLocation = glGetUniformLocation(gameObject->getShaderProgram(), "lightDirection");

	GLint specularLightColourLocation = glGetUniformLocation(gameObject->getShaderProgram(), "specularLightColour");
	GLint specularLightMaterialLocation = glGetUniformLocation(gameObject->getShaderProgram(), "specularMaterialColour");
	GLint specularPowerLocation = glGetUniformLocation(gameObject->getShaderProgram(), "specularPower");


	

	glUniform4fv(ambientLightColourLocation, 1, value_ptr(GetAmbientLightColour()));
	glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(gameObject->getAmbientMaterial()));

	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(GetDiffuseLightColour()));
	glUniform4fv(diffuseLightMaterialLocation, 1, value_ptr(gameObject->getDiffuseMaterial()));
	glUniform3fv(lightDirectionLocation, 1, value_ptr(GetLightDirection()));

	glUniform4fv(specularLightColourLocation, 1, value_ptr(GetSpecularLightColour()));
	glUniform4fv(specularLightMaterialLocation, 1, value_ptr(gameObject->getSpecularMaterial()));
	glUniform1f(specularPowerLocation, gameObject->getSpecularPower());
	
}