#include "Material.h"

Material::Material()
{
	//Compile Shader
	shader = shared_ptr<Shader>(new Shader("simpleColourVS.glsl", "simpleColourFS.glsl"));
}

Material::Material(string vs, string fs)
{
	//Compile Shader
	shader = shared_ptr<Shader>(new Shader(vs, fs));
}
Material::Material(shared_ptr<Shader> s)
{
	shader = s;
}

Material::~Material()
{
	glDeleteTextures(1, &diffuseMap);
}

void Material::CalculateLighting(shared_ptr<Light> newLight)
{
	GLint ambientLightColourLocation = glGetUniformLocation(shader->currentShaderProgram, "ambientLightColour");
	GLint ambientMaterialColourLocation = glGetUniformLocation(shader->currentShaderProgram, "ambientMaterialColour");

	GLint diffuseLightColourLocation = glGetUniformLocation(shader->currentShaderProgram, "diffuseLightColour");
	GLint diffuseLightMaterialLocation = glGetUniformLocation(shader->currentShaderProgram, "diffuseMaterialColour");
	GLint lightDirectionLocation = glGetUniformLocation(shader->currentShaderProgram, "lightDirection");

	GLint specularLightColourLocation = glGetUniformLocation(shader->currentShaderProgram, "specularLightColour");
	GLint specularLightMaterialLocation = glGetUniformLocation(shader->currentShaderProgram, "specularMaterialColour");
	GLint specularPowerLocation = glGetUniformLocation(shader->currentShaderProgram, "specularPower");

	glUniform4fv(ambientLightColourLocation, 1, value_ptr(newLight->GetAmbientLightColour()));
	glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(GetAmbientMaterial()));

	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(newLight->GetDiffuseLightColour()));
	glUniform4fv(diffuseLightMaterialLocation, 1, value_ptr(GetDiffuseMaterial()));
	glUniform3fv(lightDirectionLocation, 1, value_ptr(newLight->GetLightDirection()));

	glUniform4fv(specularLightColourLocation, 1, value_ptr(newLight->GetSpecularLightColour()));
	glUniform4fv(specularLightMaterialLocation, 1, value_ptr(GetSpecularMaterial()));
	glUniform1f(specularPowerLocation, newLight->GetSpecularPower());
}

void Material::SetMainTexture(const string& filename)
{
	diffuseMap = loadTextureFromFile(filename);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Material::SetCubeMapTextures(const string& posX, const string& negX, const string& posY, const string& negY, const string& posZ, const string& negZ)
{
	environmentMap = LoadCubemapTexture(posX, negX, posY, negY, posZ, negZ);

}