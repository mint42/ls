/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:16:12 by rreedy            #+#    #+#             */
/*   Updated: 2019/02/20 16:35:47 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

/*
** flag bits:                                  ^- 0+ #
** type bits:  lLhH jzgG eEfF cCsS dDiI bBoO uUxX pP%(
*/

# define VALID_FMTS "gGeEfFcCsSpPdDiIbBoOuUxX%lLhHjz1234567890.+- #*()"

# define S sub->s
# define FLAGS sub->flags
# define TYPE sub->type
# define BASE sub->base
# define PREC sub->p
# define WIDTH sub->w
# define JUST sub->j
# define LEN sub->len

typedef struct		s_sub
{
	char			*s;
	unsigned int	flags;
	unsigned int	type;
	unsigned int	base;
	int				p;
	int				w;
	int				j;
	size_t			len;
}					t_sub;

char				*clean(char *s, t_sub sub, char **fmt, size_t *slen);
int					ft_printf(const char *fmt, ...);
int					ft_sprintf(char **s, const char *fmt, ...);
int					ft_printfd(int fd, const char *fmt, ...);

t_sub				make_tsub(char **fmt, va_list ap, int init);

char				*parse(t_sub *sub, va_list ap);
char				*parse_bouxp(t_sub *sub, va_list ap);
char				*parse_di(t_sub *sub, va_list ap);
char				*parse_efg(t_sub *sub, va_list ap);
char				*parse_unicode(t_sub *sub, va_list ap);
char				*parse_csp(t_sub *sub, va_list ap);

char				*crop_di(t_sub *sub);
char				*crop_bouxp(t_sub *sub);
char				*crop_efg(t_sub *sub);
char				*crop_csp(t_sub *sub);
char				*crop_unicode(t_sub *sub);

#endif
