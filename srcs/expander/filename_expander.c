/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static DIR	*ready_dir(void)
{
	char	*dirname;
	DIR		*dir;

	dirname = getcwd(NULL, 0);
	if (dirname == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	dir = opendir(dirname);
	free(dirname);
	if (dir == NULL)
	{
		perror("opendir");
		return (NULL);
	}
	return (dir);
}

static t_list	*glob_dir(const char *pattern, DIR *dir)
{
	t_list			*lst;
	t_list			*lst_ent;
	struct dirent	*ent;
	char			*fname;

	lst = NULL;
	ent = readdir(dir);
	while (ent != NULL)
	{
		if (is_match_globstar(pattern, ent->d_name))
		{
			fname = ft_strdup(ent->d_name);
			lst_ent = ft_lstnew(fname);
			if (lst_ent == NULL)
				free(fname);
			ft_lstadd_front(&lst, lst_ent);
		}
		ent = readdir(dir);
	}
	if (errno != 0)
	{
		perror("glob dir");
		ft_lstclear(&lst, free);
	}
	return (lst);
}

t_list	*filename_expander(const char *pattern)
{
	DIR		*dir;
	t_list	*lst;

	errno = 0;
	dir = ready_dir();
	if (dir == NULL)
		return (NULL);
	lst = glob_dir(pattern, dir);
	closedir(dir);
	if (lst != NULL)
		ft_lstmsort(&lst, (void *)ft_strcmp);
	return (lst);
}
