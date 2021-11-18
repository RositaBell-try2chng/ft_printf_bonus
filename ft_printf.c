/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:33:32 by rbell             #+#    #+#             */
/*   Updated: 2021/11/16 16:40:55 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *form, ...)
{
	va_list	arg;
	size_t	i;
	ssize_t	res;
	t_flags	*flgs;

	flgs = malloc(sizeof(t_flags));
	if (!flgs)
		return (print_error(flgs));
	tereshkova(flgs, &i, &res, 1);
	va_start(arg, form);
	while (form[i] && flgs->f_correct == 0)
	{
		res += for_easy_string(form, &i, flgs);
		if (flgs->f_correct != 0)
			break;
		res += for_format_string(&arg, form, flgs, &i);
		i++;
	}
	va_end(arg);
	if (flgs->f_correct != 0)
		return (print_error(flgs));
	free(flgs);
	return (res);
}

