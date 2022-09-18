/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:50:53 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:50:58 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include <stdlib.h>

/* ************************************************************************** */
/*  ft_realloc creates a new allocation, copies as much of the old data       */
/*  pointed to by ptr as will fit to the new allocation, frees the old        */
/*  allocation, and returns a pointer to the allocated memory.                */
/*  If ptr is NULL, realloc() is identical to a call to malloc() for size     */
/*  bytes.                                                                    */
/*  If size is zero and ptr is not NULL, a new, minimum sized object is       */
/*  allocated and the original object is freed.                               */
/*  ft_realloc does not guarantee that the additional memory is zero-filled.  */
/* ************************************************************************** */
void	*ft_realloc(void *ptr, size_t prev_bufsize, size_t new_bufsize)
{
	unsigned char	*prev_ptr;
	unsigned char	*new_ptr;
	size_t			i;

	if (new_bufsize == 0)
		new_bufsize = 1;
	new_ptr = malloc(new_bufsize);
	if (new_ptr != NULL)
	{
		prev_ptr = ptr;
		i = 0;
		if (prev_ptr != NULL)
		{
			if (prev_bufsize > new_bufsize)
				prev_bufsize = new_bufsize;
			while (i < prev_bufsize)
			{
				new_ptr[i] = prev_ptr[i];
				i++;
			}
		}
	}
	free(ptr);
	return (new_ptr);
}
