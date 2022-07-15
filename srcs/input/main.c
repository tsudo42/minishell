#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>

#define STATUS_FAILURE -1

int	g_status;

void	ft_signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = STATUS_FAILURE;
}

int	main(void)
{
	char *line;

	line = NULL;
	while (1)
	{
		signal(SIGINT, ft_signal_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		add_history(line);
		free(line);
	}
	free(line);
	printf("exit\n");
	//	rl_clear_history;  ->I guess it's not necessary.
	return (g_status);
}
