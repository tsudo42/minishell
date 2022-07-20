/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# define INTERNAL_ERR_NUM 1

/* ************************************************************************** */
/*  This function duplicates s with allocating memory with malloc(3),         */
/*  at most len length.                                                       */
/* ************************************************************************** */
char	*ft_strndup(const char *s, size_t len);

/* ************************************************************************** */
/*  This function is an error checking version of dup(2).                     */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when dup faces error.                                             */
/* ************************************************************************** */
int		ft_x_dup(int fildes, const char *errmsg);

/* ************************************************************************** */
/*  This function is an error checking version of dup2(2).                    */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when dup2 faces error.                                          */
/* ************************************************************************** */
int		ft_x_dup2(int fildes, int fildes2, const char *errmsg);

/* ************************************************************************** */
/*  This function is an error checking version of execve(2).                  */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when execve faces error.                                          */
/* ************************************************************************** */
void	ft_x_execve(const char *path, char *const argv[], char *const envp[], \
	const char *errmsg);

/* ************************************************************************** */
/*  This function is an error checking version of fork(2).                    */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when fork faces error.                                          */
/* ************************************************************************** */
pid_t	ft_x_fork(const char *errmsg);

/* ************************************************************************** */
/*  This function is an error checking version of malloc(3).                  */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when malloc faces error.                                          */
/* ************************************************************************** */
void	*ft_x_malloc(size_t size, const char *errmsg);

/* ************************************************************************** */
/*  This function is an error checking version of pipe(2).                    */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when pipe faces error.                                           */
/* ************************************************************************** */
void	ft_x_pipe(int fildes[2], const char *errmsg);

/* ************************************************************************** */
/*  This function is an error checking version of waitpid(2).                 */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when waitpid faces error.                                         */
/* ************************************************************************** */
pid_t	ft_x_waitpid(pid_t pid, int *stat_loc, int opitons, const char *errmsg);

#endif /* UTILS_H */
