#include "../ft_printf.h"

static size_t	print_null_ptr(t_flags *flgs)
{
	int	i;

	i = -1;
	if (flgs->width <= 3)
	{
		if (write(1, "0x0", 3) < 0)
			flgs->f_correct = 'w';
		return (3);
	}
	if (!flgs->f_minus)
	{
		while (++i < flgs->width - 3)
			if (write(1, " ", 1) < 0)
				flgs->f_correct = 'w';
		if (write(1, "0x0", 3) < 0)
			flgs->f_correct = 'w';
		return ((size_t)flgs->width);
	}
	if (write(1, "0x0", 3) < 0)
		flgs->f_correct = 'w';
	while (++i < flgs->width - 3)
		if (write(1, " ", 1) < 0)
			flgs->f_correct = 'w';
	return ((size_t)flgs->width);
}

size_t	print_ptr(va_list *arg, t_flags *flgs)
{
	unsigned long int	p;
	int					i;

	i = -1;
	p = va_arg(*arg, unsigned long int);
	if (!p)
		return (print_null_ptr(flgs));
	if (flgs->width <= 14)
	{
		print_no_width_x(p, flgs, "0123456789abcdef");
		return (14);
	}
	if (flgs->f_minus)
	{
		print_no_width_x(p, flgs, "0123456789abcdef");
		while (++i < flgs->width - 14)
			if (write(1, " ", 1) < 0)
				flgs->f_correct = 'w';
		return ((size_t)flgs->width);
	}
	while (++i < flgs->width - 14)
		if (write(1, " ", 1) < 0)
			flgs->f_correct = 'w';
	print_no_width_x(p, flgs, "0123456789abcdef");
	return ((size_t)flgs->width);
}