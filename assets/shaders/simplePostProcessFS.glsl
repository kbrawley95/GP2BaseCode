out vec4 FragColor
in vec2 textureCoords;
uniform sampler2D texture0;

void main()
{
	FragColor=(texture0, textureCoords);
}