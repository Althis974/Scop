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
	glUniformMatrix4fv(env->shader.mvploc, 1, GL_FALSE, env->live.mvp.m);
	glUniform1i(env->shader.apploc, env->event.txt);
	glUniform1i(env->shader.colloc, env->event.col);
	glUniform1i(env->shader.itploc, env->event.itp);
}

const GLchar	*get_src_shader(char *filename)
{
	int		fd;
	int		ret;
	char	buff[BUFFER_SIZE];
	char	*src;
	//char	*del;

	src = ft_strnew(BUFFER_SIZE);
	if ((fd = open(filename, O_RDONLY)) == -1)
		error("Failed to open shader file.");
	while ((ret = read(fd, buff, BUFFER_SIZE)))
	{
		buff[ret] = '\0';
		//del = src;
		src = ft_strjoin(src, buff, 1);
		//ft_strdel(&del);
	}
	close(fd);
	return (src);
}

GLuint			create_shader(char *filename, int shader_type)
{
	GLint			compile_err;
	GLuint			shader;
	const GLchar	*src_shader;

	src_shader = get_src_shader(filename);
	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &src_shader, NULL);
	glCompileShader(shader);
	free((void*)src_shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_err);
	if (!compile_err)
		error("shader compilation failed.");
	return (shader);
}

void			create_shader_program(t_env *env)
{
	GLint	link_err;

	env->shader.prgmID = glCreateProgram();
	glAttachShader(env->shader.prgmID, env->shader.vrtxID);
	glAttachShader(env->shader.prgmID, env->shader.fragID);
	glLinkProgram(env->shader.prgmID);
	glGetProgramiv(env->shader.prgmID, GL_LINK_STATUS, &link_err);
	if (!link_err)
		error("shader program compilation failed.");
	glDeleteShader(env->shader.vrtxID);
	glDeleteShader(env->shader.fragID);
}

void			build_shader_program(t_env *env)
{
	env->shader.vrtxID = create_shader("./Shaders/vertex.glsl", GL_VERTEX_SHADER);
	env->shader.fragID = create_shader("./Shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	create_shader_program(env);
	env->shader.mvploc = glGetUniformLocation(env->shader.prgmID, "mvp");
	env->shader.apploc = glGetUniformLocation(env->shader.prgmID, "apply");
	env->shader.txtloc = glGetUniformLocation(env->shader.prgmID, "txt");
	env->shader.colloc = glGetUniformLocation(env->shader.prgmID, "color");
	env->shader.itploc = glGetUniformLocation(env->shader.prgmID, "inter");
}
