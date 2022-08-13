/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static size_t	get_word_len(char *word)
{
	size_t	i;
	char	q;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\'' || word[i] == '\"')
		{
			q = word[i];
			i++;
			while (word[i] != '\0' && word[i] != q)
				i++;
			if (word[i] != '\0')
				i++;
		}
		else if (word[i] == ' ' || word[i] == '\t' || word[i] == '\n')
			break ;
		else
			i++;
	}
	return (i);
}

t_list	*word_splitter(char *word)
{
	t_list	*lst;
	t_list	*lst_node;
	size_t	len;
	char	*str;

	lst = NULL;
	word += ft_strspn(word, " \t\n");
	while (*word != '\0')
	{
		len = get_word_len(word);
		str = ft_strndup(word, len);
		lst_node = ft_lstnew(str);
		if (str == NULL || lst_node == NULL)
		{
			perror(EXPANDER_ERRMSG ": malloc");
			free(str);
			free(lst_node);
			ft_lstclear(&lst, NULL);
			return (NULL);
		}
		ft_lstadd_back(&lst, lst_node);
		word += len;
		word += ft_strspn(word, " \t\n");
	}
	return (lst);
}
