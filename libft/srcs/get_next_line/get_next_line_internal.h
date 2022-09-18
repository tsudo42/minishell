/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:07:17 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:46:54 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_INTERNAL_H
# define GET_NEXT_LINE_INTERNAL_H

# include "get_next_line.h"
# include <limits.h>

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE <= 0
#   error "invalid BUFFER_SIZE"
#  endif
# else
/* #  warning "BUFFER_SIZE not defined: define as 42" */
#  define BUFFER_SIZE 42
# endif /* BUFFER_SIZE */

# ifndef FD_MAX
#  ifdef OPEN_MAX
#   define FD_MAX OPEN_MAX
#  endif /* OPEN_MAX */
# endif /* FD_MAX */

# ifndef FD_MAX
#  define FD_MAX 1024
# endif /* FD_MAX */

typedef struct s_gnl_buf
{
	void	*ptr;
	size_t	size;
}	t_gnl_buf;

#endif /* GET_NEXT_LINE_INTERNAL_H */
