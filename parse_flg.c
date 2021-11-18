/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:55:41 by rbell             #+#    #+#             */
/*   Updated: 2021/11/18 16:55:46 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static ssize_t	parse_flags(char *s, t_flags *flgs, size_t *i)
{
	while (s[++*i] == ' ' || s[*i] == '0' || s[*i] == '#' || s[*i] == '-' ||
	s[*i] == '+')
	{
		if (s[*i] == ' ')
			flgs->f_space = 1;
		else if (s[*i] == '0')
			flgs->f_zero = 1;
		else if (s[*i] == '#')
			flgs->f_prison = 1;
		else if (s[*i] == '-')
			flgs->f_minus = 1;
		else
			flgs->f_plus = 1;
	}
	if ((flgs->f_zero == 1 && flgs->f_minus == 1) || (flgs->f_space == 1 && \
	flgs->f_plus == 1))
	{
		flgs->f_correct = 'f';
		return (-1);
	}
	return (1);
}

ssize_t for_format_string(va_list *arg, char *form, t_flags *flgs, size_t *i)
{
	if (parse_flags(form, flgs, i) < 0)
		return (1);
	if (parse_width(form, flgs, i) < 0)
		return (1);
	if (parse_prec() < 0)
		return (1);
	if (check_spec(flgs, form[i]))
	{
		flgs->f_correct = 'f';
		return (1);
	}
	return (res);
}