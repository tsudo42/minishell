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

void child_put(const char *delimi, int fd, char *line)
{
	int	open_fd;

	open_fd = open("./heredoc.txt", O_CREAT | O_APPEND | O_WRONLY, 0644);
	dup2(open_fd, fd);
	close(open_fd);
	if (is_quote(delimi))
		ft_putendl_fd(line, fd);
	else
//		ft_putendl_fd(expand_env(line), fd);
		ft_putendl_fd(parameter_expander(line), fd);
	exit (0);
}

int	exec_d_heredoc(const char *delimi, int fd)
{
	char	*line;
//	extern char **environ;
	pid_t pid;
	int	status;

	while (1)
	{
		signal(SIGINT, signal_handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
		line = readline("hd> ");
		if (line == NULL || !ft_strcmp(line, extract_quote(delimi)))
		{
			free(line);
			break ;
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork()");
			break;
		}
		if (pid == 0)
			child_put(delimi, fd, line);
		else
			waitpid(pid, &status, 0);
		free(line);
	}
//	char *args[2];
//	args[0] = "./heredoc";
//	args[1] = NULL;
//	execve("/bin/cat", args, environ);
//	execve("/bin/rm", "./heredoc", environ);
	return (0);
	//exit (0);
}
