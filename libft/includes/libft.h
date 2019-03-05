/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:16:02 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/04 17:48:27 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include "ft_binarytree.h"
# include "ft_printf.h"

# define SIGFIGS_I (f.len_i + f.trail_zeros)
# define SIGFIGS_F (f.len_f + f.lead_zeros)

typedef	union		u_double
{
	double			d;
	long int		l;
}					t_double;

typedef	struct		s_fp
{
	long			integer;
	long			fraction;
	int				len_i;
	int				len_f;
	int				lead_zeros;
	int				trail_zeros;
}					t_fp;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

long long int		ft_abs(long long int n);
double				ft_absd(double n);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t len);
int					ft_ceiling(double n);
unsigned int		ft_count_c(char *s, char c);
char				*ft_crop(char **s, int in, size_t len);
char				*ft_ctoa(int c);
int					ft_cw(const char *s, int c);
void				ft_delete_double_array(char ***double_array);
double				ft_dpow(int n, int exponent);
int					ft_floor(double n);
char				*ft_ftoa(double n, int precision);
char				*ft_ftosn(double n, int precision);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_islower(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
char				*ft_itoa(int n);
char				*ft_itoabase(long long int n, int base);
void				ft_lstadd(t_list **head, t_list *link);
void				ft_lstdel(t_list **list, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **link, void (*del)(void *, size_t));
void				ft_lstiter(t_list *list, void (*f)(t_list *link));
t_list				*ft_lstmap(t_list *list, t_list *(*f)(t_list *link));
t_list				*ft_lstnew(const void *content, size_t content_size);
void				*ft_memalloc(size_t size);
void				*ft_memcat(void *d, const void *s, size_t dl, size_t sl);
void				*ft_memccpy(void *dst, const void *src, int c, size_t len);
void				*ft_memchr(const void *s, int c, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t len);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *ptr, int c, size_t len);
void				*ft_memsec(void *ptr, int c, size_t len);
size_t				ft_numlen(long long int n);
size_t				ft_numlen_sign(long long int n);
size_t				ft_pow(int n, int exponent);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(const char *s);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(const char *s);
void				ft_putstr_fd(const char *s, int fd);
long				ft_round(double n);
char				*ft_shift(char **s, int i, size_t size);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strchrs(const char *s, const char *cs);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
int					ft_strequ(const char *s1, const char *s2);
char				*ft_strinit(int c, size_t len);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(const char *s1, const char *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
size_t				ft_strlend(const char *s, int c);
char				*ft_strmap(const char *s, char (*f)(char));
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t len);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_strnequ(const char *s1, const char *s2, size_t len);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strrchrb(const char *s, int c);
char				**ft_strsplit(const char *s, char c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strtrim(const char *s);
char				*ft_strlower(char *s);
char				*ft_strupper(char *s);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_uitoabase(unsigned long long int n, int base);
size_t				ft_unumlen(unsigned long long int n);

char				*conv_utf8_char(wchar_t wc, char *s);
char				*conv_utf8_str(wchar_t *ws, char *s);

#endif
