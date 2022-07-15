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
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

bool	ft_is_continue(char	*line)
{
	if (ft_strlen(line) >= ARG_MAX_SIZE)
	{
		printf("line too long\n");
		return (true);
	}
	return (false);
}

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
	//	printf("%d\n", getpid());
	while (1)
	{
		signal(SIGINT, ft_signal_handler);
		signal(SIGQUIT, SIG_IGN);
		g_status = 0;
		line = readline("minishell> ");
//		if (g_status == STATUS_FAILURE)
		if (ft_is_continue(line))
			continue;
		if (line == NULL)
			break ;
		add_history(line);
		free(line); // has to be deleted when the compilation with lexer.
	}
	free(line); // has to be deleted when the compilation with lexer.
	printf("exit\n");
	//	rl_clear_history;  ->I guess it's not necessary.
	return (g_status);
}
