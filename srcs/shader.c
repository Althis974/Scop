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

int		loadShader(t_shader *shader)
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
		char *error;

		if (!(error = malloc((errorLength + 1) * sizeof(char*))))
			return (-1);


		// Get error
		glGetShaderInfoLog(shader->prgmID, errorLength, &errorLength, error);
		error[errorLength] = '\0';


		// Print error
		printf("%s", error);


		// Free
		free(error);
		glDeleteProgram(shader->prgmID);

		return (-1);
	}
	else
		return (0);
}

int					compileShader(GLuint shader, GLenum type, char *filename)
{
	// Create shader
	shader = glCreateShader(type);

	// Check shader
	if(!shader)
	{
		printf("Error: shader type ( %u ) doesn't exist.\n", type);
		return (-1);
	}

	// Open file
	FILE *f;
	f = fopen(filename, "r");
	if (!f)
	{
		fprintf(stderr, "Unable to open shader file %s. Aborting.\n", filename);
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
		printf("%s\n", error);


		// Free
		free(error);
		glDeleteProgram(shader);

		return (-1);
	}
	else
	{
		return (shader);
	}
}
