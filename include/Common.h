#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>
#include <string> 
#include <sstream>
#include <fstream>


#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

//Maths Headers
#include <glm.hpp>
using namespace glm;

#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>

const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";

#include "Graphics.h"
#include "Vertex.h"
#include "Shader.h"


#endif
