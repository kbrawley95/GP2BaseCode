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

