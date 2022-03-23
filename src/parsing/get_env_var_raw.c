#include "libft.h"
#include "parsing.h"
#include "minishell.h"

char	*get_env_var_raw(t_parser *parser)
{
	char	*var_name;
	char	*var_value;

	var_name = get_env_var_name(parser);
	if (ft_strlen(var_name) == 0)
		var_value = gc_strdup(get_gc(), "");
	else if (ft_strcmp(var_name, "$") == 0)
		var_value = gc_strdup(get_gc(), "$");
	else if (ft_strcmp(var_name, "?") == 0)
		var_value = gc_itoa(get_gc(), g_minishell.last_return);
	else
		var_value = gc_strdup(get_gc(), getenv(var_name));
	gc_free(get_gc(), var_name);
	return (var_value);
}
