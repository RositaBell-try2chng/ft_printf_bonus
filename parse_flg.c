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

static char	parse_flags(char *s, t_flags *flgs, size_t *i)
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
		return (0);
	}
	return (1);
}

static char	parse_num(char *form, int *a, size_t *i, t_flags *flgs)
{
	unsigned int	res;
	size_t			tmp_i;

	res = 0;
	tmp_i = *i;
	while (form[*i] >= 48 && form[*i] <= 57)
	{
		res = res * 10 + (form[*i] - 48);
		(*i)++;
		if (*i - tmp_i > 10)
			break;
	}
	if (res > INT_MAX)
	{
		flgs->f_correct = 'f';
		return (0);
	}
	*a = (int) res;
	return (1);
}

ssize_t	print_result(va_list *arg, char spec, t_flags *flgs)
{
	if (spec == 'c')
		return (print_char(arg, flgs));
	else if (spec == 's')
		return (print_string(arg, flgs));
	else if (spec == 'p')
		return (print_ptr(arg, flgs));
	else if (spec == 'd' || spec == 'i')
		return (print_num(arg, flgs));
	else if (spec == 'u')
		return (print_u_num(arg, flgs));
	else if (spec == 'x' || spec == 'X')
		return (print_x_num(arg, flgs));
	else
		return (print_percent(flgs));
}

ssize_t for_format_string(va_list *arg, char *form, t_flags *flgs, size_t *i)
{
	if (parse_flags(form, flgs, i) == 0)
		return (1);
	if (parse_num(form, &(flgs->width), i, flgs) == 0)
		return (1);
	if (form[*i] == '.')
	{
		(*i)++;
		flgs->f_prec = 1;
		if (parse_num(form, &(flgs->prec), i, flgs) == 0)
			return (1);
	}
	if (check_spec(flgs, form[*i]))
	{
		flgs->f_correct = 'f';
		return (1);
	}
	return (print_result(arg, form[(*i)++], flgs));
}