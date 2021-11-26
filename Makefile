SRCS		= ft_printf.c mini_utils.c parse_flg.c print_ft/print_char.c print_ft/print_di_2.c print_ft/print_di.c \
 				print_ft/print_ptr.c print_ft/print_string.c print_ft/print_u_2.c print_ft/print_u.c \
 				print_ft/print_x_2.c print_ft/print_x.c

HEAD		= ft_printf.h

OBJS		= ${SRCS:.c=.o}

NAME		= libftprintf.a

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

%.o:	%.c ${HEAD}
		${CC} ${CFLAGS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			ar rc ${NAME} $?
			ranlib ${NAME}

clean:
			@${RM} ${OBJS}

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
