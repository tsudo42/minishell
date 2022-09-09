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
	{
		ret = 258;
		env->exit_status = 258;
		return (258);
	}
	g_sig = 0;
	if (heredoc_ready(ast_root, env) == 0)
		ret = exec_l(ast_root, env);
	else
		ret = 1;
	ast_free_l(ast_root);
	if (g_sig != 0)
		env->exit_status = 130;
	else
		env->exit_status = ret;
	return (ret);
}
