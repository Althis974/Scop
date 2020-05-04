/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:04:50 by rlossy            #+#    #+#             */
/*   Updated: 2020/02/20 14:04:51 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <wchar.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <math.h>

# define BUFF_SIZE 1000

# define ID 0x6964
# define AXX 0
# define AXY 1
# define AXZ 2

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

/*
**	[Vector structure]
**
**	Basic name for 3 axes
*/

typedef struct		s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

/*
**	[Matrix structure]
**
**	m is a 4*4 matrix
*/

typedef struct		s_mat
{
	float			m[16];
}					t_mat;

/*
**	[Color structure]
**
**	Shade of color from RGB
*/

typedef struct		s_col
{
	double			red;
	double			green;
	double			blue;
}					t_col;

char				*ft_strdup(const char *src);
size_t				ft_strlen(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_atoi(const char *str);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack,
					const char *needle, size_t len);

void				ft_putnbr(int n);
void				ft_putallnbr(intmax_t n);
void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
char				*ft_itoa(int n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char *s1, char *s2, int free);
char				**ft_strsplit(char const *s, char c);
char				*ft_strtrim(char const *s);

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int					ft_str_is_alpha(const char *s);
int					ft_str_is_numeric(const char *s);
int					ft_str_is_printable(const char *s);
int					ft_str_is_lowercase(const char *s);
int					ft_str_is_uppercase(const char *s);
int					ft_isblank(int c);
int					ft_iscntrl(int c);
int					ft_isgraph(int c);
void				ft_str_capitalizer(char *s);
intmax_t			ft_abs(intmax_t n);
void				ft_print_hex(unsigned int n);
void				ft_print_base_upp(uintmax_t n, uintmax_t base);
void				ft_print_base_low(uintmax_t n, uintmax_t base);
void				ft_swap(void *const a, void *const b, size_t size);
void				ft_sort_int_tab(int *tab, unsigned int size);
char				*ft_itoa_base(int value, int base);
int					ft_get_len(intmax_t val, int base);
int					ft_get_len_sign(intmax_t val, int base);
int					ft_putnstr(char const *s, size_t len);
void				ft_putwchar(wchar_t c);
void				ft_putwstr(wchar_t *s);
void				ft_putallnbr_allsign(intmax_t n);
void				ft_putallnbr_nosign(intmax_t n);
int					ft_atoisign(const char *str);
char				*ft_itoasign(int n);
void				ft_get_print_len(uintmax_t n, uintmax_t base,
					size_t *len);
size_t				ft_wstrlen(wchar_t *s);
int					ft_putnwstr(wchar_t const *s, size_t len);
int					ft_isvalid_conv(int c);
int					ft_isalnocast(int c);
size_t				ft_wcharlen(wchar_t c);
size_t				ft_wcharnput(wchar_t const *s, size_t len, int print);
int					get_next_line(const int fd, char **line);
int					ft_word_count(const char *s, char c);
int					**ft_tab2d_init(size_t x, size_t y);
double				ft_reg(double x, double min, double max);
char				*ft_ftoa(double nb);
double				ft_atof(const char *s);
double				ft_pow(double nb, int exp);
int					get_tab_len(void **tab);

t_vec				ft_vadd(t_vec *v1, t_vec *v2);
t_vec				ft_vsub(t_vec *v1, t_vec *v2);
t_vec				ft_vmul(t_vec *v1, t_vec *v2);
t_vec				ft_vdiv(t_vec *v1, t_vec *v2);

t_vec				ft_vaddx(t_vec *v1, double x);
t_vec				ft_vsubx(t_vec *v1, double x);
t_vec				ft_vmulx(t_vec *v1, double x);
t_vec				ft_vdivx(t_vec *v1, double x);

t_vec				ft_vcross(t_vec *v1, t_vec *v2);
t_vec				ft_vreflect(t_vec *intensity, t_vec *normal);
void				ft_vnorm(t_vec *v);
void				ft_vreg(t_vec *v, double a, double b);
double				ft_vdot(t_vec *v1, t_vec *v2);
double				ft_vlen(t_vec *v);
double				ft_vdist(t_vec *v1, t_vec *v2);
t_vec				convec(double x, double y, double z);
void				vcpy(t_vec *v1, t_vec *v2);
t_mat				mat_rot_axis(t_mat m, int axis, double angle);

void	set_mat(t_mat *m, float f);
t_mat	ft_matmul(t_mat *a, t_mat *b);
t_mat	ft_matranspose(t_mat *m);

#endif
