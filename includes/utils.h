/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/31 15:16:49 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <unistd.h>

# define INTERNAL_ERR_NUM 1

/* ************************************************************************** */
/*  This function frees strings contained in an array and itself.             */
/*  String array is (char **)array which contains (char *)string and NULL.    */
/*  This function can be utilized to free the return value of functions like  */
/*  ft_split which returns malloc(3)-ed string array.                         */
/*  This function always returns NULL.                                        */
/* ************************************************************************** */
void	*ft_free_strarr(char **str_array);

/* ************************************************************************** */
/*  This function is an error checking version of dup(2).                     */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when dup faces error.                                             */
/* ************************************************************************** */
int		ft_x_dup(int fildes, const char *errmsg);

/* ************************************************************************** */
/*  This function is an error checking version of dup2(2).                    */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when dup2 faces error.                                            */
/* ************************************************************************** */
int		ft_x_dup2(int fildes, int fildes2, const char *errmsg);

/* ************************************************************************** */
/*  This function is an error checking version of dup2(2).                    */
/*  This function prints an error message and terminates the process and      */
/*  return the new file discriptor. When dup2 faces error, -1 is returned.    */
/* ************************************************************************** */
int		ft_r_dup2(int fildes, int fildes2, const char *errmsg);

/* ************************************************************************** */
/*  This function is an error checking version of fork(2).                    */
/*  This function prints an error message and terminates the process calling  */
/*  exit(3) when fork faces error.                                            */
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
/*  exit(3) when pipe faces error.                                            */
/* ************************************************************************** */
void	ft_x_pipe(int fildes[2], const char *errmsg);

void	ft_perror_exit(int exit_no, const char *errmsg);

/* ************************************************************************** */
/*  This function is an error checking version of strdup(3).                  */
/*  This function prints an error message and terminates the process calling  */
/*  strdup(3) when pipe faces error.                                          */
/* ************************************************************************** */
char	*ft_x_strdup(const char *s1, const char *errmsg);

#endif /* UTILS_H */
