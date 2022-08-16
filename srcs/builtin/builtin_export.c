/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void putstrlen_fd(const char *s, size_t len, int fd)
{
	size_t i;

	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return ;
	}
	i = 0;
	while (s[i] != '\0' && i < len) 
		i++;
	if (i != 0)
		write(fd, s, i);
}

static int	is_printable(char *s)
{
	if (ft_strncmp(s, "LINES=", 6) == 0)
		return (-1);
	else if (ft_strncmp(s, "COLUMNS=", 8) == 0)
		return (-1);
	return (0);
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
		if (environ[i][0] == '_' || is_printable(environ[i]) == -1)
		{
			i++;
			continue ;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		str = ft_strdup(environ[i++]);
		value = ft_strchr(str, '=');
		putstrlen_fd(str, value - str, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(++value, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
	}
	return (STATUS_SUCCESS);
}
//add the function to check if the parameter is valid or not.

static int	export_value_checker(char *name, int len, char **argv)
{
	int i;

	i = 1;
	while (i < len)
	{
		if (!ft_isalpha(name[0]))
			break ;
		if (!ft_isalpha(name[i]) || !ft_isdigit(name[i]))
			break ;
		i++;
	}
	if (i == len)
		return (STATUS_SUCCESS);
//	printf("export: '%s", *argv);
	ft_putstr_fd("export: '", STDERR_FILENO);
	ft_putstr_fd(*argv, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	free(name);
	return(STATUS_FAILURE);
}

static int	export_values(char **argv)
{
	char	*name;
	char	*value;
	int		status;

	status = STATUS_SUCCESS;
	while (*(++argv) != NULL)
	{
		name = ft_strdup(*argv);
		value = ft_strchr(name, '=');
		if ((status = export_value_checker(name, value - name, argv)) \
			== STATUS_FAILURE)
			break;
		//	}

		if (value != NULL)
			//	{
			//	*value = '\0';
			ft_setenv(name, ++value, 1);
		//	}
		free (name);
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

