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

/* ************************************************************************** */
/*  This function duplicates s with allocating memory with malloc(3),         */
/*  at most len length.                                                       */
/* ************************************************************************** */
char	*ft_strndup(const char *s, size_t len);

/* ************************************************************************** */
/*  This function allocates size memory using malloc(3).                      */
/*  If malloc(3) fails, exit with 256 + errno by malloc(3).                   */
/* ************************************************************************** */
void	*x_malloc(size_t size);

#endif /* UTILS_H */