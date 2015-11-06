#version 150

in vec2 vertexPosition;
out vec2 textureCoords;

void main()
{
	textureCoords=(vertexPosition +1.0f)/2.0f;
	gl_Position=(vertexPosition.x, vertexPosition.y, 0.0f, 1.0f);
}
