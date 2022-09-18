/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:37:27 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/14 15:56:16 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXIT_H
# define FT_EXIT_H

# include <errno.h>
# include <stddef.h>

void		ft_exit(int exit_no, const char *err_msg);
void		ft_error_exit(int exit_no, const char *msg_prefix, int errno);
const char	*ft_validate_file_ext(const char *filepath, const char *ext, \
	const char *errmsg_pref);
void		*ft_wrapped_malloc(size_t size, int exit_no, const char *err_msg);
int			ft_wrapped_puts(const char *s, int exit_no, const char *err_msg);

#endif /* FT_EXIT_H */