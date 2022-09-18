/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_file_ext.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/07 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exit.h"
#include "ft_put.h"
#include <unistd.h>

static void	wrong_file_extension(const char *filepath, const char *errmsg_pref)
{
	if (errmsg_pref != NULL)
		ft_putstr_fd(errmsg_pref, STDERR_FILENO);
	if (filepath == NULL)
		ft_exit(1, "invalid filename");
	ft_putstr_fd("unsupported file format: ", STDERR_FILENO);
	ft_exit(1, filepath);
}

const char	*ft_validate_file_ext(const char *filepath, const char *ext, \
	const char *errmsg_pref)
{
	size_t	fp_i;
	size_t	ext_i;

	if (filepath == NULL)
		wrong_file_extension(filepath, errmsg_pref);
	if (ext == NULL)
		return (filepath);
	fp_i = 0;
	while (filepath[fp_i] != '\0')
		fp_i++;
	ext_i = 0;
	while (ext[ext_i] != '\0')
		ext_i++;
	while (fp_i > 0 && ext_i > 0)
	{
		if (filepath[fp_i] != ext[ext_i])
			wrong_file_extension(filepath, errmsg_pref);
		fp_i--;
		ext_i--;
	}
	if (ext_i != 0 || fp_i == 0 || filepath[fp_i] == '/')
		wrong_file_extension(filepath, errmsg_pref);
	return (filepath);
}
