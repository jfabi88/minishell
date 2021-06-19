NAME		= minishell

SRCS		=	\
				srcs/cd.c \
				srcs/echo.c \
				srcs/main.c \
				srcs/pwd.c \
				srcs/utils_mtr.c \
				srcs/utils.c \
				srcs/utils2.c \
				srcs/utils3.c

OBJS		= $(SRCS:.c=.o)

CFLAGS		= -Wall -Wextra -Werror

%.o :		%.c
			gcc -c -g -I./include -I./libft $(CFLAGS) $< -o $@

$(NAME):	$(OBJS)
			make -C libft
			mv libft/libft.a .
			gcc $(OBJS) libft.a -o $(NAME) -lreadline

all:		$(NAME)

clean:
			rm -f $(OBJS)
			make -C libft clean

fclean:		clean
			rm -f $(NAME) libft.a

re:			fclean all

.PHONY:		all clean fclean re
