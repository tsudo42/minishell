/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/25 19:47:47 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void putstrlen_fd(const char *s, size_t max_len, int fd)
{
//	size_t len;
	size_t i;

	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return ;
	}
//	len = ft_strnlen(s, max_len);
	i = 0;
	//while (s[i] != '\0' && i < len) 
	//		i++;
//	if (i != 0)
//		write(fd, s, i);
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

static int	is_printable(char *s)
{
	if (ft_strncmp(s, "LINES=", 6) == 0)
		return (-1);
	else if (ft_strncmp(s, "COLUMNS=", 8) == 0)
		return (-1);
	else if (ft_strncmp(s, "_=", 2) == 0)
		return (-1);
	return (0);
}

static void print_values2(char *str, char *value)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	putstrlen_fd(str, value - str, STDOUT_FILENO);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	value++;
	while (*value != '\0')
	{
		if (*value == '\"' || *value == '\\' || *value == '$')
			write(STDOUT_FILENO, "\\", 1);
		write(STDOUT_FILENO, value, 1);
		value++;
	}
	ft_putstr_fd("\"\n", STDOUT_FILENO);
}

static int	print_values(void)
{
	extern char	**environ;
	int i;
	char *str;
	char *value;

	i = 0;
	while (environ[i])
	{
		if (is_printable(environ[i]) == -1)
		{
			i++;
			continue ;
		}
		str = ft_strdup(environ[i++]);
		value = ft_strchr(str, '=');
		print_values2(str, value);
	}
	return (STATUS_SUCCESS);
}

static bool is_underbar(char c)
{
	if ((int)c == '_')
		return (true);
	return (false);
}

static int	export_value_checker(char *name, int len, char **argv)
{
	int i;

	i = 1;
	while (i < len)
	{
		if (!ft_isalpha(name[0]) && !is_underbar(name[0]))
			break ;
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) \
				&& !is_underbar(name[i]))
			break ;
		i++;
	}
	if (i == len)
		return (STATUS_SUCCESS);
	ft_putstr_fd("export: '", STDERR_FILENO);
	ft_putstr_fd(*argv, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	free(name);
	return(STATUS_FAILURE);
}

static int	export_values(char **argv)
{
	char	*string;
	char	*value;
	int		status;

	status = STATUS_SUCCESS;
	while (*(++argv) != NULL)
	{
		string = ft_strdup(*argv);
		value = ft_strchr(string, '=');
		if ((status = export_value_checker(string, value - string, argv)) \
				== STATUS_FAILURE)
			break;
		*value = '\0';
		if (value != NULL)
			ft_setenv(string, ++value, 1);
		free (string);
	}
	return (status);
}

int	builtin_export(char **argv)
{
	if (argv[1] == NULL)
		return (print_values());
	else
		return (export_values(argv));
}

