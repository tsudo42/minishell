/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "environ.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

t_list	*next_parameter_token(char **word, char *exit_status_str);

static char	*lst_to_str(t_list *lst)
{
	char	*str;
	size_t	len;
	t_list	*lst_head;

	lst_head = lst;
	len = 0;
	while (lst != NULL)
	{
		len += ft_strlen(lst->content);
		lst = lst->next;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
	{
		perror(EXPANDER_ERRMSG ": malloc");
		return (NULL);
	}
	str[0] = '\0';
	lst = lst_head;
	while (lst != NULL)
	{
		ft_strlcat(str, lst->content, len + 1);
		lst = lst->next;
	}
	return (str);
}

static void	*print_error(void *to_free)
{
	perror(EXPANDER_ERRMSG ": malloc");
	free(to_free);
	return (NULL);
}

/* Errno can be set as ENOMEM by malloc or EINVAL as bad substitution. */
char	*parameter_expander(char *word)
{
	t_list	*lst;
	t_list	*lst_node;
	char	*to_free[2];
	char	*str;

	errno = 0;
	to_free[0] = word;
	to_free[1] = ft_itoa(0);
	if (to_free[1] == NULL)
		return (print_error(to_free[0]));
	lst = NULL;
	while (*word != '\0' && errno == 0)
	{
		lst_node = next_parameter_token(&word, to_free[1]);
		if (lst_node == NULL)
			perror(EXPANDER_ERRMSG ": malloc");
		ft_lstadd_back(&lst, lst_node);
	}
	str = NULL;
	if (errno == 0)
		str = lst_to_str(lst);
	ft_lstclear(&lst, NULL);
	free(to_free[0]);
	free(to_free[1]);
	return (str);
}
