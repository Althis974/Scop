/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	get_image(t_txt *txt, char *buff, int len)
{
	int	i;
	int	j;
	int	size;

	j = 0;
	size = txt->size * 2;
	txt->img = (unsigned char*)malloc(sizeof(unsigned char) * size);
	while (len >= 0)
	{
		len -= txt->row;
		i = 0;
		while (j < txt->row)
		{
			txt->img[j + i] = (unsigned char)buff[len + i + 2];
			txt->img[j + i + 1] = (unsigned char)buff[len + i + 1];
			txt->img[j + i + 2] = (unsigned char)buff[len + i];
			i += 3;
		}
		j += txt->row;
	}
}

void	get_header(char *filename, t_txt *txt)
{
	FILE	*file;

	if ((file = fopen(filename, "r")) == NULL)
		error("Failed to open texture file.");
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

void	load_texture(t_env *env, char *filename)
{
	int		len;
	int		fd;
	char	*buff;

	get_header(filename, &env->obj.txt);
	buff = (char*)malloc(sizeof(char) * env->obj.txt.size + 1);
	if ((fd = open(filename, O_RDWR)) == -1)
		error("Failed to open texture file.");
	lseek(fd, 54, SEEK_SET);
	len = read(fd, buff, env->obj.txt.size);
	get_image(&env->obj.txt, buff, len);
	ft_strdel((char**)&buff);
	close(fd);
}