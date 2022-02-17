CLIENT_SRCS	=		get_token.c lexer.c parsing.c

OBJS		=		$(addprefix $(OBJDIR), $(CLIENT_SRCS:.c=.o))

DEPENDS		=		$(addprefix $(OBJDIR), $(CLIENT_SRCS:.c=.d))

.PHONY: all
all:				$(OBJS)

$(OBJDIR)%.o:		%.c
					@echo "[Minishell] Compiling $<"
					@mkdir -p $(OBJDIR)
					@$(BIN_CC) -c $< $(BIN_CFLAGS) -o $@

.PHONY: clean
clean:
					rm -f $(DEPENDS)
					rm -f $(OBJS)

-include $(DEPENDS)