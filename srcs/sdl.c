/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sdl.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/17 15:42:51 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 15:42:51 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

int		SDLInit(t_sdl *scene)
{
	// Init SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
		SDL_Quit();

		return (-1);
	}

	// Set OpenGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


	// Double Buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	// Create window
	scene->win = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if(!scene->win)
	{
		printf("Erreur lors de la creation de la fenetre : %s\n", SDL_GetError());
		SDL_Quit();

		return (-1);
	}


	// Create openGL context
	scene->ctxt = SDL_GL_CreateContext(scene->win);

	if(!scene->ctxt)
	{
		printf("Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(scene->win);
		SDL_Quit();

		return (-1);
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return (0);
}

void	SDLRun(t_sdl scene)
{
	float vertices[] = {-0.5f, -0.5f,   0.0f, 0.5f,   0.5f, -0.5f}; // Triangle

	t_shader shader;

	// Load and compile shaders

	shader = initShader("/Users/rlossy/Cursus/Scop/Shaders/basique2D.vert", "/Users/rlossy/Cursus/Scop/Shaders/basique2D.frag");
	loadShader(&shader);

	//vao is a buffer of buffers (so will point vertices and colors)
	//vbo is for the triangle points
	GLuint vao, vbo;

	//Generate Vertex Array and bind it
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Generate the buffer object for the vertices
	glGenBuffers(1, &vbo);

	//Bind it for the next few calls
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Upload triangle data to the vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//We get the location of the 'in_Vertex' named in the vertex shader
	GLuint in_Vertex_loc = glGetAttribLocation(shader.prgmID, "in_Vertex");

	//Set the location in the vao to this buffer and tell it how to access the data.
	//We have 2 points per vertex hence 2, and sizeof(float) * 2 and the GL_FLOAT
	glVertexAttribPointer(in_Vertex_loc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	// Enable buffer
	glEnableVertexAttribArray(in_Vertex_loc);

	// Enable shader
	glUseProgram(shader.prgmID);

	while(1)
	{
		// Event
		SDL_WaitEvent(&scene.evnt);

		if (scene.evnt.type == SDL_QUIT)
			break;

		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Display
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// Update
		SDL_GL_SwapWindow(scene.win);
	}

	// Disable vertices array
	glDisableVertexAttribArray(0);

	//Disable shader
	glUseProgram(0);
}

void	SDLExit(t_sdl scene)
{
	SDL_GL_DeleteContext(scene.ctxt);
	SDL_DestroyWindow(scene.win);
	SDL_Quit();
}