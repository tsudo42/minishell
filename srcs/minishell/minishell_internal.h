/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/27 17:45:31 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_INTERNAL_H
# define MINISHELL_INTERNAL_H

# include "minishell.h"

# define ARG_MAX_SIZE 4096
# define MAIN_ERRMSG "minishell"

extern volatile sig_atomic_t	g_sig;

int	cleanup_signal(void);
int	ready_signal(void);

#endif /* MINISHELL_H */
