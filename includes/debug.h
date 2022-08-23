/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

/**
 * Function to debug lexer().
 * Input via stdin and print the token list.
 * Always returns 0.
 */
int		debug_lexer(void);

/**
 * Function to debug lexer() and parser().
 * Input via stdin and print the generated AST tree.
 * Always returns 0.
 */
int		debug_syntax(void);

/**
 * Function to debug execpath().
 * Input via stdin and print the result of execpath.
 * Always returns 0.
 */
int		debug_execpath(void);

/**
 * Function to debug expander().
 * Input via stdin and print the str list.
 * Always returns 0.
 */
int		debug_expander(void);

#endif /* DEBUG_H*/
