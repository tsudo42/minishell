/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"
#include <stddef.h>

t_token_list	*token_list_join(t_token_list *head, t_token_list *to_append)
{
	t_token_list	*tail;

	if (head == NULL)
		return (to_append);
	if (to_append == NULL)
		return (head);
	tail = head;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = to_append;
	return (head);
}
