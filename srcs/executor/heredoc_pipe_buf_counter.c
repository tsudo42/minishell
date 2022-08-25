/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe_buf_counter.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/25 11:38:29 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int heredoc_pipe_buf_counter(char *line)
{
	static int len;

	len += ft_strlen(line);
	if (PIPE_BUFF_MAX < len)
	{
		perror(EXEC_ERRMSG ": buf_max");
		return (-1);
	}
	return (0);
}
