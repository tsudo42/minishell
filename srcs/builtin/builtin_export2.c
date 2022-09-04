/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/31 16:06:19 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_internal.h"

void	putstrlen_fd(const char *s, size_t max_len, int fd)
{
	size_t	i;

	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return ;
	}
	i = 0;
	while (s[i] != '\0' && i < max_len)
	{
		if (i >= 10000000L)
		{
			write(fd, s, 10000000L);
			s += i;
			i = -1;
		}
		i++;
	}
	if (i != 0)
		write(fd, s, i);
}

int	is_printable(char *s)
{
	if (ft_strncmp(s, "_=", 2) == 0)
		return (-1);
	return (0);
}

void	print_values2(char *str, char *value)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	putstrlen_fd(str, value - str, STDOUT_FILENO);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	value++;
	while (*value != '\0')
	{
		if (*value == '\"' || *value == '\\' || \
			*value == '$' || *value == '`')
			write(STDOUT_FILENO, "\\", 1);
		write(STDOUT_FILENO, value, 1);
		value++;
	}
	ft_putstr_fd("\"\n", STDOUT_FILENO);
}

int	print_values(t_environ *env)
{
	int			i;
	char		*str;
	char		*value;

	if (!environ)
		return (STATUS_FAILURE);
	i = 0;
	while (environ[i])
	{
		if (is_printable(environ[i]) == -1)
		{
			i++;
			continue ;
		}
		str = ft_x_strdup(environ[i++], EXPORT_ERRMSG);
		value = ft_strchr(str, '=');
		print_values2(str, value);
		free (str);
		str = NULL;
	}
	return (STATUS_SUCCESS);
}
