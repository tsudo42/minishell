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

#ifndef EXPANDER_H
# define EXPANDER_H

# include "ft_list.h"

# define EXPAND_ERRMSG "minishell"
# define EXPAND_INTERNAL_ERRMSG "expander internal error"
# define EXPAND_INTERNAL_ERRNUM -1

char	*execpath(char *name);

int		is_match_globstar(const char *pattern, const char *filename);
t_list	*next_parameter_token(char **word);

char	*parameter_expander(char *word);
t_list	*word_splitter(char *words);
t_list	*filename_expander(const char *str);
t_list	*quote_remover(char *word);

t_list	*expander(char *word);

#endif /* EXPANDER_H */
