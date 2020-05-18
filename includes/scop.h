/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 11:58:09 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
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

# define WIN_W 1000
# define WIN_H 1000
# define WIN_NAME "Scop"
# define FOV 90
# define INERTIA 0.9

/*
**	[SDL structure]
**
**	win		=	pointer on window
**	ctxt	=	OpenGL context
**	evnt	=	take care of events
**	vao		=	buffer of buffers
**	vbo_v	=	triangle points
**	vbo_c	=	triangle colors
**	txt		=	texture
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
**	[Shader structure]
**
**	vrtxID	=	vertices ID
**	fragID	=	fragment ID
**	prgmID	=	program ID
**	mvploc	=	ModelViewProjection location
**	txtloc	=	textures location
**	apploc	=	apply textures location
**	colloc	=	color location
**	itploc	=	interpolation location
*/

typedef struct		s_shader
{
	GLuint			vrtxID;
	GLuint			fragID;
	GLuint			prgmID;
	GLint			mvploc;
	//GLint			txtloc;
	GLint			apploc;
	GLint			colloc;
	GLint			itploc;
}					t_shader;

/*
**	[Texture structure]
**
**	*img	=	pointer on image data
**	size	=	size of image
**	w		=	width
**	h		=	height
**	row		=	size of a row
**	bpp		=	BitsPerPixel
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
**	[Event structure]
**
**	txt		=	enable/disable texture
**	col		=	enable/disable color
**	itp		=	enable/disable interpolation
*/

typedef struct		s_event
{
	int				txt;
	int				col;
	int				itp;
}					t_event;

/*
**	[Live structure]
**
**	explicit
*/

typedef struct		s_live
{
	t_mat			model;
	t_mat			view;
	t_mat			projection;
	t_mat			mvp;
}					t_live;

/*
**	[Camera structure]
**
**	ori		=	camera origin
**	dir		=	camera direction
**	tgt		=	camera target
**	trvsal	=	transversal axis
**	lgtnal	=	longitudinal axis
**	sgttal	=	sagittal axis
**	iner	=	inertia
**	velo	=	velocity
*/

typedef struct		s_cam
{
	t_vec			ori;
	t_vec			dir;
	t_vec			tgt;
	t_vec			trvsal;
	t_vec			lgtnal;
	t_vec			sgttal;
	t_vec			iner;
	double			velo;
}					t_cam;

/*
**	[Object structure]
**
**	vrtc	=	vertices
**	faces	=	explicit
**	v_len	=	vertices length
**	f_len	=	faces length
**	v_size	=	vertices size
**	f_size	=	faces size
**	f_nb	=	faces number
**	sym_ax	=	symmetry axis
**	iner	=	inertia
**	trans	=	translation
**	rot		=	rotation
**	txt		=	texture
**	velo	=	velocity
*/

typedef struct		s_obj
{
	char			*filename;
	GLfloat			*vrtc;
	GLuint			*faces;
	int				v_len;
	int				f_len;
	int				v_size;
	int				f_size;
	int				f_nb;
	t_vec			sym_ax;
	t_vec			iner;
	t_mat			trans;
	t_mat			rot;
	t_txt			txt;
	double			velo;
}					t_obj;

typedef struct		s_env
{
	t_sdl			sdl;
	t_shader 		shader;
	t_cam 			cam;
	t_obj			obj;
	t_live			live;
	t_event			event;
}					t_env;

/*
**	SDL
*/

int					SDLInit(t_env *env);
void				SDLExit(t_sdl scene);
void				create_buffers(t_env *env);

/*
**	Parsing
*/

void				parser(t_env *env);

/*
**	Shaders
*/

void				load_shader(t_env *env);
void				update_shaders(t_env *env);

/*
**	Camera
*/

void				set_cam(t_env *env);
void				camera_look_at_target(t_env *env);
void				compute_mvp_matrix(t_env *env);
void				set_projection_matrix(t_env *env);
void				camera_move_inertia(t_env *env);

/*
**	Live
*/

void				live_action(t_env *env);

/*
**	Events
*/

int 				events(t_env *env);

/*
**	Textures
*/

void				create_texture(t_env *env);
void				load_bmp(t_env *env, char *filename);

/*
**	Utils
*/

void				error(const char *err);

#endif //SCOP_SCOP_H
