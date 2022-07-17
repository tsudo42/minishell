/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

t_token_list	*token_list_new(t_lr_token_type type, char *str)
{
	t_token_list	*token_list;

	token_list = malloc(sizeof(t_token_list));
	if (token_list == NULL)
	{
		free(str);
		return (NULL);
	}
	token_list->type = type;
	token_list->str = str;
	token_list->next = NULL;
	return (token_list);
}
