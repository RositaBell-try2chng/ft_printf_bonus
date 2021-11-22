#include "ft_printf.h"

static	void add_prec(char *s, t_flags *flgs, size_t *i)
{
	size_t	j;
	char	*s2;

	j = 0;
	s2 = s + flgs->prec - (*i - 2 * (flgs->f_prison));
	while (s[j])
		j++;
	s2[j] = '\0';
	while (--j >= 0)
		s2[j] = s[j];
	while ((s + (++j) + (2 * (flgs->f_prison))) < s2)
		s[2 * flgs->f_prison + j] = '0';
	*i = flgs->prec + 2 * (flgs->f_prison);
}

static void	count_i(size_t *i, unsigned int n)
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

static void i_to_a(unsigned int n, char *s, char *base, size_t i)
{
	if (n >= 16)
		i_to_a(n / 16, s, base, i - 1);
	s[i] = base[n % 16];
}

static char	*create_x_string(char *s, char *base, t_flags *flgs, \
unsigned int n)
{
	size_t	i;

	i = 0;
	if (flgs->f_prison)
	{
		s[i++] = '0';
		s[i++] = 'x';
	}
	count_i(&i, n);
	s[i] = '\0';
	i_to_a(n, s, base, i - 1);
	if (flgs->f_prec && flgs->prec > (i - 2 * (flgs->f_prison)))
		add_prec(s, flgs, &i);
	if (flgs->width > i)
		return (create_x_w_string(s, flgs, i));
	return (s);
}

size_t	print_x_num(va_list *arg, t_flags *flgs, char spec)
{
	char			*base;
	char 			*s;
	unsigned int	n;
	size_t			size;

	n = va_arg(*arg, unsigned int);
	size = count_size(n, 16, flgs);
	base = get_base(base, spec);
	s = malloc((size + 1) * sizeof(char));
	if (!s)
	{
		flgs->f_correct = 'm';
		return (0);
	}
	s[size] = '\0';
	s = create_x_string(s, base, flgs, size);
	if (write(1, s, size) < 0)
		flgs->f_correct = 'w';
	return (size);
}


/*
 * ' ' -
 * '-'
 * '+' -
 * '.'
 * '0'
 * '#'
 * флаг 0 в сочетании с точностью игнорирутеся
 * флаг 0 в сочетании с - игнорирутеся
 *
 * -
 * -#
 * -.
 * -#.
 * .
 * .#
 * 0
 * 0#
 */