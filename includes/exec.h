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

# define EXEC_ERRMSG "minishell"
# define EXEC_INTERNAL_ERRMSG "exec internal error"
# define EXEC_INTERNAL_ERRNUM -1

/**
 * This function executes the whole commands expressed as AST tree
 * and returns its exit status.
 * If ast_root is NULL, this function returns 1.
 * In that case, this function does not print the error message.
 *
 * Some fatal errors such as malloc(3) error causes terminating the process.
 */
int		executor(t_ast *ast_root);

#endif /* EXEC_H */
