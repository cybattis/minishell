#include <unistd.h>
#include "../libft/libft.h"

int main(int argc, char **argv)
{
	char *line = ft_get_next_line(STDIN_FILENO);

	while (line)
	{
		printf("%s", line);
		line = ft_get_next_line(STDIN_FILENO);
	}
	dprintf(STDERR_FILENO, "FINISH 2 !");
	return (0);
}
