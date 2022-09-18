/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/16 16:37:49 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include "environ.h"

# define BUILTIN_SUCCESS	0
# define BUILTIN_FAILURE	1
# define BUILTIN_FATALERROR	2

# define CD_ERRMSG		"minishell: cd"
# define ECHO_ERRMSG	"minishell: echo"
# define ENV_ERRMSG		"minishell: env"
# define EXIT_ERRMSG	"minishell: exit"
# define EXPORT_ERRMSG	"minishell: export"
# define PWD_ERRMSG		"minishell: pwd"
# define UNSET_ERRMSG	"minishell: unset"

int		builtin_echo(char **argv, t_environ *env);
int		builtin_cd(char **argv, t_environ *env);
int		builtin_pwd(char **argv, t_environ *env);
int		builtin_export(char **argv, t_environ *env);
int		builtin_unset(char **argv, t_environ *env);
int		builtin_env(char **argv, t_environ *env);
int		builtin_exit(char **argv, t_environ *env);

#endif /* BUILTIN_H */
