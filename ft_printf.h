/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:41:07 by rbell             #+#    #+#             */
/*   Updated: 2021/11/16 16:43:39 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
int		ft_printf(const char *form, ...);
void	tereshkova(t_flags *flg);
int		print_error(t_flags *flgs);
ssize_t	for_easy_string(const char *form, size_t *p_i, t_flags *flgs);
ssize_t for_format_string(va_list *arg, char *form, t_flags *flgs, size_t *i);
ssize_t	print_percent(char *form, size_t *i, t_flags *flgs);
char	check_spec(char c);

typedef struct	printf_var
{
	char	f_correct;
	char	f_space;
	char	f_plus;
	char	f_zero;
	char	f_minus;
	char	f_prison;
	int		width;
	int 	prec;
	ssize_t	tmp_res;
} t_flags;
#endif
