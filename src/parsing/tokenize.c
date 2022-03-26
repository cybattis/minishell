#include "parsing.h"
#include "libft.h"
#include "core.h"

int		get_last_token_type(t_lexer *lexer);
static t_lexer	tokenize(t_parser parser);
static void		add_next_token(t_lexer *lexer, t_parser *parser);
static t_token	get_next_token(t_lexer *lexer, t_parser *parser, int *finished);

void	tokenize_all(t_lexer **lexers, t_parser *parsers, size_t count)
{
	size_t	i;

	*lexers = gc_calloc(get_gc(), count, sizeof (t_lexer));
	i = 0;
	while (i < count)
	{
		(*lexers)[i] = tokenize(parsers[i]);
		i++;
	}
}

static t_lexer	tokenize(t_parser parser)
{
	t_lexer	lexer;

	lexer.count = 0;
	lexer.tokens = NULL;
	while (get_last_token_type(&lexer) != TOKEN_END)
		add_next_token(&lexer, &parser);
	return (lexer);
}

static void	add_next_token(t_lexer *lexer, t_parser *parser)
{
	int	has_more_tokens;

	has_more_tokens = 1;
	parser->i = skip_spaces(&parser->str[parser->i]) - parser->str;
	if (parser->str[parser->i])
		while (has_more_tokens)
			lexer_add_token(lexer, get_next_token(lexer, parser, &has_more_tokens));
	else
		lexer_add_end(lexer);
}

static t_token	get_next_token(t_lexer *lexer, t_parser *parser, int *finished)
{
	static t_err_or_char2ptr	result;
	static int					index;
	t_token						token;
	t_parser					parser_copy;

	parser_copy = *parser;
	if (index == 0)
		result = get_next_word_splitted(parser);
	if (result.error)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", result.error);
		token.str = NULL;
		token.type = TOKEN_EMPTY;
		return (token);
	}
	token.str = result.result[index];
	if (index < (int)gc_strarray_size(result.result) - 1)
		index++;
	else
		index = 0;
	token.type = get_token_type(token.str, lexer, parser_copy);
	*finished = index;
	return (token);
}
