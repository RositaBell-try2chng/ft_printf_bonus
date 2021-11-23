#include "ft_printf.h"

static void print_char_width(char c, size_t *cnt, t_flags *flgs)
{
	if (flgs->f_minus)
	{
		if (write(1, &c, 1) < 0)
			flgs->f_correct = 'w';
		while (--(flgs->width))
		{
			if (write(1, " ", 1) < 0)
				flgs->f_correct = 'w';
			(*cnt)++;
		}
	}
	else
	{
		while (--(flgs->width))
		{
			if (write(1, " ", 1) < 0)
				flgs->f_correct = 'w';
			(*cnt)++;
		}
		if (write(1, &c, 1) < 0)
			flgs->f_correct = 'w';
	}
}

size_t	print_char(va_list *arg, t_flags *flgs)
{
	unsigned char	c;
	size_t			cnt;

	cnt = 1;
	c = va_arg(*arg, int);
	if (flgs->width > 1)
		print_char_width(c, &cnt, flgs);
	else if (write(1, &c, 1) < 0)
		flgs->f_correct = 'w';
	return (cnt);
}