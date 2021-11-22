#include "ft_printf.h"

static size_t	print_null_string(t_flags *flgs)
{
	size_t	i;

	i = -1;
	if (flgs->f_prec && flgs->prec < 6)
	{
		while (++i < flgs->width)
			if (write(1, " ", 1) < 0)
				flgs->f_correct = 'w';
		return (i);
	}
	if (flgs->f_minus)
	{
		if (write(1, "(null)", 6) < 0)
			flgs->f_correct = 'w';
		while (++i + 6 < flgs->width)
			if (write(1, " ", 1) < 0)
				flgs->f_correct = 'w';
		return (i + 6);
	}
	while (++i + 6 < flgs->width)
		if (write(1, " ", 1) < 0)
			flgs->f_correct = 'w';
	if (write(1, "(null)", 6) < 0)
		flgs->f_correct = 'w';
	return (i + 6);
}

static void	print_width_string(const char *s, t_flags *flgs, size_t i)
{
	ssize_t cnt;

	cnt = -1;
	if (flgs->f_minus)
	{
		while (++cnt < i)
			if (write(1, (s + cnt), 1) < 0)
				flgs->f_correct = 'w';
		cnt = -1;
		while (++cnt < flgs->width - i)
			if (write(1, " ", 1) < 0)
				flgs->f_correct = 'w';
		return ;
	}
	while (++cnt < flgs->width - i)
		if (write(1, " ", 1) < 0)
			flgs->f_correct = 'w';
	cnt = -1;
	while (++cnt < i)
		if (write(1, (s + cnt), 1) < 0)
			flgs->f_correct = 'w';
}

size_t	print_string(va_list *arg, t_flags *flgs)
{
	const char	*s;
	size_t		i;

	i = 0;
	s = va_arg(*arg, const char *);
	if (!s)
		return (print_null_string(flgs));
	while (s[i] && (!flgs->f_prec || i < flgs->prec)
		i++;
	if (flgs->width > i)
	{
		print_width_string(s, flgs, i));
		return ((ssize_t)flgs->width);
	}
	if (write(1, s, i) < 0)
		flgs->f_correct = 'w';
	return ((ssize_t)i);
}

/*
 * ' ' -
 * '-'
 * '+' -
 * '.'
 * '0' -
 * '#' -
 */