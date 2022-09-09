/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:08:53 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include "minishell.h"
# include "environ.h"

# define CD_ERRMSG		"cd"
# define ECHO_ERRMSG	"echo"
# define ENV_ERRMSG		"env"
# define EXIT_ERRMSG	"exit"
# define EXPORT_ERRMSG	"export"
# define PWD_ERRMSG		"pwd"
# define UNSET_ERRMSG	"unset"

int		builtin_echo(char **argv, t_environ *env);
int		builtin_cd(char **argv, t_environ *env);
int		builtin_pwd(char **argv, t_environ *env);
int		builtin_export(char **argv, t_environ *env);
int		builtin_unset(char **argv, t_environ *env);
int		builtin_env(char **argv, t_environ *env);
int		builtin_exit(char **argv, t_environ *env);

#endif /* BUILTIN_H */
