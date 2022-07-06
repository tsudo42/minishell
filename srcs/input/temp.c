int	main(void)
{
	char *line;

	line = NULL;
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL || ft_strlen(line) == 0)
		{
			free(line);
			break;
		}
//		printf("line is '%s'\n", line);
		add_history(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}
