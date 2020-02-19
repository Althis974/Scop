/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shader.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/18 10:09:42 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/18 10:09:42 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
	{
		printf("nique");
		return (-1);
	}

	printf("vrtxID %d\n", shader->vrtxID);

	if((shader->frgmtID = compileShader(shader->frgmtID, GL_FRAGMENT_SHADER, shader->frgmtSrc)) < 0)
	{
		printf("tamere");
		return (-1);
	}

	printf("frgmtID %d\n", shader->frgmtID);

	// Create program
	shader->prgmID = glCreateProgram();


	// Attach shaders
	glAttachShader(shader->prgmID, shader->vrtxID);
	glAttachShader(shader->prgmID, shader->frgmtID);


	// Lock shaders
	glBindAttribLocation(shader->prgmID, 0, "in_position");
	//glBindAttribLocation(shader->prgmID, 1, "in_Color");
	//glBindAttribLocation(shader->prgmID, 2, "in_TexCoord0");


	// Link program
	glLinkProgram(shader->prgmID);


	// Check successful link
	GLint linkError;
	glGetProgramiv(shader->prgmID, GL_LINK_STATUS, &linkError);

	printf("yo %d\n", shader->prgmID);

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


	FILE *f;
	f = fopen(filename, "r");
	if (!f)
	{
		fprintf(stderr, "Unable to open shader file %s. Aborting.\n", filename);
		return (-1);
	}

	size_t len = 0;
	ssize_t read;
	char *line = NULL;
	char *srcCode = NULL;

	while((read = getline(&line, &len, f)) != -1)
	{
		//printf("line = %s", line);
		if (srcCode != NULL)
			srcCode = ft_strjoin(srcCode, line, 0);
		else
		{
			if (!(srcCode = malloc((ft_strlen(line) + 1) * sizeof(char*))))
				return (-1);
			srcCode = ft_strcpy(srcCode, line);
		}
		//printf("srcCode = %s", srcCode);
	}

	printf("srcCode:\n%s\n", srcCode);

	// Flux de lecture
	//std::ifstream fichier(fichierSource.c_str());
/*
	int		fd;

	// Test d'ouverture

	printf("bouya");

	if((fd = (open(filename, O_RDONLY))) == -1)
	{
		printf("Error: %s is missing.\n", filename);
		glDeleteShader(shader);

		return (-1);
	}

	printf("bouyata");

	// Strings permettant de lire le code source

	int		ret;
	char 	*line;
	char 	*srcCode;


	// Lecture

	//while(getline(fichier, line))
	//	srcCode += line + '\n';

	ret = get_next_line(fd, &line);
	printf("poto: %s", line);
	free(line);

	if ((ret == 0) || (ret == -1))
	{
		printf("Error: %s is wrong.\n", filename);
		glDeleteShader(shader);

		return (-1);
	}

	while (get_next_line(fd, &line))
	{
		printf("pota: %s", line);
		free(line);
	}

	if ((close(fd)) == -1)
	{
		printf("Error: can't close %s\n", filename);
		glDeleteShader(shader);

		return (-1);
	}


	// Fermeture du fichier

	//fichier.close();


	char *tmp;

	fd = (open(filename, O_RDONLY));
	ret = get_next_line(fd, &line);
	tmp = line;
	while (get_next_line(fd, &line))
	{
		//printf("line = %s", line);
		srcCode = ft_strjoin(tmp, line, 0);
	}
	//printf("%s\n", srcCode);
	srcCode += '\0';
	close(fd);
*/

	//printf("after: srcCode = %s\n", srcCode);

	// RÈcupÈration de la chaine C du code source

	//const GLchar* chaineCodeSource = srcCode.c_str();

	const GLchar* chaineCodeSource = srcCode;

	printf("chaineCodeSource:\n%s\n", chaineCodeSource);

	// Envoi du code source au shader

	glShaderSource(shader, 1, &chaineCodeSource, 0);


	// Compilation du shader
	glCompileShader(shader);

	printf("shader = %d\n", shader);

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
		printf("SHADER: %s\n", error);


		// Free
		free(error);
		glDeleteProgram(shader);

		return (-1);
	}
	else
		return (shader);
}
