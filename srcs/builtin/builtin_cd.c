/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


static int	cd_to_home(char **argv)
{
	char	*home_dir;

	home_dir = ft_getenv("HOME");
	if (home_dir == NULL)
	{
		perror("cd_to_home");
		return (STATUS_FAILURE);
	}
	if (chdir(home_dir) == -1)
	{
		free(home_dir);
		perror("cd_to_home2");
		return (STATUS_FAILURE);
	}
	free(home_dir);
	return (STATUS_SUCCESS);
}

int	builtin_cd(char **argv)
{
	if (argv[1] == NULL)
		return (cd_to_home(argv));
	if (chdir(argv[1]) == -1)
	{
		perror("builtin_cd");
		return (STATUS_FAILURE);
	}
	return (STATUS_SUCCESS);
}

int main(void)
{
	char *argv[10];
	char str[10] = "echo";
	//	char str1[10] = "-n";
	char str1[10] = "str1";
	char str2[10] = "str2";
	char str3[10] = "str3";
	char *str4;

	str4 = NULL;
	argv[0] = str;
	argv[1] = str1;
	argv[2] = str2;
	argv[3] = str3;
	argv[4] = str4;
	builtin_cd(argv);
	return (0);
}
