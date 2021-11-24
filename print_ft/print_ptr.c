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

static size_t	count_ptr_size(unsigned long int p)
{
	size_t	size;

	size = 2;
	while (p > 0)
	{
		p /= 16;
		size++;
	}
	return (size);
}

static size_t print_ptr_return(unsigned long int p, t_flags *flgs, size_t size)
{
	print_no_width_x(p, flgs, "0123456789abcdef", 1);
	return (size);
}

size_t	print_ptr(va_list *arg, t_flags *flgs)
{
	unsigned long int	p;
	int					i;
	size_t				size;

	i = -1;
	p = va_arg(*arg, unsigned long int);
	if (!p)
		return (print_null_ptr(flgs));
	size = count_ptr_size(p);
	if ((size_t)(flgs->width) < size)
		return (print_ptr_return(p, flgs, size));
	if (flgs->f_minus)
	{
		print_no_width_x(p, flgs, "0123456789abcdef", 1);
		while (++i < flgs->width - 14)
			if (write(1, " ", 1) < 0)
				flgs->f_correct = 'w';
		return ((size_t)flgs->width);
	}
	while (++i < flgs->width - 14)
		if (write(1, " ", 1) < 0)
			flgs->f_correct = 'w';
	print_no_width_x(p, flgs, "0123456789abcdef", 1);
	return ((size_t)flgs->width);
}