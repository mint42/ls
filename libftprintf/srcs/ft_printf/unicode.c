/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 21:30:44 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/14 22:50:10 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		precision_unicode(t_sub *sub)
{
	int		i;

	i = 0;
	if (FLAGS & 0x40 && PREC < 6)
		S[0] = '\0';
	while (S[i] != '\0' && PREC)
	{
		++i;
		while (S[i] && (S[i] & 0xC0) == 0x80)
			++i;
		--PREC;
	}
	S[i] = '\0';
}

static void		width_unicode(t_sub *sub)
{
	if ((size_t)JUST > (size_t)WIDTH - LEN)
		JUST = WIDTH - LEN;
	if (!(FLAGS & 0x30))
		JUST = WIDTH - JUST - LEN;
	else if ((FLAGS & 0x30) == 0x30)
		JUST = (WIDTH - LEN) / 2;
	else if (FLAGS & 0x20)
		JUST = ((WIDTH - LEN) / 2) + (((WIDTH - LEN) % 2) ? 1 : 0);
	if (TYPE & 0xC0000 && FLAGS & 0x40)
	{
		S = ft_shift(&S, JUST, WIDTH);
		S[JUST] = '\0';
	}
	else
		S = ft_shift(&S, JUST, WIDTH);
	LEN = WIDTH;
}

char			*crop_unicode(t_sub *sub)
{
	int		i;

	i = 0;
	if (PREC >= 0 && !(TYPE & 0x40000))
		precision_unicode(sub);
	while (S[i] && ++i)
		while (S[i] && (S[i] & 0xC0) == 0x80 && ++i)
			++WIDTH;
	LEN = (TYPE & 0x40000 && FLAGS & 0x40) ? 1 : ft_strlen(S);
	if ((size_t)WIDTH > LEN)
		width_unicode(sub);
	return (S);
}
