#include "environ.h"

static int find_name(const char *name)
{
	extern char **environ;
	int i;
	int len;

	i = 0;
	len = ft_strlen(name);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_unsetenv(const char *name)
{
	extern char **environ;
	char **tmp;
	int skip;
	int i;
	int j;

	ft_init_environ();
	if ((skip = find_name(name)) == -1)
		return (-1);
	tmp = (char **)malloc(sizeof(char **) * ft_envlen());
	if (!tmp)
		return (-1);
	i = 0;
	j = 0;
	while (environ[j])
	{
		if (i == skip)
			j++;
		if (environ[j])
			tmp[i++] = environ[j++];
	}
	tmp[i] = NULL;
	free (environ);
	environ = tmp;
	return (0);
}