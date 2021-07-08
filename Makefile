NAME		= minishell

SRCS		=	\
				command/all_com.c \
				command/cd.c \
				command/echo.c \
				command/env.c \
				command/exit.c \
				command/export.c \
				command/pwd.c \
				command/unset.c \
				gnl/get_next_line_utils.c \
				gnl/get_next_line.c \
				parse/parse_dollar.c \
				parse/parse_check.c \
				parse/parse_manager.c \
				parse/parse_utils.c \
				parse/parse.c \
				srcs/create_path.c \
				srcs/data_utils.c \
				srcs/env_utils.c \
				srcs/error.c \
				srcs/file_utils.c \
				srcs/flag_utils.c \
				srcs/history.c \
				srcs/main.c \
				srcs/mtr_utils.c \
				srcs/termios.c \
				srcs/utils.c \
				srcs/utils_2.c

OBJS		= $(SRCS:.c=.o)

CFLAGS		= -Wall -Wextra -Werror

%.o :		%.c
			gcc -c -g -I./include -I./libft -I./gnl $(CFLAGS) $< -o $@

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
