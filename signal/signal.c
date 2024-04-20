#include	"../minishell.h"

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("",0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_controller(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
