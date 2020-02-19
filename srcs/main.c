/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/14 10:48:50 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/14 10:48:50 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

int		main()
{
	t_sdl	scene;


	if (SDLInit(&scene))
		return (-1);

	/*//Output OpenGL Version
	const unsigned char *version = glGetString(GL_VERSION);
	if (version == NULL)
	{
		fprintf(stderr, "Unable to determine OpenGL version\n");
		exit(1);
	}
	fprintf(stderr, "OpenGl Version: %s\n", version);*/

	SDLRun(scene);

	// On quitte la SDL
	SDLExit(scene);

	return (0);
}