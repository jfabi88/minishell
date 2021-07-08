#include "minishell.h"

static void	ft_enable_raw_mode(struct termios *termios)
{

}

static void	ft_disable_raw_mode(struct termios *termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, termios);
}

void	ft_set_termios(void)
{
	struct termios	termios;

	ft_disable_raw_mode(&termios);
	ft_enable_raw_mode(&termios);
}
