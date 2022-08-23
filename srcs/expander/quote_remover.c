/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <stdio.h>
#include <stdlib.h>

void	quote_remover_helper(char *dst, char *src)
{
	char	q;

	while (*src != '\0')
	{
		if (*src == '\'' || *src == '\"')
		{
			q = *src++;
			while (*src != '\0' && *src != q)
				*dst++ = *src++;
			if (*src == '\0')
				break ;
		}
		else
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}

t_list	*quote_remover(char *word)
{
	t_list	*lst;

	lst = ft_lstnew(NULL);
	if (lst == NULL)
	{
		free(word);
		perror(EXPANDER_ERRMSG ": malloc");
		return (NULL);
	}
	lst->content = word;
	quote_remover_helper(word, word);
	return (lst);
}
