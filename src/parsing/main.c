#include "../../includes/parsing.h"
#include "../../libft/libft.h"

int main(int argc, char **argv)
{
	ft_printf("argc: %d\n", argc);
	for (int i = 0; i < argc; i++)
	{
		ft_printf("argv[%d]: %s\n", i, argv[i]);
	}
}
