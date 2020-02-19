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
	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
		SDL_Quit();

		return (-1);
	}

	// Version d'OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


	// Double Buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);



	// Création de la fenêtre
	scene->win = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if(!scene->win)
	{
		printf("Erreur lors de la creation de la fenetre : %s\n", SDL_GetError());
		SDL_Quit();

		return (-1);
	}


	// Création du contexte OpenGL
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
	float vertices[] = {    -1.0f, 0.0f,
							1.0f, -1.0f,
							1.0f, 1.0f}; // Triangle

	t_shader shader;

	shader = initShader("/Users/rlossy/Cursus/Scop/Shaders/vertex.glsl", "/Users/rlossy/Cursus/Scop/Shaders/fragment.glsl");
	loadShader(&shader);

	printf("prgmID %d\n", shader.prgmID);

	while(1)
	{
		// Event
		SDL_WaitEvent(&scene.evnt);

		if (scene.evnt.type == SDL_QUIT)
			break;

		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		GLuint vbo, vao;

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		GLuint index = glGetAttribLocation(shader.prgmID, "in_position");
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(index);
		// Fill and enable vertices array
		glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
		// Enable shader
		glUseProgram(shader.prgmID);
		glBindVertexArray(vao);
		// Display
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// Disable vertices array
		glDisableVertexAttribArray(0);

		// Disable shader
		glUseProgram(0);

		// Update
		SDL_GL_SwapWindow(scene.win);
	}
}

void	SDLExit(t_sdl scene)
{
	SDL_GL_DeleteContext(scene.ctxt);
	SDL_DestroyWindow(scene.win);
	SDL_Quit();
}