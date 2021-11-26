/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:10:22 by rbell             #+#    #+#             */
/*   Updated: 2021/11/24 11:11:10 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static	void	add_x_prec(char *s, t_flags *flgs, int *i)
{
	size_t	j;
	char	*s2;

	j = 0;
	s2 = s + flgs->prec - (*i - 2 * (flgs->f_prison));
	while (s[j])
		j++;
	s2[j] = '\0';
	while (--j > 0)
		s2[j] = s[j];
	s2[j] = s[j];
	j--;
	while ((s + (++j) + (2 * (flgs->f_prison))) < s2)
		s[2 * flgs->f_prison + j] = '0';
	*i = flgs->prec + 2 * (flgs->f_prison);
}

static void	count_x_i(int *i, unsigned int n)
{
	if (n == 0)
	{
		(*i)++;
		return ;
	}
	while (n > 0)
	{
		n /= 16;
		(*i)++;
	}
}

static void	i_to_a(unsigned int n, char *s, char *base, size_t i)
{
	if (n >= 16)
		i_to_a(n / 16, s, base, i - 1);
	s[i] = base[n % 16];
}

static char	*create_x_string(char *s, char *base, t_flags *flgs, \
unsigned int n)
{
	int	i;

	i = 0;
	if (flgs->f_prison)
	{
		s[i++] = '0';
		s[i++] = base[16];
	}
	count_x_i(&i, n);
	s[i] = '\0';
	i_to_a(n, s, base, i - 1);
	if (flgs->f_prec && flgs->prec > (i - 2 * (flgs->f_prison)))
		add_x_prec(s, flgs, &i);
	if (flgs->width > i)
		return (create_x_w_string(s, flgs, i));
	return (s);
}

size_t	print_x_num(va_list *arg, t_flags *flgs, char spec)
{
	char			*base;
	char			*s;
	unsigned int	n;
	size_t			size;

	n = va_arg(*arg, unsigned int);
	if (n == 0)
		flgs->f_prison = 0;
	size = count_size(n, 16, flgs);
	base = get_base(spec, &base);
	s = malloc((size + 1) * sizeof(char));
	if (!s)
	{
		flgs->f_correct = 'm';
		return (0);
	}
	s[size] = '\0';
	s = create_x_string(s, base, flgs, n);
	if (n == 0 && flgs->f_prec && flgs->prec == 0)
		size = 0;
	else if (write(1, s, size) < 0)
		flgs->f_correct = 'w';
	free(s);
	return (size);
}
