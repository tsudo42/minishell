#include "exec.h"
/*
	 static bool	is_env(char c)
	 {
	 return (ft_isalpha(c) || c == '_');
	 }

	 static char	*ft_str_c_join(char *str, char c)
	 {
	 char	*res;
	 size_t	len;

	 len = ft_strlen(str);
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

	 char	*expand_env(char *line)
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
	 while (is_env(*line))
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
	 */

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

void	signal_handler_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit (1);
}

static void put_line(const char *delimi, char *line, int *pipe_fd, int *len)
{
	char *tmp;

	if (is_quote(delimi))
		*len += ft_putendl_len_fd(line, pipe_fd[1]);
	else
	{
		tmp = ft_strdup(line);
		*len += ft_putendl_len_fd(parameter_expander(tmp), pipe_fd[1]);
	}
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
	if (ret <= 0)
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
	signal(SIGINT, signal_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || !ft_strcmp(line, extract_quote(delimi)))
		{
			free(line);
			break ;
		}
		put_line(delimi, line, pipe_fd, &len);
		free(line);
	}
	return (close_pipe(pipe_fd, len));
}
