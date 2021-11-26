/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:06:19 by rbell             #+#    #+#             */
/*   Updated: 2021/11/24 11:06:37 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	add_to_empty_str(char *s, t_flags *flgs, size_t *t)
{
	if (flgs->f_space)
		s[0] = ' ';
	else
		s[0] = '+';
	if ((size_t)(flgs->width) > (*t))
		(*t) = flgs->width;
	return (1);
}

size_t	add_di_plus_or_space(char *s, t_flags *flgs, int i, size_t *t)
{
	char	*s2;
	size_t	res;

	if ((*t) == 0)
	{
		s[!(++(*t))] = '\0';
		return (add_to_empty_str(s, flgs, t));
	}
	res = i + 1;
	s2 = s + 1;
	while (i > 0)
	{
		s2[i] = s[i];
		i--;
	}
	s2[i] = s[i];
	if (flgs->f_plus)
		s[0] = '+';
	else
		s[0] = ' ';
	return (res);
}
