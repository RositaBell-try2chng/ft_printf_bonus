/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:55:41 by rbell             #+#    #+#             */
/*   Updated: 2021/11/24 10:58:12 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	parse_flags(const char *s, t_flags *flgs, size_t *i)
{
	while (s[++(*i)] == ' ' || s[*i] == '0' || s[*i] == '#' || s[*i] == '-' || \
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
	if (flgs->f_zero == 1 && flgs->f_minus == 1)
		flgs->f_zero = 0;
	if (flgs->f_space == 1 && flgs->f_plus == 1)
		flgs->f_space = 0;
	if (flgs->f_zero == 1 && flgs->f_prec == 1)
		flgs->f_zero = 0;
	return (1);
}

char	parse_num(const char *form, int *a, size_t *i, t_flags *flgs)
{
	unsigned int	res;

	res = 0;
	while (form[*i] >= 48 && form[*i] <= 57)
	{
		res = res * 10 + (form[*i] - 48);
		if (res > (unsigned )INT_MAX)
		{
			flgs->f_correct = 'f';
			return (0);
		}
		(*i)++;
	}
	*a = (int) res;
	return (1);
}

size_t	print_result(va_list *arg, char spec, t_flags *flgs)
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
		return (print_x_num(arg, flgs, spec));
	else
		return (print_percent(flgs));
}

char	check_spec(t_flags *f, char c)
{
	if (c == 'c' && !(f->f_space) && !(f->f_zero) && !(f->f_prison) && \
	!(f->f_plus) && !(f->f_prec))
		return (0);
	if (c == 's' && !(f->f_space) && !(f->f_zero) && !(f->f_prison) && \
	!(f->f_plus))
		return (0);
	if (c == 'p' && !(f->f_space) && !(f->f_zero) && !(f->f_prison) && \
	!(f->f_plus) && !(f->f_prec))
		return (0);
	if ((c == 'd' || c == 'i') && !(f->f_prison))
		return (0);
	if ((c == 'x' || c == 'X') && !(f->f_space) && !(f->f_plus))
		return (0);
	if (c == 'u' && !(f->f_space) && !(f->f_prison) && !(f->f_plus))
		return (0);
	if (c == '%' && !(f->f_space) && !(f->f_zero) && !(f->f_prison) && \
	!(f->f_plus) && !(f->f_prec) && !(f->f_minus))
		return (0);
	return (1);
}
