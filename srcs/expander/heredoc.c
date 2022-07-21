#include "heredoc.h"

static bool	ft_is_env(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static char	*ft_str_c_join(char *str, char c)
{
	char	*res;
	size_t	len;

	len = ft_strlen(src);
	res = (char *)malloc(sizeof(char) * (len + 2));
	if(!res)
	{
		perror ("ft_str_c_join");
		exit (EXIT_FAILURE);
	}
	ft_strlcpy(res, str, len + 1);
	res[len] = c;
	free(str);
	return (res);
}

char	*ft_expand_env(char *line)
{
	char	*env_name;
	char	*res;

	res = ft_strdup("");
	while (*line != '\0')
	{
		if (*line == '$')
		{
			line++;
			env_name = ft_strdup("");
			while (ft_is_env(*line))
			{
				env_name = ft_str_c_join(env_name, *line);
				line++;
			}
			res = ft_strjoin(res, getenv(env_name));
		}
		else
		{
			res = ft_str_c_join(res, *line);
			line++;
		}
	}
	return (res);
}

bool	ft_is_quote(char *delimi)
{
	char	*s;

	s = ft_strchr(delimi, '"');
	if (s != NULL && s != ft_strrchr(delimi, '"'))
		return (true);
	s = ft_strchr(delimi, '\'');
	if (s != NULL && s != ft_strrchr(delimi, '\''))
		return (true);
	return (false);
}

char	*ft_extract_quote(char *delimi)
{
	char	*res;
	char	*temp;

	res = (char *)malloc(sizeof(char)*(ft_strlen(delimi) + 1));
	temp = res;
	while (*delimi != '\0')
	{
		if (*delimi == '"')
			while (*(++delimi) != '"' && *delimi != '\0')
				*temp++ = *delimi;
		else if (*delimi == '\'')
			while (*(++delimi) != '\'' && *delimi != '\0')
				*temp++ = *delimi;
		else
			*temp++ = *delimi++;
	}
//	printf("res: %s\n", res);
//	printf("temp: %s\n", temp - 1);
	*temp = *delimi;
	return (res);
}

void	ft_signal_handler_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit (1);
//	g_status·=·STATUS_FAILURE;
}

int	heredoc(char *delimi)
{
	char	*line;
	int	pipefd[2];
	
	if (pipe(pipefd) == -1)
	{
		perror("heredoc");
		exit(EXIT_FAILURE);
	}
	line = NULL;
	while (1)
	{
		signal(SIGINT, ft_signal_handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
		line = readline("hd> ");
		if (line == NULL || !ft_strcmp(line, ft_extract_quote(delimi)))
		{
			free(line);
			break ;
		}
		if (ft_is_quote(delimi))
			ft_putendl_fd(line, pipefd[WRITE]);
		else
			ft_putendl_fd(ft_expand_env(line), pipefd[WRITE]);
		free(line);
	}	
	close(pipefd[WRITE]);
	return (pipefd[READ]);
}
