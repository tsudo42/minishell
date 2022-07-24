/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast2.c                                       :+:      :+:    :+:   */
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

void	print_ast_a(char pref[PRINT_BUFSIZE], t_ast_a *a)
{
	if (a == NULL)
	{
		printf("A: (null)\n");
		return ;
	}
	printf("A->red: %s\n", a->red);
	printf("%s+->word: %s\n", pref, a->word);
	printf("%s\\->", pref);
	ft_strlcat(pref, "   ", PRINT_BUFSIZE);
	print_ast_a(pref, a->next);
}

void	print_ast_d(char pref[PRINT_BUFSIZE], t_ast_d *d)
{
	if (d == NULL)
	{
		printf("D: (null)\n");
		return ;
	}
	printf("D->num: %s\n", d->num);
	printf("%s+->red: ", pref);
	if (d->type == AST_D_REDIN)
		printf("redin(<)\n");
	else if (d->type == AST_D_REDOUT)
		printf("redout(>)\n");
	else if (d->type == AST_D_REDAPP)
		printf("redapp(>>)\n");
	else if (d->type == AST_D_HEREDOC)
		printf("heredoc(<<)\n");
	else
		printf("undefined error\n");
	printf("%s+->word: %s\n", pref, d->word);
	printf("%s\\->", pref);
	ft_strlcat(pref, "   ", PRINT_BUFSIZE);
	print_ast_d(pref, d->next);
}
