#include "Common.h"
#include "Graphics.h"
#include "Vertex.h"
#include "Shader.h"
#include"Texture.h"

//Shader Program
GLuint shaderProgram = 0;

//Vertex Buffer Object
GLuint VBO;
//Element Buffer Object 
GLuint EBO;
//Vertex Array Object
GLuint VAO;

//Texture Map
GLuint textureMap;

//Matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;
mat4 MVPMatrix;

Vertex verts[] = {

	//Front
		{ vec3(-0.5f, 0.5f, 0.5f),
		vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)},// Top Left

		{ vec3(-0.5f, -0.5f, 0.5f),
		vec4(1.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f) },// Bottom Left

		{ vec3(0.5f, -0.5f, 0.5f),
		vec4(0.0f, 1.0f, 1.0f, 1.0f), vec2(1.0f,1.0f) }, //Bottom Right

		{ vec3(0.5f, 0.5f, 0.5f),
		vec4(1.0f, 0.0f, 1.0f, 1.0f),vec2(1.0f, 0.0f) },// Top Right


		//back
		{ vec3(-0.5f, 0.5f, -0.5f),
		vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f) },// Top Left

		{ vec3(-0.5f, -0.5f, -0.5f),
		vec4(1.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},// Bottom Left

		{ vec3(0.5f, -0.5f, -0.5f),
		vec4(0.0f, 1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)}, //Bottom Right

		{ vec3(0.5f, 0.5f, -0.5f),
		vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)},// Top Right

};

GLuint indices[] = {
	//front
	0, 1, 2,
	0, 3, 2,

	//left
	4, 5, 1,
	4, 1, 0,

	//right
	3, 7, 2,
	7, 6, 2,

	//bottom
	1, 5, 2,
	6, 2, 5,

	//top
	4, 0, 7,
	0, 7, 3,

	//back
	4, 5, 6,
	4, 7, 6
};


void initScene()
{	
	//Load Texture & Bind
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	textureMap = loadTextureFromFile(texturePath);

	glBindTexture(GL_TEXTURE_2D, textureMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);

	//||====VERTEX ARRAY OBJECT====||
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	//||====VERTEX BUFFER OBJECT====||
	//create buffer
	glGenBuffers(1, &VBO);
	//Make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Copy vertex data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);


	//||====ELEMENT BUFFER OBJECT====||
	//create buffer
	glGenBuffers(1, &EBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Vertex array pointers setup
	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3)) +(sizeof(vec4)));

	GLuint vertexShaderProgram = 0;
	string vsPath = ASSET_PATH + SHADER_PATH + "/simpleColorVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
	checkForCompileErrors(vertexShaderProgram);

	GLuint fragmentShaderProgram = 0;
	string fsPath = ASSET_PATH + SHADER_PATH + "/simpleColorFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
	checkForCompileErrors(fragmentShaderProgram);

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);

	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);


	glBindAttribLocation(shaderProgram, 0, "vertexPosition");
	glBindAttribLocation(shaderProgram, 1, "vertexColor");
	glBindAttribLocation(shaderProgram, 2, "vertexTexCoords");

	glLinkProgram(shaderProgram);

	checkForLinkErrors(shaderProgram);

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}

void cleanUp()
{
	glDeleteTextures(1, &textureMap);
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	
}

void render()
{
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureMap);

	GLuint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	GLuint texture0Location = glGetUniformLocation(shaderProgram, "texture0");
	glUniform1f(texture0Location, 0);

	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVPMatrix));
	
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

}	

void update()
{
	projMatrix = perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

	viewMatrix = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	worldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));

	MVPMatrix = projMatrix*viewMatrix*worldMatrix;
}

int main(int argc, char * arg[])
{
	bool run = true;

	//init everything - SD, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "ERROR SDL_Init" << SDL_GetError() << endl;

		return -1;
	}

	//init SDL_Image
	int imageInitFlags = IMG_INIT_JPG|| IMG_INIT_PNG;
	int returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)&(imageInitFlags)) != imageInitFlags)
	{
		cout << "ERROR SDL_Image Init" << IMG_GetError() << endl;
	}

	//Ask for version 4.2 of OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Create a window
	SDL_Window * window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);	//Window title, x position (centred, y position centred, width (pixels), height (pixels), flags

	//Create an OpenGL context associated with the windo.
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	//Initialisation
	//Call our InitOpenGL Function
	initOpenGL();
	//Call our InitScene Funtion
	initScene();
	//Set Our ViewPort
	setViewPort(640, 480);

	//Value to hold the even generated by SDL
	SDL_Event event;
	//Game loop
	while (run)
	{
		//while we still have events in the queue
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYUP)
			{
				cout << "Key Released" << endl;

				switch (event.key.keysym.sym)
				{
				case SDLK_a:
				
					break;

				case SDLK_d:
					
					break;

				case SDLK_w:
					
					break;

				case SDLK_s:
				
					break;
				}
			}
			else if (event.type == SDL_KEYDOWN)
			{
				cout << "Key Pressed" << endl;

				switch (event.key.keysym.sym)
				{
				case SDLK_a:
					
					break;

				case SDLK_d:
					
					break;

				case SDLK_w:
					
					break;

				case SDLK_s:
				
					break;
				}
			}

			//Get Event type
			switch (event.type)
			{
			case SDL_QUIT:
			{
				//set our boolean which controls the loop to false
				run = false;
				break;
			}

			case SDL_WINDOWEVENT_CLOSE:
			{
				//set our boolean which controls the loop to false
				run = false;
				break;
			}


			}

		}

		//update
		update();
		//Then Draw
		render();

		//Call wap so that our GL back buffer is displayed
		SDL_GL_SwapWindow(window);
	}

	//Clean up, reverse order!!!
	cleanUp();
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

    return 0;
}
