#include "../libft/libft.h"

int main(int argc, char **argv)
{
	printf("argc: %d\n", argc);
	for (int i = 0; i < argc; i++)
		printf("argv[%d]: [%s]\n", i, argv[i]);

	printf("result: %d\n", contains_unfinished_quotes(argv[1]));
}
