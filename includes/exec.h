/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "ast.h"
# include "builtin.h"
# include "environ.h"
# include "expander.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <wait.h>

# define READ 0
# define WRITE 1

# define EXEC_ERRMSG "minishell"
# define EXEC_INTERNAL_ERRMSG "exec internal error"
# define EXEC_INTERNAL_ERRNUM -1

int		executor(t_ast *ast_root);
int	ft_strcmp(const char *s1, const char *s2);
int	exec_d_heredoc(const char *delimi, int fd);

#endif /* EXEC_H */
