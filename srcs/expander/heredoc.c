#include "heredoc.h"

/*
static bool	is_envname(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static char	*str_append(char *src, char dst)
{
	char	*appended_str;
	size_t	len;

	len = ft_strlen(src);
	appended_str = (char *)ft_xcalloc(len + 2, sizeof(char));
	ft_strlcpy(appended_str, src, len + 1);
	appended_str[len] = dst;
	free(src);
	return (appended_str);
}

char	*expand_env(char *line)
{
	char	*key;
	char	*expanded;

	expanded = ft_xstrdup("");
	while (*line != '\0')
	{
		if (*line == '$')
		{
			line++;
			key = ft_xstrdup("");
			while (is_envname(*line))
			{
				key = str_append(key, *(line++));
			}
			expanded = ft_xstrjoin(expanded, get_env(key));
		}
		else
			expanded = str_append(expanded, *(line++));
	}
	return (expanded);
}
*/

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
	char	*ret_str;
	char	*temp_str;

	ret_str = (char *)malloc(sizeof(char)*(ft_strlen(delimi) + 1));
	temp_str = ret_str;
	while (*delimi != '\0')
	{
		if (*delimi == '"')
			while (*(++delimi) != '"' && *delimi != '\0')
				*temp_str++ = *delimi;
		else if (*delimi == '\'')
			while (*(++delimi) != '\'' && *delimi != '\0')
				*temp_str++ = *delimi;
		else
			*temp_str++ = *delimi++;
	}
//	printf("ret_str: %s\n", ret_str);
//	printf("temp_str: %s\n", temp_str - 1);
	*temp_str = *delimi;
	return (ret_str);
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
		line = readline("heredoc> ");
		if (line == NULL || !ft_strcmp(line, ft_extract_quote(delimi)))
		{
			free(line);
			break ;
		}
		if (ft_is_quote(delimi))
			ft_putendl_fd(line, pipefd[WRITE]);
//		else
//			ft_putendl_fd(expand_env(line), pipe_fd[WRITE_INDEX]);
		free(line);
	}	
//	xclose(pipe_fd[WRITE_INDEX]);
//	return (pipe_fd[READ_INDEX]);
	return (0);
}
