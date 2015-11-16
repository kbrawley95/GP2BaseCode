#ifndef _CAMERA_H
#define _CAMERA_H

#include "Common.h"
#include "GameObject.h"

class Camera:GameObject
{
public:
	Camera();
	~Camera();

	void update();
	void setLookAt(vec3& pos);
	void setUp(vec3& up);
private:
	vec3 m_LookAt;
	vec3 m_Up;
	float m_AspectRatio;
	float m_FOV;
	float m_NearClip;
	float m_FarClip;
};

#endif