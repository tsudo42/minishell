/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_match_globstar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"

static int	glob_helper(const char *pattern, const char *filename);

static int	glob_star(const char *pattern, const char *filename)
{
	while (*pattern == '*')
		pattern++;
	while (*filename != '\0')
	{
		if (glob_helper(pattern, filename))
			return (1);
		filename++;
	}
	return (*pattern == *filename);
}

static int	glob_in_quote(const char **pat, const char **fname)
{
	char	q;

	q = **pat;
	(*pat)++;
	while (1)
	{
		if (**pat == q)
		{
			(*pat)++;
			return (1);
		}
		if (**pat != **fname)
			return (0);
		if (**fname == '\0' && **pat == '\0')
			return (1);
		(*pat)++;
		(*fname)++;
	}
}

static int	glob_helper(const char *pattern, const char *filename)
{
	while (*filename != '\0')
	{
		if (*pattern == '*')
			return (glob_star(pattern, filename));
		if (*pattern == '\'' || *pattern == '\"')
		{
			if (glob_in_quote(&pattern, &filename) == 0)
				return (0);
			continue ;
		}
		if (*pattern != *filename)
			return (0);
		pattern++;
		filename++;
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == *filename);
}

int	is_match_globstar(const char *pattern, const char *filename)
{
	if (*pattern != '.' && *filename == '.')
		return (0);
	if (glob_helper(pattern, filename))
		return (1);
	return (0);
}
