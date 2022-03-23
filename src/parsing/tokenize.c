#include "parsing.h"

int		get_last_token_type(t_lexer *lexer);
static t_lexer	tokenize(t_parser parser);
static void		add_next_token(t_lexer *lexer, t_parser *parser);
static t_token	get_next_token(t_lexer *lexer, t_parser *parser);

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
	parser->i = skip_spaces(&parser->str[parser->i]) - parser->str;
	if (parser->str[parser->i])
		lexer_add_token(lexer, get_next_token(lexer, parser));
	else
		lexer_add_end(lexer);
}

static t_token	get_next_token(t_lexer *lexer, t_parser *parser)
{
	t_err_or_charptr	result;
	t_token				token;

	result = get_next_word_parser(parser, 1);
	if (result.error)
	{
		printf("%s\n", result.error);
		token.str = NULL;
		token.type = TOKEN_EMPTY;
		return (token);
	}
	token.str = result.result;
	token.type = get_token_type(token.str, lexer);
	return (token);
}
