/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expander2.c                              :+:      :+:    :+:   */
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
#include <unistd.h>

static void	bad_substitution(const char *str)
{
	if (errno == 0)
	{
		ft_dprintf(STDERR_FILENO, \
			"%s: %s: bad substitution\n", EXPANDER_ERRMSG, str);
		errno = EINVAL;
	}
}

/* str[0] should be '$'. */
static size_t	sep_var_len(char *str)
{
	size_t	i;

	if (ft_isdigit(str[1]) || str[1] == '?')
		return (2);
	i = 2;
	if (ft_isalpha(str[1]) || str[1] == '_')
	{
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		return (i);
	}
	if (str[1] == '{')
	{
		while (str[i] != '\0')
		{
			if (str[i] == '}')
				return (i + 1);
			if (!(ft_isalnum(str[i]) || str[i] == '_'))
				break ;
			i++;
		}
		bad_substitution(str);
		return (ft_strlen(str));
	}
	return (0);
}

static size_t	sep_len(char *str, char *quote)
{
	size_t	i;

	i = 0;
	if (str[0] == '$')
		i = sep_var_len(str);
	if (i > 0)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (*quote == '\0')
				*quote = str[i];
			else if (*quote == str[i])
				*quote = '\0';
		}
		else if (str[i] == '$' && *quote != '\'' && sep_var_len(&(str[i])) > 0)
			return (i);
		i++;
	}
	return (i);
}

static const char	*get_env_helper(char *param, t_environ *env)
{
	char		*param_head;
	const char	*env_var;

	if (*param == '$')
		param++;
	if (*param == '{')
	{
		param_head = param + 1;
		param += ft_strcspn(param, "}");
		*param = '\0';
	}
	else
	{
		param_head = param;
		if (ft_isdigit(*param) || *param == '?')
			*(param + 1) = '\0';
	}
	if (ft_strcmp(param_head, "?") == 0)
		env_var = get_exit_status_str(env);
	else
		env_var = variable_get(param_head, env);
	if (env_var == NULL)
		return ("");
	return (env_var);
}

/* returns the ft_list node of parameter token.                              */
/* (*word)[0] should not be '\0'.                                            */
/* error message of malloc error should be printed outside of this function. */
t_list	*next_parameter_token(char **word, char *quote, t_environ *env)
{
	t_list	*lst;
	char	*word_head;
	size_t	len;
	char	tmp;

	word_head = *word;
	len = sep_len(word_head, quote);
	if (len > 0)
	{
		(*word) += len;
		return (ft_lstnew(word_head));
	}
	len = sep_var_len(word_head);
	(*word) += len;
	if (errno != 0)
		return (NULL);
	tmp = (**word);
	(**word) = '\0';
	lst = ft_lstnew((void *)get_env_helper(word_head, env));
	(**word) = tmp;
	*word_head = '\0';
	return (lst);
}
