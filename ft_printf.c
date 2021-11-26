/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:33:32 by rbell             #+#    #+#             */
/*   Updated: 2021/11/24 10:52:01 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *form, ...)
{
	va_list	arg;
	size_t	i;
	size_t	res;
	t_flags	*flgs;

	flgs = malloc(sizeof(t_flags));
	if (!flgs)
		return (print_error(flgs));
	tereshkova(flgs, &i, &res, 1);
	va_start(arg, form);
	while (form[i] && flgs->f_correct == 0)
	{
		tereshkova(flgs, &i, &res, 0);
		res += for_easy_string(form, &i, flgs);
		if (flgs->f_correct != 0)
			break ;
		if (form[i] == '%')
			res += for_format_string(&arg, form, flgs, &i);
	}
	va_end(arg);
	if (flgs->f_correct != 0)
		return (print_error(flgs));
	free(flgs);
	return ((int)res);
}

size_t	for_easy_string(const char *form, size_t *i, t_flags *flgs)
{
	size_t	res;

	res = 0;
	while (form[*i] != '%' && form[*i])
	{
		flgs->tmp_res = write(1, (form + (*i)), 1);
		if (flgs->tmp_res < 0)
			flgs->f_correct = 'w';
		res += flgs->tmp_res;
		(*i)++;
	}
	return (res);
}

size_t	for_format_string(va_list *arg, const char *form, t_flags *flgs, \
		size_t *i)
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

int	print_error(t_flags *flgs)
{
	if (!flgs || flgs->f_correct == 'm')
		write(2, "malloc error\n", 13);
	else if (flgs->f_correct == 'w')
		write(2, "write error\n", 12);
	else if (flgs->f_correct == 'f')
		write(2, "format error\n", 13);
	else if (flgs->f_correct == 'r')
		write(2, "flags repeat\n", 13);
	free(flgs);
	return (-1);
}
