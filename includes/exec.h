/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:37:15 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "utils.h"
# include "libft.h"
# include "ast.h"
# include "builtin.h"
# include "environ.h"
# include "expander.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>

/**
 * This function executes the whole commands expressed as AST tree
 * and returns its exit status.
 * If ast_root is NULL, this function returns 1.
 * In that case, this function does not print the error message.
 *
 * Some fatal errors such as malloc(3) error causes terminating the process.
 */
int		executor(t_ast *ast_root, t_environ *env);

#endif /* EXEC_H */
