/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/25 12:10:54 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include "libft.h"
# include "parser.h"
# include "lexer.h"
# include "exec.h"

# define STATUS_FAILURE -1
# define STATUS_SUCCESS 0
# define ARG_MAX_SIZE 4096

volatile sig_atomic_t	g_sig;

void activate_signal(void);
void deactivate_signal(void);
void activate_signal_heredoc(void);
int *exit_status(void);
int rl_status_checker(void);

#endif /* MINISHELL_H */
