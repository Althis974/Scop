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
#include <fcntl.h>
#include "../libft/libft.h"
#include <SDL2/SDL.h>

#define GL_SILENCE_DEPRECATION
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>

#ifndef GL_BGR
#	define GL_BGR 0x80E0
#endif

# define WIN_W 800
# define WIN_H 600
# define WIN_NAME "Scop"

/*
**	[SDL structure]
**
**	win is a pointer on window
**	ctxt is the OpenGL context
**	evnt take care of events
**	vao is a buffer of buffers
**	vbo_v is for triangle points
**	vbo_c is for triangle colors
*/

typedef struct		s_sdl
{
	SDL_Window *	win;
	SDL_GLContext	ctxt;
	SDL_Event		evnt;
	GLuint			vao;
	GLuint 			vbo_v;
	GLuint			vbo_c;
}					t_sdl;

typedef struct		s_shader
{
	GLuint			vrtxID;
	GLuint			frgmtID;
	GLuint			prgmID;
	char *			vrtxScr;
	char *			frgmtSrc;

}					t_shader;

// SDL

int					SDLInit(t_sdl *scene);
void				SDLRun(t_sdl scene);
void				SDLExit(t_sdl scene);

// Shader

t_shader			initShader(char *vrtxScr, char *frgmtSrc);
int					loadShader(t_shader *shader);
int					compileShader(GLuint shader, GLenum type, char *filename);

#endif //SCOP_SCOP_H
