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

t_token_list	*token_list_new(
	t_token_type type, char *raw_str, void *other_param)
{
	t_token_list	*token_list;

	token_list = malloc(sizeof(t_token_list));
	if (token_list == NULL)
	{
		free(raw_str);
		free(other_param);
		return (NULL);
	}
	token_list->type = type;
	token_list->raw_str = raw_str;
	token_list->other_param = other_param;
	token_list->next = NULL;
	return (token_list);
}
