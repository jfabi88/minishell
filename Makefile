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
				command/utils.c \
				file_manager/file.c \
				gnl/get_next_line_utils.c \
				gnl/get_next_line.c \
				parse/parse_dollar.c \
				parse/parse_check.c \
				parse/parse_create.c \
				parse/parse_manager.c \
				parse/parse_utils.c \
				parse/parse.c \
				pipe/exec_pipe.c \
				pipe/create_pipe.c \
				read/prompt.c \
				read/read.c \
				read/history.c \
				srcs/create_path.c \
				srcs/error.c \
				srcs/main.c \
				utils/data_utils.c \
				utils/env_utils.c \
				utils/file_utils.c \
				utils/flag_utils.c \
				utils/lst_utils.c \
				utils/mtr_utils.c \
				utils/utils.c \
				utils/utils_2.c \
				utils/utils_3.c

SRCS_BONUS	=	\
				command/all_com.c \
				command/cd.c \
				command/echo.c \
				command/env.c \
				command/export.c \
				command/pwd.c \
				command/unset.c \
				command/utils.c \
				file_manager/file.c \
				gnl/get_next_line_utils.c \
				gnl/get_next_line.c \
				parse/parse_dollar.c \
				parse/parse_check.c \
				parse/parse_create.c \
				parse/parse_manager.c \
				parse/parse_utils.c \
				parse/parse.c \
				pipe/exec_pipe.c \
				pipe/create_pipe.c \
				read/prompt.c \
				read/read.c \
				read/history.c \
				srcs/create_path.c \
				srcs/error.c \
				srcs_bonus/exit_bonus.c \
				srcs_bonus/main_bonus.c \
				token/token_bonus.c \
				token/token_check_bonus.c \
				token/token_utils_bonus.c \
				token/token_utils2_bonus.c \
				token/token2_bonus.c \
				utils/data_utils.c \
				utils/env_utils.c \
				utils/file_utils.c \
				utils/flag_utils.c \
				utils/lst_utils.c \
				utils/mtr_utils.c \
				utils/utils.c \
				utils/utils_2.c \
				utils/utils_3.c

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
