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

int		SDLInit(t_env *env)
{
	// Init SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		error(SDL_GetError());
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
	env->sdl.win = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(!env->sdl.win)
	{
		write(2, "Error Creating window: ", 23);
		ft_putstr_fd(SDL_GetError(), 2);
		write(2, "\n", 1);
		SDL_Quit();
		return (-1);
	}

	// Create openGL context
	env->sdl.ctxt = SDL_GL_CreateContext(env->sdl.win);
	if(!env->sdl.ctxt)
	{
		error(SDL_GetError());
		SDL_DestroyWindow(env->sdl.win);
		SDL_Quit();
		return (-1);
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	return (0);
}

void	SDLRun(t_env *env)
{
	//float vertices[] = {-0.5f, -0.5f,   0.0f, 0.5f,   0.5f, -0.5f}; // Triangle
	//float couleurs[] = {1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f};

	//t_shader shader;

	// Load and compile shaders

	//env->shader = initShader("/Users/rlossy/Cursus/Scop/Shaders/couleur2D.vert", "/Users/rlossy/Cursus/Scop/Shaders/couleur2D.frag");
	//loadShader(&env->shader);

	//Generate Vertex Array and bind it
	glGenVertexArrays(1, &env->sdl.vao);
	glBindVertexArray(env->sdl.vao);

	//Generate the buffer object for the vertices
	glGenBuffers(1, &env->sdl.vbo_v);

	//Bind it for the next few calls
	glBindBuffer(GL_ARRAY_BUFFER, env->sdl.vbo_v);

	//Upload triangle data to the vbo_v
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, env->obj.v_size, env->obj.vrtc, GL_STATIC_DRAW);

	//Get the location of the 'in_Vertex' named in the vertex shader
	//GLuint in_Vertex_loc = glGetAttribLocation(env->shader.prgmID, "in_Vertex");

	//Set the location in the vao to this buffer and tell it how to access the data.
	//2 points per vertex hence 2, and sizeof(float) * 2 and the GL_FLOAT
	//glVertexAttribPointer(in_Vertex_loc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

	// Enable buffer
	glEnableVertexAttribArray(0);

	//Generate the vbo for colors
	glGenBuffers(1, &env->sdl.vbo_c);

	//Bind it for the next few calls
	glBindBuffer(GL_ARRAY_BUFFER, env->sdl.vbo_c);

	//Upload the color data in the same way as triangles
	//glBufferData(GL_ARRAY_BUFFER, sizeof(couleurs), couleurs, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, env->obj.f_size, env->obj.faces, GL_STATIC_DRAW);

	//Get the location of the 'in_Color' named in the vertex shader
	//GLint in_Color_loc = glGetAttribLocation(env->shader.prgmID, "in_Color");

	//This time it's RGBA values so set up 4 floats per vertex
	//glVertexAttribPointer(in_Color_loc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

	//Enable the vbo
	glEnableVertexAttribArray(1);

	// Enable shader
	//glUseProgram(env->shader.prgmID);
	glUseProgram(env->shader.program);


	while(1)
	{
		// Event
		SDL_WaitEvent(&env->sdl.evnt);
		if (env->sdl.evnt.type == SDL_QUIT)
			break;

		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera_look_at_target(env);
		compute_mvp_matrix(env);
		update_shader_uniforms(env);
		glBindVertexArray(env->sdl.vao);

		// Display
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, env->obj.f_nb, GL_UNSIGNED_INT, 0);

		// Update
		SDL_GL_SwapWindow(env->sdl.win);
	}

	// Disable vertices array
	glDisableVertexAttribArray(1);

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

void	create_buffers(t_env *env)
{
	glGenBuffers(1, &env->sdl.vbo_v);
	glGenBuffers(1, &env->sdl.vbo_c);
	glGenVertexArrays(1, &env->sdl.vao);
	glBindVertexArray(env->sdl.vao);
	glBindBuffer(GL_ARRAY_BUFFER, env->sdl.vbo_v);
	glBufferData(GL_ARRAY_BUFFER, env->obj.v_size, env->obj.vrtc, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->sdl.vbo_c);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, env->obj.f_size, env->obj.faces, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
						  (GLvoid *) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
						  (GLvoid *) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef(1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	
	create_texture(env);
}