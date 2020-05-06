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
#include "keycode.h"
#include "../libft/libft.h"
#include <SDL2/SDL.h>

#define GL_SILENCE_DEPRECATION
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>

#ifndef GL_BGR
#	define GL_BGR 0x80E0
#endif

# define WIN_W 800
# define WIN_H 800
# define WIN_NAME "Scop"
# define FOV 90
# define BUFFER_SIZE 128

/*
**	[SDL structure]
**
**	win is a pointer on window
**	ctxt is the OpenGL context
**	evnt take care of events
**	vao is a buffer of buffers
**	vbo_v is for triangle points
**	vbo_c is for triangle colors
**	txt is for texture
*/

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_GLContext	ctxt;
	SDL_Event		evnt;
	GLuint			vao;
	GLuint 			vbo_v;
	GLuint			vbo_c;
	GLuint			txt;
}					t_sdl;

/*
**	[Texture structure]
**
**	*img is a pointer on image data
**	size is the size of image
**	w is the width
**	h is the height
**	row is the size of a row
**	bpp is nb of BitsPerPixel
*/

typedef struct		s_txt
{
	unsigned char	*img;
	int				size;
	int				w;
	int				h;
	int				row;
	short			bpp;
}					t_txt;

/*
typedef struct		s_shader
{
	GLuint			vrtxID;
	GLuint			frgmtID;
	GLuint			prgmID;
	char			*vrtxScr;
	char			*frgmtSrc;

}					t_shader;
*/

typedef struct	s_shader
{
	GLuint	program;
	GLint	mvploc;
	//GLint	cmdloc;
	//GLint	smdloc;
	GLint	tmdloc;
	//GLint	gmdloc;
	//GLint	mmdloc;
	GLint	texloc;
}				t_shader;

typedef struct	s_live
{
	t_mat	model;
	t_mat	view;
	t_mat	projection;
	t_mat	mvp;
}				t_live;

typedef struct		s_cam
{
	t_vec			ori;
	t_vec			dir;
	t_vec			target;
	t_vec			up;
	t_vec			right;
	t_vec			front;
	t_vec			inertia;
	double			velocity;
}					t_cam;

typedef struct		s_obj
{
	t_mat			translation;
	t_mat			rotation;
	GLfloat			*vrtc;
	GLuint			*faces;
	int				f_len;
	int				v_len;
	int				f_size;
	int				v_size;
	int				f_nb;
	t_vec			sym_axis;
	t_vec			inertia;
	t_txt			txt;
	double			velocity;
	char			*filename;
}					t_obj;

typedef struct		s_env
{
	t_sdl			sdl;
	t_shader 		shader;
	t_cam 			cam;
	t_obj			obj;
	t_live			live;
}					t_env;

// SDL

int					SDLInit(t_env *env);
void				SDLRun(t_env *env);
void				SDLExit(t_sdl scene);

// Shader

t_shader			initShader(char *vrtxScr, char *frgmtSrc);
int					loadShader(t_shader *shader);
int					compileShader(GLuint shader, GLenum type, char *filename);

void			build_shader_program(t_env *env);
void	camera_look_at_target(t_env *env);
void	compute_mvp_matrix(t_env *env);
void			update_shader_uniforms(t_env *env);
void	create_buffers(t_env *env);
void	set_projection_matrix(t_env *env, float fov);
void		parser(t_env *env);
void	live_action(t_env *env, double inertia);
void	camera_move_inertia(t_env *env, double inertia);
void	create_texture(t_env *env);
void	load_bmp(t_env *env, char *filename);

int 	events(t_env *env);
void				error(const char *err);
#endif //SCOP_SCOP_H
