#include "libft.h"
#include "utils.h"

int	ft_putendl_len_fd(const char *s, int fd)
{
	int len;

	len = 0;
	len = ft_strlen(s);
	ft_putstr_fd(s, fd);
	len += write(fd, "\n", 1);
	return (len);
}
