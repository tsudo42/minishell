/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strarr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 08:42:37 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

void	*ft_free_strarr(char **str_arr)
{
	void	*str_arr_to_free;

	if (str_arr == NULL)
		return (NULL);
	str_arr_to_free = str_arr;
	while (*str_arr != NULL)
	{
		free(*str_arr);
		*str_arr = NULL;
		str_arr++;
	}
	free(str_arr_to_free);
	return (NULL);
}
