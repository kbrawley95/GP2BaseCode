#include "Common.h"

//Movement Variables
bool up, down, left, right = false;
GLfloat x, y, z=0;
GLfloat speed =.001f;

//Vertex array
Vertex verts[] = {

	//Front Face
		{-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Left
		{-0.5f,-0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f},	//Bottom Left
		{0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f},	//Bottom Right
		{0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f},		//Top Right
		{-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Left
		{0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f},	//Bottom Right

	//Back Face
		{-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Left
		{-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f},	//Bottom Left
		{0.5f,-0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Bottom Right
		{0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Right
		{-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Left
		{0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f},	//Bottom Right

	//Left Face
		{-0.5f, 0.5f, -0.5f, 1.0, 0.0f, 1.0f, 1.0f},	//Top Left
		{-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f},	//Bottom Left
		{-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f},	//Bottom Right
		{-0.5f,	0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Right
		{-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Left
		{-0.5f, -0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 1.0f },	//Bottom Right

	//Right Face
		{0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Left
		{0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f},	//Bottom Left
		{0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f},	//Bottom Right
		{0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Right
		{0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Left
		{0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f},	//Bottom Right

	//Top Face
		{-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f },	//Top Left
		{0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f},			//Bottom Left
		{0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f},	//Bottom Right
		{-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Right
		{-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Left
		{0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f},	//Bottom Right


	//Bottom Face
		{-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Left
		{0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f},	//Bottom Left
		{0.f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f},	//Bottom Right
		{-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Right
		{ -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f},	//Top Left
		{0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f},	//Bottom Right


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
GLuint VBO;
GLuint EBO;

void initScene()
{	
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
}

void cleanUp()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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
		std::cout << speed << std::endl;
	}
	if (down)
	{
		y -= speed;
		std::cout << speed << std::endl;
	}
}

void render()
{
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Make the new VBO active. Repeat here as a sanity check (may have changed since the initialisation
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//the 3 pararmeter is now filled out, the pipeline needs to know the size of each vertex
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);

	//The last parameter basically says that the colours start 3 floats into each element of the array
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void**)(3 * sizeof(float)));

	//Establish arrays that contains vertices & colours
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
	
	//glDrawArrays(GL_TRIANGLES, 0, sizeof(verts) / sizeof(Vertex));	Render using VBO

	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);
		//REset using the Identity MAtrix
	glLoadIdentity();
	//translate
	gluLookAt(-0.5f, -0.5f, 0.5f, 0.0, 0.0, -1.0f, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.0f, -6.0f);
	//ACtually draw the triangle, giving the number of vertices provided
	glDrawArrays(GL_TRIANGLES, 0, sizeof(verts) / (3 * sizeof(float)));

	////Additional triangles rendered relative to the initial triangles position	
	//glTranslatef(1.0f, 0.0f, -6.0f);
	//glDrawArrays(GL_TRIANGLES, 0, sizeof(verts) / (3 * sizeof(float)));
	//glTranslatef(1.0f, 0.0f, -6.0f);
	//glDrawArrays(GL_TRIANGLES, 0, sizeof(verts) / (3 * sizeof(float)));
	//glPushMatrix();
	////Switch to ModelView
	//glMatrixMode(GL_MODELVIEW);

	////||===================================================||
	////||======================TRIANGLE1====================||
	////Reset using the Identity Matrix
	//glLoadIdentity();
	////Translate to -5.0f on z-axis
	//glTranslatef(x, y, -5.0f);
	////Begin drawing triangles
	//glBegin(GL_TRIANGLES);
	//	glColor3f(1.0f, 0.0f, 1.0f);	//Color of the vertices
	//	glVertex3f(-1.0f, 0.0f, 0.0f);	//Top
	//	glVertex3f(-1.0f, -1.0f, 0.0f);	//Bottom Left
	//	glVertex3f(1.0f, -1.0f, 0.0f);	//Bottom Right
	//glEnd();
	//
	////||===================================================||
	////||======================TRIANGLE2====================||
	////Reset using the Identity Matrix
	//glLoadIdentity();
	////Translate to 1.0f on the x-axis & -3.0f, on the z-axis
	//glTranslatef(0.0f, 0.0f, -5.0f);
	////Begin drawing triangles
	//glBegin(GL_TRIANGLES);
	//		glColor3f(1.0f, 1.0f, 0.0f);	//Color of the vertices
	//		glVertex3f(0.0f, 1.0f, 0.0f);	//Top
	//		glVertex3f(-1.0f, -1.0f, 0.0f);	//Bottom Left
	//		glVertex3f(1.0f, -1.0f, 0.0f);	//Bottom Right
	//glEnd();
	//glPopMatrix();

}	

void update()
{
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
