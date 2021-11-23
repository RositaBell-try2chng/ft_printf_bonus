#include "ft_printf.h"

static void	count_di_i(char *s, size_t *i, int num)
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

static void di_to_a(int num, size_t i, char *s)
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

static void	add_di_prec(char *s, t_flags *flgs, size_t *i)
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
	while ((s + j) < s2)
		s[j++] = '0';
	*i = flgs->prec;
}

static char	*create_di_string(char *s, t_flags *flgs, long int num)
{
	size_t	i;

	i = 0;
	count_di_i(s, &i, num);
	s[i] = '\0';
	di_to_a(num, i - 1, s);
	if (flgs->f_prec && flgs->prec > i))
		add_di_prec(s, flgs, &i);
	if (flgs->f_space || flgs->f_plus)
		i = add_di_plus_or_space(s, flgs, &i);
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
	size = count_size(num, 10);
	s = malloc(sizeof(char) * (size + 1));
	if (!s)
	{
		flgs->f_correct = 'm';
		return (0);
	}
	s[size] = '\0';
	s = create_di_string(s, flgs, num);
	if (write(1, s, size) < 0)
		flgs->f_correct = 'w';
	free(s);
	return (size);
}