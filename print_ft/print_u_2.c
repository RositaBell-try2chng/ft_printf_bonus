/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:10:01 by rbell             #+#    #+#             */
/*   Updated: 2021/11/24 11:10:10 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static char	*create_u_w_left(char *s, t_flags *flgs, size_t i)
{
	while (i < (size_t)(flgs->width))
	{
		s[i] = ' ';
		i++;
	}
	s[i] = '\0';
	return (s);
}

static char	*create_u_w_right(char *s, t_flags *flgs, size_t i, char c)
{
	size_t	j;
	char	*s2;
	char	flg;

	j = 0;
	flg = ((s[0] == '-' || s[0] == ' ') && flgs->f_zero);
	s2 = s + flgs->width - i;
	while (s[j])
		j++;
	s2[j + flg] = '\0';
	while ((--j - flg) > 0)
		s2[j] = s[j];
	s2[j] = s[j];
	j--;
	while ((s + (++j)) < s2 + flg)
		s[j] = c;
	return (s);
}

char	*create_u_w_string(char *s, t_flags *flgs, size_t i)
{
	if (flgs->f_minus)
		s = create_u_w_left(s, flgs, i);
	else if (flgs->f_zero)
		s = create_u_w_right(s, flgs, i, '0');
	else
		s = create_u_w_right(s, flgs, i, ' ');
	return (s);
}

char	*get_base(char spec, char **base)
{
	if (spec == 'x')
		*base = "0123456789abcdefx";
	else
		*base = "0123456789ABCDEFX";
	return(*base);
}