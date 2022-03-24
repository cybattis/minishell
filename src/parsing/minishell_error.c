#include "libft.h"

int	error_return(char *msg, int code)
{
	ft_dprintf(STDERR_FILENO, "%s\n", msg);
	return (code);
}