/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

t_token_list	*lex_single_quote(char **input)
{
	size_t	len;
	char	*raw_str;

	if (**input != '\'')
		return (NULL);
	len = ft_strcspn(*input + 1, "\'") + 1;
	if ((*input)[len] == '\0')
		return (token_list_new(NULL_TOKEN, ft_strdup(*input), NULL));
	\
	raw_str = malloc(sizeof(char) * (len + 2));
	if (raw_str == NULL)
		return (NULL);
	ft_strlcpy(raw_str, *input, len + 2);
	*input += len + 1;
	return (token_list_new(SQ_STRING, raw_str, NULL));
}

t_token_list	*lex_double_quote(char **input)
{
	size_t	len;
	char	*raw_str;

	if (**input != '\"')
		return (NULL);
	len = ft_strcspn(*input + 1, "\"") + 1;
	if ((*input)[len] == '\0')
		return (token_list_new(NULL_TOKEN, ft_strdup(*input), NULL));
	\
	raw_str = malloc(sizeof(char) * (len + 2));
	if (raw_str == NULL)
		return (NULL);
	ft_strlcpy(raw_str, *input, len + 2);
	*input += len + 1;
	return (token_list_new(DQ_STRING, raw_str, NULL));
}
