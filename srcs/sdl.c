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

int		sdl_init(t_sdl *scene)
{
	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Erreur lors de l'initialisation de la SDL : %s", SDL_GetError());
		SDL_Quit();

		return (-1);
	}

	// Version d'OpenGL
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


	// Double Buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Création de la fenêtre
	scene->win = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if(!scene->win)
	{
		printf("Erreur lors de la creation de la fenetre : %s", SDL_GetError());
		SDL_Quit();

		return (-1);
	}


	// Création du contexte OpenGL
	scene->ctxt = SDL_GL_CreateContext(scene->win);

	if(!scene->ctxt)
	{
		printf("Error: %s", SDL_GetError());
		SDL_DestroyWindow(scene->win);
		SDL_Quit();

		return (-1);
	}

	return (0);
}

void	sdl_run(t_sdl scene)
{
	float vertices[] = {
			0.0f, 0.0f,   0.5f, 0.0f,   0.0f, 0.5f,          // Triangle 1
			-0.8f, -0.8f,   -0.3f, -0.8f,   -0.8f, -0.3f};   // Triangle 2

	while(1)
	{
		// Event
		SDL_WaitEvent(&scene.evnt);

		if (scene.evnt.type == SDL_QUIT)
			break;

		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT);


		// Fill and enable vertices array
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);


		// Display
		glDrawArrays(GL_TRIANGLES, 0, 6);


		// Disable vertices array
		glDisableVertexAttribArray(0);


		// Update
		SDL_GL_SwapWindow(scene.win);
	}
}

void	sdl_exit(t_sdl scene)
{
	SDL_GL_DeleteContext(scene.ctxt);
	SDL_DestroyWindow(scene.win);
	SDL_Quit();
}