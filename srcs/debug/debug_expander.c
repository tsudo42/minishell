/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "debug.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	print_str_list(t_list *lst)
{
	size_t	i;
	int		save_errno;

	save_errno = errno;
	printf("--------------------\n");
	i = 0;
	while (lst != NULL)
	{
		printf("str[%ld]\t: `%s`\n", i, (char *)(lst->content));
		lst = lst->next;
		i++;
	}
	printf("str[%ld]\t: `(null)`\n", i);
	printf("(%s)\n", strerror(save_errno));
	printf("--------------------\n");
}

/**
 * Function to debug expander().
 * Input via stdin and print the str list.
 * Always returns 0.
 */
int	debug_expander(void)
{
	t_environ	*env;
	char		*input;
	t_list		*lst;

	env = environ_init();
	write(1, "> ", 2);
	input = get_next_line_easy(0);
	while (input != NULL)
	{
		lst = expander(input, env);
		print_str_list(lst);
		ft_lstclear(&lst, free);
		write(1, "> ", 2);
		input = get_next_line_easy(0);
	}
	environ_destroy(env);
	return (0);
}
