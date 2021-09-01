#include "minishell.h"

void	ft_set_termios(struct termios *saved)
{	
	struct termios	m_termios;

	tcgetattr(STDIN_FILENO, saved);
 	m_termios = *saved;
	m_termios.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &m_termios);
}