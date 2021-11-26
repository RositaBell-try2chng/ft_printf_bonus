/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:05:20 by rbell             #+#    #+#             */
/*   Updated: 2021/11/24 11:06:04 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	count_di_i(char *s, int *i, int num)
{
	if (num == 0)
	{
		(*i)++;
		return ;
	}
	else if (num < 0)
	{
		(*i)++;
		s[0] = '-';
	}
	while (num != 0)
	{
		num /= 10;
		(*i)++;
	}
}

static void	di_to_a(int num, size_t i, char *s)
{
	if (num >= 10)
		di_to_a(num / 10, i - 1, s);
	else if (num <= -10)
		di_to_a(num / (-10), i - 1, s);
	if (num >= 0)
		s[i] = num % 10 + '0';
	else
		s[i] = -(num % 10) + '0';
}

static void	add_di_prec(char *s, t_flags *flgs, int *i)
{
	size_t	j;
	char	*s2;
	char	flg;

	j = 0;
	flg = (s[0] == '-');
	s2 = s + flgs->prec - (*i - flg);
	while (s[j])
		j++;
	s2[j + flg] = '\0';
	while ((--j - flg) > 0)
		s2[j] = s[j];
	s2[j] = s[j];
	j--;
	while ((s + (++j)) < s2 + flg)
		s[j] = '0';
	*i = flgs->prec + flg;
}

static char	*create_di_string(char *s, t_flags *flgs, long int num, size_t *t)
{
	int	i;

	i = 0;
	count_di_i(s, &i, num);
	s[i] = '\0';
	di_to_a(num, i - 1, s);
	if (flgs->f_prec && flgs->prec > (i - (s[0] == '-')))
		add_di_prec(s, flgs, &i);
	if (num == 0 && flgs->f_prec && flgs->prec == 0)
	{
		*t = 0;
		i = 0;
	}
	if ((flgs->f_space || flgs->f_plus) && num >= 0)
		i = add_di_plus_or_space(s, flgs, i, t);
	if (flgs->width > i)
		return (create_u_w_string(s, flgs, i));
	return (s);
}

size_t	print_num(va_list *arg, t_flags *flgs)
{
	int		num;
	char	*s;
	size_t	size;

	num = va_arg(*arg, int);
	if (num < 0)
	{
		flgs->f_space = 0;
		flgs->f_plus = 0;
	}
	size = count_size(num, 10, flgs);
	s = malloc(sizeof(char) * (size + 1 + (num < 0)));
	if (!s)
	{
		flgs->f_correct = 'm';
		return (0);
	}
	s[size] = '\0';
	s = create_di_string(s, flgs, num, &size);
	if (size < (size_t)(flgs->width))
		size = flgs->width;
	if (write(1, s, size) < 0)
		flgs->f_correct = 'w';
	free(s);
	return (size);
}
