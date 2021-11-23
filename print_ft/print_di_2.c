#include "../ft_printf.h"

size_t	add_di_plus_or_space(char *s, t_flags *flgs, int i)
{
	char	*s2;
	size_t	res;

	res = i + 1;
	s2 = s + 1;
	while (i > 0)
	{
		s2[i] = s[i];
		i--;
	}
	s2[i] = s[i];
	if (flgs->f_plus)
		s[0] = '+';
	else
		s[0] = ' ';
	return (res);
}