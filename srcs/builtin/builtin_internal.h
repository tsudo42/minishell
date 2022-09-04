/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:08:50 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_INTERNAL_H
# define BUILTIN_INTERNAL_H

# include "builtin.h"

# define CD_ERRMSG		"cd"
# define ECHO_ERRMSG	"echo"
# define ENV_ERRMSG		"env"
# define EXIT_ERRMSG	"exit"
# define EXPORT_ERRMSG	"export"
# define PWD_ERRMSG		"pwd"
# define UNSET_ERRMSG	"unset"

void	putstrlen_fd(const char *s, size_t max_len, int fd);
int		is_printable(char *s);
void	print_values2(char *str, char *value);
int		print_values(t_environ *env);

#endif /* BUILTIN_H */
