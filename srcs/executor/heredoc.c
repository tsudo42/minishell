#include "exec.h"

bool	is_quote(const char *delimi)
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

char	*extract_quote(const char *delimi)
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
	*temp = *delimi;
	return (res);
}

static int put_line(const char *delimi, char *line, int *pipe_fd, int *len)
{
	char *tmp;

	if (is_quote(delimi))
		*len += ft_putendl_len_fd(line, pipe_fd[1]);
	else
	{
		if ((tmp = ft_strdup(line)) == NULL)
			return (-1);
		*len += ft_putendl_len_fd(parameter_expander(tmp), pipe_fd[1]);
	}
	return (0);
}

static int close_pipe(int *pipe_fd, int len)
{
	int ret;

	if (len > 15873)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		perror("exec_d_heredoc: over pipe buf");
		return (-1);
	}
	ret = ft_r_dup2(pipe_fd[0], 0, "close_pipe: dup2");
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (ret < 0)
		return (-1);
	return (0);
}

int	exec_d_heredoc(const char *delimi, int fd)
{
	char	*line;
	int pipe_fd[2];
	int len;

	(void)fd;
	if (pipe(pipe_fd) < 0)
	{
		perror("exec_d_heredoc: pipe");
		return (-1);
	}
	len = 0;
	activate_signal_heredoc();
	while (1)
	{
		line = readline("> ");
		if (line == NULL || !ft_strcmp(line, extract_quote(delimi)))
		{
			free(line);
			break ;
		}
		if ((put_line(delimi, line, pipe_fd, &len)) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (close_pipe(pipe_fd, len));
}
