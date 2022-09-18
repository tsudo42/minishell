/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:07:17 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 17:46:54 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>

/* Normal get_next_line. Can handle multiple fd at the same time. */
/* Also, able to handle binary inputs. */
char	*get_next_line(int fd);

/* Mandetory part of get_next_line. */
char	*get_next_line_easy(int fd);

/* GNL but ignores Ctrl+D. */
char	*gnl_ignore_ctrl_d(int fd);

#endif /* GET_NEXT_LINE_H */
