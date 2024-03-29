/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 16:53:17 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

/* unquote delim and return whether delim was quoted. */
static int	is_quoted(char *delim)
{
	size_t	i;
	size_t	j;
	char	q;
	int		quoted;

	quoted = 0;
	i = 0;
	j = 0;
	while (delim[i] != '\0')
	{
		if (delim[i] == '\'' || delim[i] == '\"')
		{
			quoted = 1;
			q = delim[i++];
			while (delim[i] != '\0' && delim[i] != q)
				delim[j++] = delim[i++];
			if (delim[i] == '\0')
				break ;
		}
		else
			delim[j++] = delim[i];
		i++;
	}
	delim[j] = '\0';
	return (quoted);
}

/* get single line. perform parameter expansion if delimiter was not quoted. */
static char	*heredoc_getline(int quoted, int *is_error, t_environ *env)
{
	char	*line;
	char	*expanded;

	errno = 0;
	line = readline("> ");
	if (errno != 0)
		perror(EXEC_ERRMSG ": heredoc");
	if (line != NULL && quoted)
	{
		expanded = parameter_expander(line, env);
		free(line);
		line = expanded;
	}
	if (errno != 0)
		*is_error = 1;
	return (line);
}

static int	heredoc_append(char **input, char **line, int *is_error)
{
	char	*joined;

	if (*line == NULL)
		return (*is_error);
	joined = ft_strjoin3(*input, *line, "\n");
	if ((*input != NULL || *line != NULL) && joined == NULL)
	{
		*is_error = 1;
		perror(EXEC_ERRMSG ": heredoc: malloc");
	}
	free(*input);
	free(*line);
	*input = joined;
	*line = NULL;
	return (*is_error);
}

/* determine whether to quit the input loop. */
/* here delim is already unquoted. */
static int	is_end_input(const char *line, const char *delim, int *is_error)
{
	size_t	len;

	if (line == NULL || *is_error != 0)
		return (1);
	len = 0;
	while (line[len] == delim[len] && delim[len] != '\0')
		len++;
	if (line[len] == '\0' && delim[len] == '\0')
		return (1);
	if (line[len] == '\n' && delim[len] == '\0')
		return (1);
	return (0);
}

char	*heredoc_input(char *delim, int *is_error, t_environ *env)
{
	char	*input;
	char	*line;
	int		quoted;

	if (ready_heredoc_signal(is_error) != 0)
		return (NULL);
	quoted = is_quoted(delim);
	input = NULL;
	line = heredoc_getline(quoted, is_error, env);
	while (!is_end_input(line, delim, is_error))
	{
		if (g_sig != 0)
		{
			*is_error = 1;
			break ;
		}
		if (heredoc_append(&input, &line, is_error) < 0)
			break ;
		line = heredoc_getline(quoted, is_error, env);
	}
	cleanup_heredoc_signal(is_error);
	ft_free_set((void **)&line, NULL);
	if (*is_error)
		ft_free_set((void **)&input, NULL);
	return (input);
}
