/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_unset(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
		ft_unsetenv(argv[i++]);
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
	builtin_unset(argv);
	return (0);
}
