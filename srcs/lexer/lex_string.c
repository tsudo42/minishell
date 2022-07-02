/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

t_token_list	*lex_space_tab(char **input)
{
	size_t	len;
	char	*raw_str;

	len = ft_strspn(*input, " \t");
	if (len == 0)
		return (NULL);
	raw_str = malloc(sizeof(char) * (len + 1));
	if (raw_str == NULL)
		return (NULL);
	ft_strlcpy(raw_str, *input, len + 1);
	*input += len;
	return (token_list_new(SPACE_TAB, raw_str, NULL));
}

t_token_list	*lex_string(char **input)
{
	size_t	len;
	char	*raw_str;

	len = ft_strcspn(*input, " \t\n\'\"<>|");
	raw_str = malloc(sizeof(char) * (len + 1));
	if (raw_str == NULL)
		return (NULL);
	ft_strlcpy(raw_str, *input, len + 1);
	*input += len;
	return (token_list_new(STRING, raw_str, NULL));
}
