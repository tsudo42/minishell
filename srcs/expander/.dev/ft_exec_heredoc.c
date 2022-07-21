#include "main.h"

void	ft_exec_heredoc(char *delimi)
{
	int fd_r = fileno(stdin);
	int fd_w = fileno(stdout);

	int pipe_child2parent[2];
	int pipe_parent2child[2];
	int pid;

	if (pipe(pipe_child2parent) < 0)
	{
		perror("popen2");
		return 1;
	}
	if (pipe(pipe_parent2child) < 0)
	{
		perror("popen2");
		close(pipe_child2parent[READ]);
		close(pipe_child2parent[WRITE]);
		return 1;
	}
	if ((pid = fork()) < 0)
	{
		perror("popen2");
		close(pipe_child2parent[READ]);
		close(pipe_child2parent[WRITE]);
		close(pipe_parent2child[READ]);
		close(pipe_parent2child[WRITE]);
		return 1;
	}
	if (pid == 0)
	{
		close(pipe_parent2child[WRITE]);
		close(pipe_child2parent[READ]);
		dup2(pipe_parent2child[READ], 0);
		dup2(pipe_child2parent[WRITE], 1);
		close(pipe_parent2child[READ]);
		close(pipe_child2parent[WRITE]);
		if (ft_heredoc("EOF") < 0)
		{
			perror("popen2");
//			close(pipe_parent2child[READ]);
//			close(pipe_child2parent[WRITE]);
			return 1;
		}
	}
	close(pipe_parent2child[READ]);
	close(pipe_child2parent[WRITE]);
	*fd_r = pipe_child2parent[READ];
	*fd_w = pipe_parent2child[WRITE];
	return pid;	popen2(&fd_r, &fd_w);

	write(fd_w, argv[1], strlen(argv[1]));
//
	char buf[255];
	int size = read(fd_r, buf, 255);

	if (size == -1)
	{
		perror("error");
		return 1;
	}
	fwrite(buf, 1, size, stdout);
//	printf("\n");
	return 0;
}
