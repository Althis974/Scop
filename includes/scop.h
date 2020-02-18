/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scop.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/17 15:05:06 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 15:05:06 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SCOP_SCOP_H
#define SCOP_SCOP_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define GL_SILENCE_DEPRECATION
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>

#ifndef GL_BGR
#	define GL_BGR 0x80E0
#endif

# define WIN_H 1000
# define WIN_W 1000
# define WIN_NAME "Scop"

typedef struct		s_sdl
{
	SDL_Window *	win;
	SDL_GLContext	ctxt;
	SDL_Event		evnt;

}					t_sdl;

int					sdl_init(t_sdl *scene);
void				sdl_run(t_sdl scene);
void				sdl_exit(t_sdl scene);

#endif //SCOP_SCOP_H
