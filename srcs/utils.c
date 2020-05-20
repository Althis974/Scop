
#include "../includes/scop.h"

void		usage()
{
	write(2, "usage : ./scop <filename>\n", 26);
}

void		error(const char *err)
{
	write(2, "Error: ", 7);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
	exit(1);
}

char		**file_checker(t_env *env, char *line, int *len, char c)
{
	int 	tmp;
	char	**tab;

	tab = ft_strsplit(&line[1], ' ');

	tmp = get_tab_len((void**)tab);

	if ((c == 'v' && tmp != 3) || (c == 'f' && (tmp < 3 || tmp > 4)))
		error("Erroneous data.");

	if (c == 'f')
	{
		*len = tmp == 4 ? 6 : 3;
		env->obj.f_len += *len;
	}

	return (tab);
}
