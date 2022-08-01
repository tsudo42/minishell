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
	while (*env_var)
		res[i++] = *(env_var++);
	res[i++] = '=';
	while (*content)
		res[i++] = *(content++);
	res[i] = '\0';
	return (res);
}
//return value can be void?
int	ft_setenv(const char *env_var, const char *content, int overwrite)
{
	extern char	**environ;
	char	**tmp;
	int i;

	(void)overwrite;
	tmp = ft_init_environ(1);
	i = 0;
	while (environ[i])
	{
		tmp[i] = environ[i];
		i++;
	}
	tmp[i] = env_strjoin(env_var, content);
	if (!tmp[i++])
		return (-1);
	tmp[i] = NULL;
//	free(environ);
	environ = tmp;
	return (0);
}
