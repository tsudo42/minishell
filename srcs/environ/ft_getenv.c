/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
			return (-1);
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			break ;
		s1++;
		s2++;
		if (!s1 || !s2)
			return (-1);
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_getenv(const char *name)
{
	extern char	**environ;
	char	**tmp;
	char	*content;
	int		len;

//	if (ft_strcmp("?", name) == 0)
//		return (ft_itoa(*exit_status()));
	if (!name)
		return (NULL);
	tmp = environ;
	len = ft_strlen(name);
	while (*tmp)
	{
		if (ft_strncmp(*tmp, name, len) == 0)
		{
			content = ft_strchr(*tmp, '=');
			content++;
			return (content);
		}
		tmp++;
	}
	return (NULL);
}
