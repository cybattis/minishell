SRCS		=		get_token.c lexer.c parsing.c

OBJS		=		$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPENDS		=		$(addprefix $(OBJS_DIR), $(SRCS:.c=.d))

.PHONY: all
all:				$(OBJS)

$(OBJS_DIR)%.o:		%.c
					@echo "[Minishell] Compiling $<"
					@mkdir -p $(OBJS_DIR)
					@$(BIN_CC) -c $< $(BIN_CFLAGS) -o $@

.PHONY: clean
clean:
					rm -f $(DEPENDS)
					rm -f $(OBJS)

tests:				$(OBJS) parsing_tests.c
					$(BIN_CC) $(BIN_LDFLAGS) $(OBJS) parsing_tests.c -o tests
					@./tests
					@rm testsb

-include $(DEPENDS)