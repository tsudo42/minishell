/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

/**
 * Type definitions for AST - Abstruct Syntax Tree
 *
 * AST are used to express the result of LR parsing,
 * which is performed upon author-defined following grammar.
 *
 * OP      := && or ||
 * PIPE    := |
 * LBRACE  := (
 * RBRACE  := )
 * RED     := [n]< or [n]> or [n]>> or [n]<<
 * WORD    := a string of characters which is not defined above
 *
 * L     : L OP P
 *       |      P
 *       ;
 * P     : P PIPE S
 *       | P PIPE C
 *       |        S
 *       |        C
 *       ;
 * S     : LBRACE L RBRACE D
 *       | LBRACE L RBRACE
 *       ;
 * C     : C A
 *       |   A
 *       ;
 * A     : RED WORD
 *       |     WORD
 *       ;
 * D     : D RED WORD
 *       |   RED WORD
 *       ;
 */

typedef enum e_ast_d_type {
	AST_D_REDIN,
	AST_D_REDOUT,
	AST_D_REDAPP,
	AST_D_HEREDOC
}	t_ast_d_type;

typedef struct s_ast_d {
	t_ast_d_type	type;
	char			*num;
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

/**
 * These functions generate AST node using malloc(3).
 *
 * The arguments passed to a function is directly connected to a new node
 * as a leaf. Therefore, any arguments passed to a function should not be freed.
 */
t_ast_l	*ast_make_l(t_ast_l *prev_l, t_ast_l_type op, t_ast_p *p);
t_ast_p	*ast_make_p(t_ast_p *prev_p, t_ast_p_type type, void *content);
t_ast_s	*ast_make_s(t_ast_l *l, t_ast_d *d);
t_ast_c	*ast_make_c(t_ast_c *c, t_ast_a *a, t_ast_d *d);
t_ast_a	*ast_make_a(char *red, char *word);
t_ast_d	*ast_make_d(t_ast_d *prev_d, char *red, char *word);

/**
 * This function converts AST node type A into node type D.
 * Nodes t_ast_a:next is not NULL can be handled;
 * in that case, generated Node t_ast_d will have its next node.
 *
 * The arguments passed to this function will be properly transplanted and
 * freed; it is needless to free the argument a externally.
 *
 * AST type A which does not express RED WORD should not be passed to
 * this function; it is recognized as HEREDOC.
 *
 * AST type A is either WORD or RED WORD.
 * However, it is preferable to handle redirections using AST type D
 * and make AST type A to express only command arguments.
 */
t_ast_d	*ast_convert_a_to_d(t_ast_a *a);

/**
 * These functions frees the allocated memory of AST node and
 * its leaves respectively.
 */
void	ast_free_l(t_ast_l *l);
void	ast_free_p(t_ast_p *p);
void	ast_free_s(t_ast_s *s);
void	ast_free_c(t_ast_c *c);
void	ast_free_a(t_ast_a *a);
void	ast_free_d(t_ast_d *d);

/**
 * This function prints AST tree for debugging.
 */
void	print_ast(t_ast	*ast);

#endif /* AST_H */
