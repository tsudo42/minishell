/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "libft.h"

/**
 * The information to be passed to execve.
 */
typedef struct s_cmd {
	pid_t		pid;
	const char	*raw_str;
	char		**args;
	int			redin_fd;
	int			redout_fd;
	int			ret_val;
}	t_cmd;

typedef enum e_cmd_list_type {
	NULL_CMDLIST,
	HEAD,
	PIPELINE,
	OR_CMDLIST,
	AND_CMDLIST,
	BRACES
}	t_cmd_list_type;

typedef struct s_cmd_list {
	pid_t				pid;
	t_cmd_list_type		type;
	union {
		struct s_cmd		*content_cmd;
		struct s_cmd_list	*content_list;
	};
	int					ret_val;
	struct s_cmd_list	*next;
}	t_cmd_list;

int	parser(t_token_list *token_list);

#endif /* PARSER_H */
