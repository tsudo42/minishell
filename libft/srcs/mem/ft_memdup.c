/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:36:23 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/05 23:42:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  This function creates a duplicate of memory using malloc(3).              */
/* ************************************************************************** */
void	*ft_memdup(const void *ptr, size_t size)
{
	void	*new_ptr;

	if (size == 0 || ptr == NULL)
		return (NULL);
	new_ptr = malloc(size);
	ft_memmove(new_ptr, ptr, size);
	return (new_ptr);
}
