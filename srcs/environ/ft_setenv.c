/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

/*
static void	allocate_env(void)
{
	extern char	**environ;
	char		**tmp;
	char		*env_var;
	char		*content;

	tmp = environ;
	while (*tmp != NULL)
	{
		env_var = ft_strdup(*tmp);
		content = ft_strchr(env_var, '=');
		*content = '\0';
		content++;
		ft_setenv(env_var, content);
		free(env_var);
		tmp++;
	}
}
*/
char *env_strjoin(const char *env_var, const char *content)
{
	char *res;
	int len1;
	int	len2;
	int i;
	
	if (!env_var || !content)
		return (NULL);
	len1 = ft_strlen(env_var);
	len2 = ft_strlen(content);
	res = (char *)malloc(sizeof(char) * (len1 + len2 + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (*env_var)
		res[i++] = *(env_var++);
	res[i++] = '=';
	while (*content)
		res[i++] = *(content++);
	res[i] = '\0';
	return (res);
}

int	ft_setenv(const char *env_var, const char *content, int overwrite)
{
	extern char	**environ;
	char **env_new;
	int i;
	int len;

	(void)overwrite;
	ft_init_environ();
	len = ft_envlen();
	env_new = (char **)malloc(sizeof(char **) * len + 2);
	if (!env_new)
	{
		perror("ft_init_environ");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (environ[i])
	{
		env_new[i] = environ[i];
		i++;
	}
	env_new[i] = env_strjoin(env_var, content);
	if (!env_new[i++])
		return (-1);
	env_new[i] = NULL;
	free(environ);
	environ = env_new;
	return (0);
}
