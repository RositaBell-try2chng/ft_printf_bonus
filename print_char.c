#include "ft_printf.h"

static void print_char_width(char c, ssize_t *cnt, char f, t_flags *flgs)
{
	if (f == 0)
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

ssize_t	print_char(va_list *arg, t_flags *flgs)
{
	unsigned char	c;
	ssize_t			cnt;

	cnt = 1;
	c = va_arg(*arg, int);
	if (flgs->width > 1)
	{
		if (flgs->f_minus)
			print_char_width(c, &cnt, 0, flgs);
		else
			print_char_width(c, &cnt, 1, flgs);
	}
	if (write(1, &c, 1) < 0)
		flgs->f_correct = 'w';
	return (cnt);
}