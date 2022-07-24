#include "main.h"

int	ft_exec_heredoc(char *delimi)
{
	int fd_r = fileno(stdin);
//	int fd_w = fileno(stdout);
//	int pipe_child2parent[2];
//	int pipe_parent2child[2];
	int pid;

/*	if (pipe(pipe_child2parent) < 0)
	{
		perror("ft_exec_heredoc");
		return 1;
	}

	if (pipe(pipe_parent2child) < 0)
	{
		perror("ft_exec_heredoc");
		return 1;
	}
*/
	if ((pid = fork()) < 0)
	{
		perror("ft_exec_heredoc");
/*		close(pipe_child2parent[READ]);
		close(pipe_child2parent[WRITE]);
		close(pipe_parent2child[READ]);
		close(pipe_parent2child[WRITE]);
*/		return 1;
	}
	if (pid == 0)
	{
	//	printf("child\n");
		//close(pipe_parent2child[WRITE]);
		//close(pipe_child2parent[READ]);
				//pipe_child2parent[WRITE] 
		fd_r = ft_heredoc(delimi);
//		printf("fd_r: %d\n", fd_r);
		//dup2(fd_r, 0);
	
		//printf("fd_r: %d\n", fd_r);
				//dup2(pipe_parent2child[READ], 0);
		//		dup2(pipe_child2parent[WRITE], 1);
		//		dup2(fd_r, 1);
//		printf("fd_r: %d\n", fd_r);
		//close(pipe_child2parent[WRITE]);
		//lose(pipe_parent2child[READ]);
	}
	int status;
	waitpid(-1, &status, 0);
//	close(pipe_parent2child[READ]);
	//close(pipe_child2parent[WRITE]);

//	fd_r = pipe_child2parent[WRITE];
//	fd_w = pipe_parent2child[WRITE];
//	(void)fd_w;

//	write(fd_w, "aaa", 4);

	char buf[255];
//	printf("fd_r2: %d\n", fd_r);
	int size = read(fd_r, buf, 255);

	if (size == -1)
	{
		perror("error");
		return 1;
	}
	printf("%s", buf);
	//fwrite(buf, 1, size, stdout);
//	printf("\n");
	close (fd_r);
	//close (fd_w);
	return 0;
}
