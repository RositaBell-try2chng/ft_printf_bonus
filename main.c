#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
/*
 * c
 * s
 * p
 * di
 * u
 * x
 * X
 * % +
 * prosto +
 */
int main()
{
	int a;
	//char *s = "hello world";
	//s = NULL;
	a = printf("|%- 5.0d|\n", -1);
	printf("%d\n", a);
	a = ft_printf("|%- 5.0d|\n", -1);
	printf("%d\n", a);
}

/*
 *gcc -Wall -Wextra -Werror main.c -L. -lftprintf
 *
 *
 * ' '
 * 0
 * +
 * -
 * .
 * # -
 */