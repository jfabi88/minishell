NAME		= minishell

NAME_BONUS = minishell_bonus

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
				pipe/pipe.c \
				read/prompt.c \
				read/read.c \
				srcs/create_path.c \
				srcs/data_utils.c \
				srcs/env_utils.c \
				srcs/error.c \
				srcs/file_utils.c \
				srcs/flag_utils.c \
				srcs/ft_m_strlcpy.c \
				srcs/main.c \
				srcs/lst_utils.c \
				srcs/history.c \
				srcs/mtr_utils.c \
				srcs/utils.c \
				srcs/utils_2.c \

SRCS_BONUS	=	\
				command/all_com.c \
				command/cd.c \
				command/echo.c \
				command/env.c \
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
				pipe/pipe.c \
				read/prompt.c \
				read/read.c \
				srcs/create_path.c \
				srcs/data_utils.c \
				srcs/env_utils.c \
				srcs/error.c \
				srcs/file_utils.c \
				srcs/flag_utils.c \
				srcs/ft_m_strlcpy.c \
				srcs/lst_utils.c \
				srcs/history.c \
				srcs/mtr_utils.c \
				srcs/utils.c \
				srcs/utils_2.c \
				srcs_bonus/main_bonus.c \
				srcs_bonus/exit_bonus.c \
				token/token_bonus.c \
				token/token2_bonus.c \
				token/token_check_bonus.c \
				token/token_utils_bonus.c \
				token/token_utils2_bonus.c \

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

CFLAGS		= -Wall -Wextra -Werror

%.o :		%.c
			gcc -c -g -I./include -I./libft -I./gnl $< -o $@

$(NAME):	$(OBJS)
			make -C libft
			mv libft/libft.a .
			gcc $(OBJS) libft.a -o $(NAME) -lreadline

$(NAME_BONUS):	$(OBJS_BONUS)
				make -C libft
				mv libft/libft.a .
				gcc $(OBJS_BONUS) libft.a -o $(NAME_BONUS) -lreadline

all:		$(NAME)

bonus:		$(NAME_BONUS)

clean:		
			rm -f $(OBJS)
			make -C libft clean

clean_bonus:	
				rm -f $(OBJS_BONUS)
				make -C libft clean

fclean:		clean clean_bonus
			rm -f $(NAME_BONUS)
			rm -f $(NAME) libft.a

re:			fclean all

.PHONY:		all clean fclean re
