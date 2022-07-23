/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ast_internal.h"
#include "libft.h"
#include <stdio.h>

void	print_ast_l(char pref[PRINT_BUFSIZE], t_ast_l *l)
{
	char	pref_tmp[PRINT_BUFSIZE];

	if (l == NULL)
	{
		printf("L: (null)\n");
		return ;
	}
	ft_strlcpy(pref_tmp, pref, PRINT_BUFSIZE);
	ft_strlcat(pref, "|  ", PRINT_BUFSIZE);
	printf("L->");
	print_ast_p(pref, l->p);
	if (l->op == AST_L_AND)
		printf("%s+->\'&&\'\n", pref_tmp);
	else
		printf("%s+->\'||\'\n", pref_tmp);
	ft_strlcpy(pref, pref_tmp, PRINT_BUFSIZE);
	ft_strlcat(pref, "   ", PRINT_BUFSIZE);
	printf("%s\\->", pref_tmp);
	print_ast_l(pref, l->next);
}

void	print_ast_p(char pref[PRINT_BUFSIZE], t_ast_p *p)
{
	char	pref_tmp[PRINT_BUFSIZE];

	if (p == NULL)
	{
		printf("P: (null)\n");
		return ;
	}
	ft_strlcpy(pref_tmp, pref, PRINT_BUFSIZE);
	ft_strlcat(pref, "|  ", PRINT_BUFSIZE);
	printf("P->");
	print_ast_s(pref, p->s);
	printf("%s+->", pref_tmp);
	print_ast_c(pref, p->c);
	ft_strlcpy(pref, pref_tmp, PRINT_BUFSIZE);
	ft_strlcat(pref, "   ", PRINT_BUFSIZE);
	printf("%s\\->", pref_tmp);
	print_ast_p(pref, p->next);
}

void	print_ast_s(char pref[PRINT_BUFSIZE], t_ast_s *s)
{
	char	pref_tmp[PRINT_BUFSIZE];

	if (s == NULL)
	{
		printf("S: (null)\n");
		return ;
	}
	ft_strlcpy(pref_tmp, pref, PRINT_BUFSIZE);
	ft_strlcat(pref, "|  ", PRINT_BUFSIZE);
	printf("S->");
	print_ast_l(pref, s->l);
	ft_strlcpy(pref, pref_tmp, PRINT_BUFSIZE);
	ft_strlcat(pref, "   ", PRINT_BUFSIZE);
	printf("%s\\->", pref_tmp);
	print_ast_d(pref, s->d);
}

void	print_ast_c(char pref[PRINT_BUFSIZE], t_ast_c *c)
{
	char	pref_tmp[PRINT_BUFSIZE];

	if (c == NULL)
	{
		printf("C: (null)\n");
		return ;
	}
	ft_strlcpy(pref_tmp, pref, PRINT_BUFSIZE);
	ft_strlcat(pref, "|  ", PRINT_BUFSIZE);
	printf("C->");
	print_ast_a(pref, c->a);
	ft_strlcpy(pref, pref_tmp, PRINT_BUFSIZE);
	ft_strlcat(pref, "   ", PRINT_BUFSIZE);
	printf("%s\\->", pref_tmp);
	print_ast_d(pref, c->d);
}

void	print_ast(t_ast	*ast)
{
	char	pref[PRINT_BUFSIZE];

	pref[0] = '\0';
	print_ast_l(pref, ast);
}
