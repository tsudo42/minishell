/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/26 07:54:48 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_internal.h"

int	executor(t_ast *ast_root, t_environ *env)
{
	int	ret;

	if (ast_root == NULL)
		return (258);
	g_sig = 0;
	if (heredoc_ready(ast_root, env) != 0)
		ret = 1;
	else
		ret = exec_l(ast_root, env);
	ast_free_l(ast_root);
	return (ret);
}
