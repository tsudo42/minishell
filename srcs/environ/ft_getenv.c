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

char	*ft_getenv(const char *name)
{
	extern char	**environ;
	char	**tmp;
	char	*content;
	int		len;

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
