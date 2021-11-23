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
# include <limits.h>

typedef struct	printf_var
{
	char	f_correct;
	char	f_space;
	char	f_plus;
	char	f_zero;
	char	f_minus;
	char	f_prison;
	char	f_prec;
	int		width;
	int 	prec;
	ssize_t	tmp_res;
} t_flags;

int		ft_printf(const char *form, ...);
void	tereshkova(t_flags *flg, size_t *p_i, size_t *p_res, char begin_flg);
int		print_error(t_flags *flgs);
size_t	for_easy_string(const char *form, size_t *p_i, t_flags *flgs);
size_t	for_format_string(va_list *arg, const char *form, t_flags *flgs, \
		size_t *i);
size_t	print_percent(t_flags *flgs);
size_t	print_result(va_list *arg, char spec, t_flags *flgs);
size_t	print_char(va_list *arg, t_flags *flgs);
size_t	print_string(va_list *arg, t_flags *flgs);
size_t	print_ptr(va_list *arg, t_flags *flgs);
void	print_no_width_x(unsigned long int p, t_flags *flgs, char *base, \
		char f);
size_t	print_x_num(va_list *arg, t_flags *flgs, char spec);
char	parse_flags(const char *s, t_flags *flgs, size_t *i);
char	parse_num(const char *form, int *a, size_t *i, t_flags *flgs);
char	check_spec(t_flags *f, char c);
char	*get_base(char *base, char c);
size_t	count_size(long int n, int base, t_flags *flgs);
char	*create_x_w_string(char *s, t_flags *flgs, size_t i);
size_t	print_u_num(va_list *arg, t_flags *flgs);
char	*create_u_w_string(char *s, t_flags *flgs, size_t i);
size_t 	add_di_plus_or_space(char *s, t_flags *flgs, int i, size_t *t);
char	*create_di_w_string(char *s, t_flags *flgs, size_t i);
size_t	print_num(va_list *arg, t_flags *flgs);
#endif
