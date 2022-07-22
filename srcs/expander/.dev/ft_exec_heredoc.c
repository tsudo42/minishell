#include "main.h"

int	ft_exec_heredoc(char *delimi)
{
	int fd_r = fileno(stdin);
	char buf[255];
	
	fd_r = ft_heredoc(delimi);
	int size = read(fd_r, buf, 255);
	if (size == -1)
	{
		perror("error");
		return 1;
	}
	printf("%s", buf);
	close (fd_r);
	return 0;
}
