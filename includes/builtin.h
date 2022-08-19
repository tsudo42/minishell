/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include "minishell.h"
# include "environ.h"

# define BUILT_ERRMSG "minishell"
//# define BUILT_INTERNAL_ERRMSG "builtin internal error"
//# define BUILT_INTERNAL_ERRNUM -1

char *remove_dollormk(char *argv);
int	builtin_echo(char **argv);
int	builtin_cd(char **argv);
int	builtin_pwd(char **argv);
int	builtin_export(char **argv);
int	builtin_unset(char **argv);
int	builtin_env(char **argv);
int	builtin_exit(char **argv);

#endif /* BUILTIN_H */
