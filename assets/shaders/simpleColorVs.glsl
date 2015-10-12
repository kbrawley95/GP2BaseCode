#version 150

in vec3 vertexPosition;
in vec4 vertexColour;

out vec4 VertexColourOut;
uniform mat4 MVP;

void main()
{
	gl_Position=MVP * vec4(vertexPosition, 1.0);
	VertexColourOut=VertexColour;
}