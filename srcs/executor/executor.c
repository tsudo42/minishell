/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
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
	if (heredoc_set(ast_root) == 0)
		ret = exec_l(ast_root);
	else
		ret = 1;
	ast_free_l(ast_root);
	set_exit_status(ret);
	return (ret);
}
