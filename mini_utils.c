/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:51:11 by rbell             #+#    #+#             */
/*   Updated: 2021/11/18 13:51:15 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void tereshkova(t_flags *flg, size_t *p_i, ssize_t *p_res, char begin_flg)
{
	flg->f_correct = 0;
	flg->f_space = 0;
	flg->f_plus = 0;
	flg->f_zero = 0;
	flg->f_minus = 0;
	flg->f_prison = 0;
	flg->f_prec = 0;
	flg->width = 0;
	flg->prec = 0;
	if (begin_flg == 0)
		return ;
	*p_i = 0;
	*p_res = 0;
}

size_t	print_percent(t_flags *flgs) // need corrective
{
	(*i)++;
	if (write(1, "%", 1) < 0)
		flgs->f_correct = 'w';
	return (1);
}

void	print_no_width_x(unsigned long int p, t_flags *flgs, char *base)
{
	if (p/16 > 0)
		print_no_width_x(p/16, flgs, base);
	if (write(1, (base + (p % 16)), 1) < 0)
		flgs->f_correct = 'w';
}

char	*get_base(char *base, char c)
{
	if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789";
	return (base);
}

size_t	count_size(long int n, int base, t_flags *flgs)
{
	size_t	res;

	res = 0;
	if (n <= 0)
		res++;
	while (n != 0)
	{
		n /= base;
		res++;
	}
	if (flgs->f_prison)
		res += 2;
	if (flgs->width > res)
		res = flgs->width;
	if (flgs->f_prec && flgs->prec > res)
		res = flgs->prec;
	return (res);
}