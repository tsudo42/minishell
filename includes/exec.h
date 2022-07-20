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

# include "builtin.h"
# include "environ.h"
# include "expander.h"

# define EXEC_ERRMSG "minishell"
# define EXEC_INTERNAL_ERRMSG "exec internal error"
# define EXEC_INTERNAL_ERRNUM -1

typedef enum e_ast_d_type {
	AST_D_REDIN,
	AST_D_REDOUT,
	AST_D_REDAPP,
	AST_D_HEREDOC
}	t_ast_d_type;

typedef struct s_ast_d {
	t_ast_d_type	type;
	int				fd;
	char			*word;
	struct s_ast_d	*next;
}	t_ast_d;

typedef struct s_ast_a {
	char			*red;
	char			*word;
	struct s_ast_a	*next;
}	t_ast_a;

typedef struct s_ast_c {
	t_ast_a	*a;
	t_ast_d	*d;
}	t_ast_c;

/* type of t_ast_s.l is t_ast_l, but it cannot be defined here. */

typedef struct s_ast_s {
	void	*l;
	t_ast_d	*d;
}	t_ast_s;

typedef enum e_ast_p_type {
	AST_P_S,
	AST_P_C
}	t_ast_p_type;

typedef struct s_ast_p {
	t_ast_p_type	type;
	t_ast_s			*s;
	t_ast_c			*c;
	struct s_ast_p	*next;
}	t_ast_p;

typedef enum e_ast_l_type {
	AST_L_AND = 0,
	AST_L_OR = 1
}	t_ast_l_type;

typedef struct s_ast_l {
	t_ast_l_type	op;
	t_ast_p			*p;
	struct s_ast_l	*next;
}	t_ast_l;

typedef t_ast_l	t_ast;

int	executor(t_ast *ast_root);

#endif /* EXEC_H */
