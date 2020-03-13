/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:52:39 by rlossy            #+#    #+#             */
/*   Updated: 2020/02/20 10:52:39 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"
/*
t_shader	initShader(char *vrtxScr, char *frgmtSrc)
{
	t_shader shader;

	shader.vrtxID = 0;
	shader.frgmtID = 0;
	shader.prgmID = 0;
	shader.vrtxScr = vrtxScr;
	shader.frgmtSrc = frgmtSrc;
	return (shader);
}

int			loadShader(t_shader *shader)
{
	// Delete possible old shader
	if(glIsShader(shader->vrtxID) == GL_TRUE)
		glDeleteShader(shader->vrtxID);
	if(glIsShader(shader->frgmtID) == GL_TRUE)
		glDeleteShader(shader->frgmtID);
	if(glIsProgram(shader->prgmID) == GL_TRUE)
		glDeleteProgram(shader->prgmID);

	// Compile shaders
	if((shader->vrtxID = compileShader(shader->vrtxID, GL_VERTEX_SHADER, shader->vrtxScr)) < 0)
		return (-1);
	if((shader->frgmtID = compileShader(shader->frgmtID, GL_FRAGMENT_SHADER, shader->frgmtSrc)) < 0)
		return (-1);

	// Create program
	shader->prgmID = glCreateProgram();

	// Attach shaders
	glAttachShader(shader->prgmID, shader->vrtxID);
	glAttachShader(shader->prgmID, shader->frgmtID);

	// Lock shaders
	glBindAttribLocation(shader->prgmID, 0, "in_Vertex");
	glBindAttribLocation(shader->prgmID, 1, "in_Color");
	glBindAttribLocation(shader->prgmID, 2, "in_TexCoord0");

	// Link program
	glLinkProgram(shader->prgmID);

	// Check successful link
	GLint linkError;
	glGetProgramiv(shader->prgmID, GL_LINK_STATUS, &linkError);
	if(linkError != GL_TRUE)
	{
		// Get error length
		GLint errorLength;
		glGetProgramiv(shader->prgmID, GL_INFO_LOG_LENGTH, &errorLength);

		// Malloc
		char *err;
		if (!(err = malloc((errorLength + 1) * sizeof(char*))))
			return (-1);

		// Get error
		glGetShaderInfoLog(shader->prgmID, errorLength, &errorLength, err);
		err[errorLength] = '\0';

		// Print error
		error(err);

		// Free
		free(err);
		glDeleteProgram(shader->prgmID);
		return (-1);
	}
	else
		return (0);
}

int			compileShader(GLuint shader, GLenum type, char *filename)
{
	// Create shader
	shader = glCreateShader(type);

	// Check shader
	if(!shader)
	{
		write(2, "Error: shader type (", 20);
		ft_putnbr_fd(type, 2);
		write(2, ") doesn't exist.\n", 17);
		return (-1);
	}

	// Open file
	FILE *f;
	f = fopen(filename, "r");
	if (!f)
	{
		write(2, "Error: Unable to open shader file ", 34);
		ft_putstr_fd(filename, 2);
		write(2, ". Aborting.\n", 12);
		return (-1);
	}

	// Read file
	size_t len = 0;
	ssize_t read;
	char *line = NULL;
	char *srcShader = NULL;

	while((read = getline(&line, &len, f)) != -1)
	{
		if (srcShader != NULL)
			srcShader = ft_strjoin(srcShader, line, 1);
		else
			srcShader = ft_strdup(line);
	}
	if (line)
		free(line);

	// Get source code
	const GLchar* srcCode = srcShader;

	// Send source code to shader
	glShaderSource(shader, 1, &srcCode, 0);

	// Compilation du shader
	glCompileShader(shader);
	free(srcShader);

	// Check compile
	GLint compileError;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileError);

	// Check error
	if(compileError != GL_TRUE)
	{
		// Get error length
		GLint errorLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);

		// Malloc
		char *error;
		if (!(error = malloc((errorLength + 1) * sizeof(char*))))
			return (-1);

		// Get error
		glGetShaderInfoLog(shader, errorLength, &errorLength, error);
		error[errorLength] = '\0';

		// Print error
		ft_putstr_fd(error, 2);
		write(2, "\n", 1);

		// Free
		free(error);
		glDeleteProgram(shader);
		return (-1);
	}
	else
		return (shader);
}
*/


void			update_shader_uniforms(t_env *env)
{
	glUniformMatrix4fv(env->shader.mvploc, 1, GL_FALSE, env->sim.mvp.m);
	//glUniform1i(env->shader.smdloc, env->mod.shading);
	//glUniform1i(env->shader.cmdloc, env->mod.color);
	//glUniform1i(env->shader.gmdloc, env->mod.greyscale);
	//glUniform1i(env->shader.mmdloc, env->mod.mapping);
	//glUniform1i(env->shader.tmdloc, env->mod.texture);
}

const GLchar	*get_shader_source(char *filename)
{
	int		fd;
	int		ret;
	char	buffer[BUFFER_SIZE];
	char	*source;
	char	*del;

	source = ft_strnew(BUFFER_SIZE);
	if ((fd = open(filename, O_RDONLY)) == -1)
		error("shader source file opening failed.");
	while ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = '\0';
		del = source;
		source = ft_strjoin(source, buffer, 0);
		ft_strdel(&del);
	}
	close(fd);
	return (source);
}

GLuint			create_shader(char *filename, int shader_type)
{
	GLint			success;
	GLuint			shader;
	const GLchar	*shader_source;

	shader_source = get_shader_source(filename);
	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);
	free((void*)shader_source);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
		error("shader compilation failed.");
	return (shader);
}

GLuint			create_shader_program(GLuint shader_vert, GLuint shader_frag)
{
	GLint	success;
	GLuint	shader_program;

	shader_program = glCreateProgram();
	glAttachShader(shader_program, shader_vert);
	glAttachShader(shader_program, shader_frag);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
		error("shader program compilation failed.");
	glDeleteShader(shader_vert);
	glDeleteShader(shader_frag);
	return (shader_program);
}

void			build_shader_program(t_env *env)
{
	GLuint	shader_vert;
	GLuint	shader_frag;

	shader_vert = create_shader("./Shaders/vertex.glsl", GL_VERTEX_SHADER);
	shader_frag = create_shader("./Shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	env->shader.program = create_shader_program(shader_vert, shader_frag);
	env->shader.mvploc = glGetUniformLocation(env->shader.program, "mvp");
	//env->shader.smdloc = glGetUniformLocation(env->shader.program, "smod");
	//env->shader.cmdloc = glGetUniformLocation(env->shader.program, "cmod");
	//env->shader.tmdloc = glGetUniformLocation(env->shader.program, "tmod");
	//env->shader.gmdloc = glGetUniformLocation(env->shader.program, "gmod");
	//env->shader.mmdloc = glGetUniformLocation(env->shader.program, "mmod");
	//env->shader.texloc = glGetUniformLocation(env->shader.program, "ltexture");
}
