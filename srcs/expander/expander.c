/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <errno.h>
#include <stdlib.h>

static int	is_star_detected(char *word)
{
	char	q;

	if (word == NULL)
		return (0);
	q = '\0';
	while (*word != '\0')
	{
		if (*word == '\'' || *word == '\"')
		{
			q = *word;
			word++;
			while (*word != '\0' && *word != q)
				word++;
			if (*word == '\0')
				return (0);
			word++;
		}
		else if (*word == '*')
			return (1);
		else
			word++;
	}
	return (0);
}

static t_list	*expander2(t_list *lst)
{
	t_list	*lst2;
	t_list	*lst_new;

	lst2 = NULL;
	while (lst != NULL)
	{
		lst_new = NULL;
		if (is_star_detected(lst->content))
			lst_new = filename_expander(lst->content);
		if (lst_new == NULL && errno == 0)
		{
			lst_new = quote_remover(lst->content);
			lst->content = NULL;
		}
		if (lst_new == NULL)
		{
			ft_lstclear(&lst2, free);
			return (NULL);
		}
		ft_lstadd_back(&lst2, lst_new);
		lst = lst->next;
	}
	return (lst2);
}

t_list	*expander(char *word, t_environ *env)
{
	t_list	*lst;
	t_list	*lst2;

	errno = 0;
	word = parameter_expander(word, env);
	if (word == NULL)
		return (NULL);
	lst = word_splitter(word);
	free(word);
	if (lst == NULL)
		return (NULL);
	lst2 = expander2(lst);
	ft_lstclear(&lst, free);
	return (lst2);
}
