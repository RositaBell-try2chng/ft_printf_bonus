/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:11:19 by rbell             #+#    #+#             */
/*   Updated: 2021/11/24 11:12:14 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static char	*create_x_w_left(char *s, t_flags *flgs, int i)
{
	while (i < flgs->width)
	{
		s[i] = ' ';
		i++;
	}
	s[i] = '\0';
	return (s);
}

static char	*create_x_w_right(char *s, t_flags *flgs, size_t i, char c)
{
	size_t	j;
	char	*s2;

	j = 0;
	s2 = s + flgs->width - (i - 2 * (flgs->f_prison));
	while (s[j])
		j++;
	s2[j] = '\0';
	while (--j > 0)
		s2[j] = s[j];
	s2[j] = s[j];
	j--;
	while ((s + (++j) + (2 * (flgs->f_prison))) < s2)
		s[2 * flgs->f_prison + j] = c;
	return (s);
}

char	*create_x_w_string(char *s, t_flags *flgs, size_t i)
{
	if (flgs->f_minus)
		s = create_x_w_left(s, flgs, i);
	else if (flgs->f_zero)
		s = create_x_w_right(s, flgs, i, '0');
	else
		s = create_x_w_right(s, flgs, i, ' ');
	return (s);
}
