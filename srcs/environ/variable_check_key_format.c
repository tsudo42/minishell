/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_check_key_format.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/31 15:09:46 by hosuzuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "libft.h"
#include <errno.h>

/**
 *  This function checks format of key, and returns 0 when the format does
 *  not contain any problem.
 *
 *  Errno will be set to EINVAL and returns -1 if key is one of following:
 *  - key is NULL.
 *  - key is an empty string.
 *  - key conatains character '='.
 */
int	variable_check_key_format(const char *key)
{
	if (key == NULL || *key == '\0' || ft_strchr(key, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	return (0);
}
