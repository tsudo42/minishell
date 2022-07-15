#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#define STATUS_FAILURE -1
#define ARG_MAX_SIZE 4096

int	g_status;

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

bool	ft_is_continue(char	*line)
{
	if (ft_strlen(line) >= ARG_MAX_SIZE)
	{
		(void)line;
	}
	return (true);
}

void	ft_signal_handler(int sig)
{
	(void)sig;
	g_status = STATUS_FAILURE;
}

int	main(void)
{
	char *line;

	line = NULL;
//	printf("%d\n", getpid());
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_status = 0;
		line = readline("minishell> ");
		if (g_status == STATUS_FAILURE)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		if (ft_is_continue(line))
			continue;
		if (line == NULL)
			break ;
		add_history(line);
		//		free(line);
	}
	//	free(line);
	printf("exit\n");
	//	rl_clear_history;  ->I guess it's not necessary.
	return (g_status);
}
