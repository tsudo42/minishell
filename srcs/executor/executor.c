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

int	executor(t_ast *ast_root)
{
	int	ret;

	if (ast_root == NULL)
	{
		ret = 258;
		set_exit_status(ret);
		return (ret);
	}
	g_sig = 0;
	if (heredoc_ready(ast_root) == 0)
		ret = exec_l(ast_root);
	else
		ret = 1;
	ast_free_l(ast_root);
	if (g_sig == 0)
		set_exit_status(ret);
	else
		set_exit_status(130);
	return (ret);
}
