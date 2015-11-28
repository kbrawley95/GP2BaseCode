#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Common.h"
#include "Shader.h"
#include "Texture.h"
#include "Light.h"

class Material
{
public:

	shared_ptr<Shader> shader;
	//Use Defuse shader by default
	Material();
	Material(shared_ptr<Shader> s);
	Material(string vs, string fs);

	//Memory cleanup
	~Material();

	void CalculateLighting(shared_ptr<Light> newLight);
	void SetMainTexture(const string& filename);
	void SetCubeMapTextures(const string& posX, const string& negX, const string& posY, const string& negY, const string& posZ, const string& negZ);

	vec4& GetAmbientMaterial()
	{
		return ambientMaterial;
	};
	vec4& GetDiffuseMaterial()
	{
		return diffuseMaterial;
	};
	vec4& GetSpecularMaterial()
	{
		return specularMaterial;
	};
	GLuint& GetDiffuseMap()
	{
		return diffuseMap;
	};

private:
	vec4 ambientMaterial;
	vec4 diffuseMaterial;
	vec4 specularMaterial;
	GLuint diffuseMap;
	GLuint environmentMap;
};
#endif
