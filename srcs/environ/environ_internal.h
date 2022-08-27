/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:04:02 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_INTERNAL_H
# define ENVIRON_INTERNAL_H

# include "environ.h"

# define ENVIRON_ERRMSG "minishell"

extern char	**environ;

size_t	envlen(char **envp);
int			find_name(const char *name);
void		free_environ(void);
int			print_env(const char *string);
char		**add_environ(const char *string);

#endif

