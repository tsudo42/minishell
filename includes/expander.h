/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/28 16:39:50 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "ft_list.h"
# include "environ.h"

# define EXPANDER_ERRMSG "minishell"

/**
 * This function generates full path of executable file searched using PATH
 * environment variable using ft_getenv() and malloc(3).
 * If no executable is found, this function dupricates the passed argument
 * using malloc(3).
 *
 * NULL is returned only when this function encounters malloc(3) error.
 * In that case, error message will be printed using perror(3).
 */
char	*execpath(char *name, t_environ *env);

/**
 * This function evaluates whether patten matches filename as a result of
 * filename expansion.
 */
int		is_match_globstar(const char *pattern, const char *filename);

/**
 * This function takes malloc(3)-ed string, performs the parameter expansion,
 * and returns the result using malloc(3).
 * The word passed to this function will be freed.
 * Upon malloc(3) error, error message will be printed.
 * Errno will be initialized in the beginning of this call.
 */
char	*parameter_expander(char *word, t_environ *env);

/**
 * This function performs word splitting and returns split word list using
 * malloc(3).
 * The words passed to this function will be freed.
 * Upon malloc(3) error, this function prints error message using perror(3)
 * and returns NULL.
 * Errno will be initialized in the beginning of this call.
 *
 * Blank word will be result in returning NULL, so caller should refer
 * to errno to identify whether NULL return is caused by malloc(3) error
 * or blank word.
 */
t_list	*word_splitter(char *words);

/**
 * This function performs filename expansion and returns a word.
 * The words passed to this function will NOT be freed.
 * This function internally calls malloc(3), getcwd(3), and
 * open/read/closedir(3) functions. Upon those error, this function prints
 * error message using perror(3).
 * Errno will be initialized in the beginning of this call.
 */
t_list	*filename_expander(const char *str);

/**
 * This function performs quote removal and returns a word.
 * Upon malloc(3) error, error message will be printed and NULL is returned.
 *
 * The allocation memory passed to this function as an argument will be
 * utilized to returned list or freed. Caller should not free the argument.
 */
t_list	*quote_remover(char *word);

/**
 * This function generates expansion listed above and returns a word list.
 * When This function encounters any error, error message will be printed
 * and NULL will be returned.
 * Caller does not need to free the word passed to this function.
 *
 * NULL is returned either to represent error or blank word.
 * Caller should recognize referring to errno.
 */
t_list	*expander(char *word, t_environ *env);

#endif /* EXPANDER_H */
