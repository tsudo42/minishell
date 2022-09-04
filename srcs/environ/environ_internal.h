/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/29 13:10:17 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_INTERNAL_H
# define ENVIRON_INTERNAL_H

# include "environ.h"
# include "utils.h"
# include <stdlib.h>

# define ENVIRON_ERRMSG "minishell"
# define ENV_INITIALIZED 1

size_t	envlen(char **envp);
int		print_env(const char *string);
char	**add_environ(const char *string);
int		is_init_environ(int activation);

#endif
