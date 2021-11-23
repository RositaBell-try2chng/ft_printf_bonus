#include "ft_printf.h"

static void	count_u_i(size_t *i, unsigned int u)
{
	if (u == 0)
	{
		(*i)++;
		return ;
	}
	while (u > 0)
	{
		u /= 10;
		(*i)++;
	}
}

static void	u_to_a(unsigned int u, size_t i, char *s)
{
	if (u >= 10)
		u_to_a(u / 10, i - 1, s);
	s[i] = (u % 10) + '0';
}

static void	add_u_prec(char *s, t_flags *flgs, size_t *i)
{
	size_t	j;
	char	*s2;

	j = 0;
	s2 = s + flgs->prec - *i;
	while (s[j])
		j++;
	s2[j] = '\0';
	while (--j > 0)
		s2[j] = s[j];
	s2[j] = s[j];
	j--;
	while ((s + (++j)) < s2)
		s[j] = '0';
	*i = flgs->prec;
}

static char	*create_u_string(char *s, t_flags *flgs, size_t *size, \
unsigned int u)
{
	size_t	i;

	i = 0;
	count_u_i(&i, u);
	s[i] = '\0';
	u_to_a(u, i - 1, s);
	if (flgs->f_prec && flgs->prec > i))
		add_u_prec(s, flgs, &i);
	if (flgs->width > i)
		return (create_u_w_string(s, flgs, i));
	return (s);
}

size_t	print_u_num(va_list *arg, t_flags flgs)
{
	unsigned int	u;
	size_t			size;
	char			*s;

	u = va_arg(*arg, unsigned int);
	size = count_size(u, 10);
	s = malloc(sizeof(char) * (size + 1));
	if (!s)
	{
		flgs->f_correct = 'm';
		return (0);
	}
	s[size] = '\0';
	s = create_u_string(s, flgs, size, u);
	if (write(1, s, size) < 0)
		flgs->f_correct = 'w';
	free(s);
	return (size);
}

/*
 * ' ' -
 * '-'
 * '+' -
 * '.'
 * '0'
 * '#' -
 * флаг 0 в сочетании с точностью игнорирутеся
 * флаг 0 в сочетании с - игнорирутеся
 * -
 * -.
 * .
 * 0
 */