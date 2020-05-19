
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

char		**file_checker(char *line, char c)
{
	int 	len;
	char	**tab;

	tab = ft_strsplit(&line[1], ' ');

	len = get_tab_len((void**)tab);

	if ((c == 'v' && len != 3) || (c == 'f' && (len < 3 || len > 4)))
		error("Erroneous data.");

	return (tab);
}