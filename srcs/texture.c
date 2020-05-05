/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:52:39 by rlossy            #+#    #+#             */
/*   Updated: 2020/02/20 10:52:39 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	create_texture(t_env *env)
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

void	read_header(char *filename, t_txt *txt)
{
	FILE	*file;

	if ((file = fopen(filename, "r")) == NULL)
		error("bmp file opening (fopen) failed.");
	fseek(file, 18, SEEK_SET);
	fread(&txt->w, 4, 1, file);
	fread(&txt->h, 4, 1, file);
	fseek(file, 2, SEEK_CUR);
	fread(&txt->bpp, 2, 1, file);
	fclose(file);
	txt->row = txt->w * (txt->bpp / 8);
	txt->w < 0 ? txt->w = -txt->w : 0;
	txt->h < 0 ? txt->h = -txt->h : 0;
	txt->size = txt->row * txt->h;
}

void	get_image(t_txt *txt, char *buff, int i)
{
	int	j;
	int	k;
	int	size;

	k = 0;
	size = txt->size * 2;
	txt->img = (unsigned char*)malloc(sizeof(unsigned char) * size);
	while (i >= 0)
	{
		i -= txt->row;
		j = 0;
		while (j < txt->row)
		{
			txt->img[k + j] = (unsigned char)buff[i + j + 2];
			txt->img[k + j + 1] = (unsigned char)buff[i + j + 1];
			txt->img[k + j + 2] = (unsigned char)buff[i + j];
			j += 3;
		}
		k += txt->row;
	}
}

void	load_bmp(t_env *env, char *filename)
{
	int		fd;
	int		i;
	char	*buff;

	read_header(filename, &env->obj.txt);
	buff = (char*)malloc(sizeof(char) * env->obj.txt.size + 1);
	if ((fd = open(filename, O_RDWR)) == -1)
		error("bmp file opening failed.");
	lseek(fd, 54, SEEK_SET);
	i = read(fd, buff, env->obj.txt.size);
	get_image(&env->obj.txt, buff, i);
	ft_strdel((char**)&buff);
	close(fd);
}