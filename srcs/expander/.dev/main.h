#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include "libft.h"
#include <sys/types.h>
#include <sys/wait.h>


//#define READ  (0)
//#define WRITE (1)

#define STATUS_FAILURE -1
#define ARG_MAX_SIZE 4096

int	g_status;

int	ft_exec_heredoc(char *delimi);

//size_t	ft_strlen(const char *s);

int ft_heredoc(char *delimi);

#endif
