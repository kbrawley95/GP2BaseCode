#ifndef _LIGHT_H
#define _LIGHT_H

#include"Common.h"

class Light
{
public:

	Light();
	
	~Light();

	vec3& GetLightDirection()
	{
		return m_direction;
	};

	vec4& GetAmbientLightColour()
	{
		return m_ambientLightColour;
	};
	vec4& GetDiffuseLightColour()
	{
		return m_diffuseLightColour;
	};
	vec4& GetSpecularLightColour()
	{
		return m_specularLightColour;
	};

	float GetSpecularPower()
	{
		return m_specularPower;
	};

private:

	vec3 m_direction;
	vec4 m_ambientLightColour;
	vec4 m_diffuseLightColour;
	vec4 m_specularLightColour;
	float m_specularPower;

};

#endif