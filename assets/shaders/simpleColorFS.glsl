#version 150

//The output Frag Color
out vec4 FragColor;
in vec4 vertexColorOut;

void main()
{
	//The Frag Colour
	FragColor=vec4(1.0f,1.0f,1.0f,1.0f) * vertexColorOut;
}