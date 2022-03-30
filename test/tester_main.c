#include <unistd.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
	char *line;
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		strerror(errno);
		return (1);
	}
	while ((line = ft_get_next_line(fd)) != NULL)
	{
		dprintf(STDIN_FILENO, "%s", line);
		free(line);
	}
	dprintf(STDERR_FILENO, "FINISH !\n");
	close(fd);
	return (0);
}
