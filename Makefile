NAME		= minishell

SRCS		=	\
				parse/dollar.c \
				parse/parse_check.c \
				parse/parse_manager.c \
				parse/parse_utils.c \
				parse/parse.c \
				srcs/cd.c \
				srcs/create_path.c \
				srcs/echo.c \
				srcs/env_utils.c \
				srcs/error.c \
				srcs/exit.c \
				srcs/export.c \
				srcs/file_utils.c \
				srcs/flag_utils.c \
				srcs/main.c \
				srcs/mtr_utils.c \
				srcs/pwd.c \
				srcs/utils.c \
				srcs/utils_2.c

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
