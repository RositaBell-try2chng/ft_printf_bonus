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

int print_error(t_flags *flgs)
{
	if (!flgs || flgs->f_correct == 'm')
		write(2, "malloc error\n", 13);
	else if (flgs->f_correct == 'w')
		write(2, "write error\n", 12);
	else if (flgs->f_correct == 'f')
		write(2, "format error\n", 13);
	free(flgs);
	return (-1);
}

ssize_t	for_easy_string(const char *form, size_t *p_i, t_flags *flgs)
{
	ssize_t	res;

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

ssize_t	print_percent(t_flags *flgs) // need corrective
{
	(*i)++;
	if (write(1, "%", 1) < 0)
		flgs->f_correct = 'w';
	return (1);
}

char check_spec(t_flags *f, char c) //need correct
{
	if (c == 'c' && !(f->f_space) && !(f->f_zero) && !(f->f_prison) && \
	!(f->f_plus) && !(f->f_prec))
		return (0);
	else if (c == 's' && !(f->f_space) && !(f->f_zero) && !(f->f_prison) && \
	!(f->f_plus))
		return (0);
	else if (c == 'p' && !(f->f_space) && !(f->f_zero) && !(f->f_prison) && \
	!(f->f_plus) && !(f->f_prec))
		return (0);
	else if ((c == 'd' || c == 'i') && !(f->f_prison))
		return (0);
	else if ((c == 'x' || c == 'X') && !(f->f_space) && !(f->f_plus))
		return (0);
	else if (c == 'u' && !(f->f_space) && !(f->f_prison) && !(f->f_plus))
		return (0);
	else if (c == '%' && !(f->f_space) && !(f->f_zero) && !(f->f_prison) && \
	!(f->f_plus) && !(f->f_prec) && !(f->f_minus))
		return (0);
	return (1);
}