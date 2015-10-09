#include "Common.h"

//Movement Variables
bool up, down, left, right = false;
GLfloat x, y, z=0;
GLfloat speed =.001f;

//Shader Program
GLuint shaderProgram = 0;

//Matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;
mat4 MVPMatrix;



//Vertex array
Vertex verts[] = {

	//Front Face
	vec3{ -0.5f, 0.5f, 0.5f }, vec4{1.0f, 0.0f, 1.0f, 1.0f},	//Top Left
	vec3{ -0.5f, -0.5f, 0.5f }, vec4{1.0f, 1.0f, 0.0f, 1.0f },	//Bottom Left
	vec3{ 0.5f, -0.5f, 0.5f }, vec4{0.0f, 1.0f, 1.0f, 1.0f },	//Bottom Right
	vec3{ 0.5f, 0.5f, 0.5f }, vec4{1.0f, 0.0f, 1.0f, 1.0f },		//Top Right
	

	//Back Face
	vec3{ -0.5f, 0.5f, -0.5f },vec4{ 1.0f, 0.0f, 1.0f, 1.0f },	//Top Left
	vec3{ -0.5f, -0.5f, -0.5f } ,vec4{1.0f, 1.0f, 0.0f, 1.0f },	//Bottom Left
	vec3{ 0.5f, -0.5f, -0.5f }, vec4{1.0f, 0.0f, 1.0f, 1.0f },	//Bottom Right
	vec3{ 0.5f, 0.5f, -0.5f } , vec4{1.0f, 0.0f, 1.0f, 1.0f }	//Top Right

};

GLuint indices[] = {

	//front
	0,1,2,
	0,3,2,

	//left
	4,5,1,
	4,1,0,

	//right
	3,7,2,
	7,6,2,

	//bottom
	1,5,2,
	6,2,5,

	//top
	4,0,7,
	0,7,3,

	//back
	4,5,6,
	4,7,6

};
//Vertex Buffer Object
GLuint VBO;
//Element Buffer Object 
GLuint EBO;
//Vertex Array Object
GLuint VAO;

void initScene()
{	

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
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);

	GLuint vertexShaderProgram = 0;
	std::string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
	checkForCompileErrors(vertexShaderProgram);

	GLuint fragmentShaderProgram = 0;
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
	checkForCompileErrors(fragmentShaderProgram);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);
	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

	//Binding location 0 to vertexPosition in shader program
	glBindAttribLocation(shaderProgram, 0, "vertexPosition");
}

void cleanUp()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProgram);
}

void move()
{
	if (left)
	{
		x -=speed;
		std::cout <<"Moving Left. Position: " << x << std::endl;
	}
	 
	if (right)
	{
		x += speed;
		std::cout << "Moving Right. Position: " << x << std::endl;
	}	
	
	if (up)
	{
		y += speed;
		std::cout << "Moving Up. Position: " <<y<< std::endl;
	}
	if (down)
	{
		y -= speed;
		std::cout << "Moving Down. Position: "<< y << std::endl;
	}
}

void render()
{
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

	glUseProgram(shaderProgram);	

	GLuint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVPMatrix));
	
}	

void update()
{
	projMatrix = perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

	viewMatrix = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	worldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));

	MVPMatrix = projMatrix*viewMatrix*worldMatrix;

	//Alterates position of triangle on x/y axises
	move();

}

int main(int argc, char * arg[])
{
	bool run = true;

	//init everything - SD, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;

		return -1;
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
				std::cout << "Key Released" << std::endl;

				switch (event.key.keysym.sym)
				{
				case SDLK_a:
					left = false;
					break;

				case SDLK_d:
					right = false;
					break;

				case SDLK_w:
					up= false;
					break;

				case SDLK_s:
					down = false;
					break;
				}
			}
			else if (event.type == SDL_KEYDOWN)
			{
				std::cout << "Key Pressed" << std::endl;

				switch (event.key.keysym.sym)
				{
				case SDLK_a:
					left = true;
					break;

				case SDLK_d:
					right = true;
					break;

				case SDLK_w:
					up = true;
					break;

				case SDLK_s:
					down =true;
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
	SDL_Quit();

    return 0;
}
