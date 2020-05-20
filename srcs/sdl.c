/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

int		sdl_init_next(t_env *env)
{
	if (!env->sdl.win)
	{
		write(2, "Error: Failed to create window: ", 23);
		ft_putstr_fd(SDL_GetError(), 2);
		write(2, "\n", 1);
		SDL_Quit();
		return (-1);
	}
	env->sdl.ctxt = SDL_GL_CreateContext(env->sdl.win);
	if (!env->sdl.ctxt)
	{
		error(SDL_GetError());
		SDL_DestroyWindow(env->sdl.win);
		SDL_Quit();
		return (-1);
	}
	return (0);
}

int		sdl_init(t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		error(SDL_GetError());
		SDL_Quit();
		return (-1);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
			SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	env->sdl.win = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (sdl_init_next(env) < 0)
		return (-1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	return (0);
}

void	sdl_exit(t_sdl scene)
{
	SDL_GL_DeleteContext(scene.ctxt);
	SDL_DestroyWindow(scene.win);
	SDL_Quit();
}

void	opengl_set_buffers(t_env *env)
{
	glGenBuffers(1, &env->sdl.vbo_v);
	glGenBuffers(1, &env->sdl.vbo_c);
	glGenVertexArrays(1, &env->sdl.vao);
	glBindVertexArray(env->sdl.vao);
	glBindBuffer(GL_ARRAY_BUFFER, env->sdl.vbo_v);
	glBufferData(GL_ARRAY_BUFFER, env->obj.v_size, env->obj.vrtc,
			GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->sdl.vbo_c);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, env->obj.f_size, env->obj.faces,
			GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
			(GLvoid *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
			(GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

void	opengl_set_texture(t_env *env)
{
	glGenTextures(1, &env->sdl.txt);
	glBindTexture(GL_TEXTURE_2D, env->sdl.txt);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, env->obj.txt.w, env->obj.txt.h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, env->obj.txt.img);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}
