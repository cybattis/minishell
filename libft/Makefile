NAME				=		libft.a
NAMED				=		libftd.a
CC					=		gcc
CFLAGS				=		-Wall -Wextra -o2 -I.
CFLAGSD				=		$(CFLAGS) $(FSANITIZE)
FSANITIZE			=		-fsanitize=address
DEPS				=		libft.h

#=========================
#===========SRCS==========
#=========================
#LinkLists
LINKLISTDIR			=		data_structures/link_list/
LINKLIST			=		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstize.c	\
							ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

#Dynamic Arrays
DARRAYDIR			=		data_structures/dynamic_array/
DARRAY				=		darray_create.c darray_add.c darray_remove.c darray_get.c darray_free.c darray_utils.c		\

#IO
IODIR				=		io/
IO					=		ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_get_next_line.c			\
							ft_putnbr_base_fd.c ft_format_valid.c ft_valid_args.c

#Printf
PRINTFDIR			=		io/printf/
PRINTF				=		ft_print_char.c ft_print_hex.c ft_print_hex_big.c ft_print_integer.c ft_print_ptr.c			\
							ft_print_str.c ft_print_uinteger.c ft_printf.c

#Memory Management
MEMORYDIR			=		memory/
MEMORY				=		ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c			\
							ft_memseti.c ft_memsetf.c

#C style strings
CSTRINGSDIR			=		strings/cstrings/
CSTRINGS			=		ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c		\
 							ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c 	\
 							ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c 	\
 							ft_tolower.c ft_toupper.c ft_split_size.c ft_split_free.c ft_atol_base.c ft_trim.c 			\
 							ft_isspace.c ft_str_count.c ft_word_size.c ft_strcmp.c ft_strappend.c

#Stringviews
STRINGVIEWDIR		=		strings/string_view/
STRINGVIEW			=		sv_create.c

#Basic Maths
BASICMATHDIR		=		maths/basics/
BASICMATH			=		ft_factorial.c ft_pow2.c ft_sqrt.c ft_trig.c ft_modf.c ft_lerp.c

#Vectors
VECTORSDIR			=		maths/vectors/
VECTORS				=		vec2_init.c vec2_add.c vec2_div.c vec2_magnitude.c vec2_mult.c vec2_normalize.c				\
							vec3_init.c vec3_add.c vec3_div.c vec3_magnitude.c vec3_mult.c vec3_normalize.c				\
							vec3_lerpf.c vec3_clamp.c																	\
							vec4_init.c vec4_add.c vec4_div.c vec4_mult.c												\

#Matrix
MATRIXDIR			=		maths/matrix/
MATRIX				=		mat4_init.c mat4_mult.c mat4_mvp.c mat4_rotation.c mat4_scale.c

#Standard
STANDARDDIR			=		standard/
STANDARD			=		ft_error_exit.c ft_random.c

#Garbage collector
GCDIR				=		memory/garbage_collector/
GC					=		gc_init.c gc_calloc.c gc_free.c gc_itoa.c gc_split.c gc_split_free.c gc_strdup.c			\
							gc_strappend.c gc_substr.c gc_strjoin.c gc_strarray_init.c gc_strarray_append.c				\
							gc_strarray_free.c gc_strarray_from.c gc_strarray_size.c gc_strarray_asstr.c				\
							gc_get_next_line.c																			\


SRCS				=		$(addprefix $(LINKLISTDIR), $(LINKLIST))													\
							$(addprefix $(DARRAYDIR), $(DARRAY)) 														\
							$(addprefix $(IODIR), $(IO)) 																\
							$(addprefix $(PRINTFDIR), $(PRINTF)) 														\
							$(addprefix $(MEMORYDIR), $(MEMORY)) 														\
							$(addprefix $(CSTRINGSDIR), $(CSTRINGS)) 													\
							$(addprefix $(BASICMATHDIR), $(BASICMATH)) 													\
							$(addprefix $(VECTORSDIR), $(VECTORS)) 														\
							$(addprefix $(MATRIXDIR), $(MATRIX)) 														\
							$(addprefix $(STANDARDDIR), $(STANDARD)) 													\
							$(addprefix $(GCDIR), $(GC)) 																\


OBJSDIR				=		objs/
OBJS				=		$(addprefix $(OBJSDIR), $(notdir $(SRCS:.c=.o)))

OBJSDIRD			=		objsd/
OBJSD				=		$(addprefix $(OBJSDIRD), $(notdir $(SRCS:.c=d.o)))


#RELEASE
$(OBJSDIR)%.o:		$(LINKLISTDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIR)
					@$(CC) -c $< $(CFLAGS) -o $@
$(OBJSDIR)%.o:		$(DARRAYDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIR)
					@$(CC) -c $< $(CFLAGS) -o $@
$(OBJSDIR)%.o:		$(IODIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIR)
					@$(CC) -c $< $(CFLAGS) -o $@
$(OBJSDIR)%.o:		$(PRINTFDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIR)
					@$(CC) -c $< $(CFLAGS) -o $@
$(OBJSDIR)%.o:		$(MEMORYDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIR)
					@$(CC) -c $< $(CFLAGS) -o $@
$(OBJSDIR)%.o:		$(CSTRINGSDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIR)
					@$(CC) -c $< $(CFLAGS) -o $@
$(OBJSDIR)%.o:		$(STRINGVIEWDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIR)
					@$(CC) -c $< $(CFLAGS) -o $@
$(OBJSDIR)%.o:		$(BASICMATHDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIR)
					@$(CC) -c $< $(CFLAGS) -o $@
$(OBJSDIR)%.o:		$(VECTORSDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIR)
					@$(CC) -c $< $(CFLAGS) -o $@
$(OBJSDIR)%.o:		$(MATRIXDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIR)
					@$(CC) -c $< $(CFLAGS) -o $@
$(OBJSDIR)%.o:		$(STANDARDDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIR)
					@$(CC) -c $< $(CFLAGS) -o $@
$(OBJSDIR)%.o:		$(GCDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIR)
					@$(CC) -c $< $(CFLAGS) -o $@

#DEBUG
$(OBJSDIRD)%d.o:	$(LINKLISTDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIRD)
					@$(CC) -c $< $(CFLAGSD) -o $@
$(OBJSDIRD)%d.o:	$(DARRAYDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIRD)
					@$(CC) -c $< $(CFLAGSD) -o $@
$(OBJSDIRD)%d.o:	$(IODIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIRD)
					@$(CC) -c $< $(CFLAGSD) -o $@
$(OBJSDIRD)%d.o:	$(PRINTFDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIRD)
					@$(CC) -c $< $(CFLAGSD) -o $@
$(OBJSDIRD)%d.o:	$(MEMORYDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIRD)
					@$(CC) -c $< $(CFLAGSD) -o $@
$(OBJSDIRD)%d.o:	$(CSTRINGSDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIRD)
					@$(CC) -c $< $(CFLAGSD) -o $@
$(OBJSDIRD)%d.o:	$(STRINGVIEWDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIRD)
					@$(CC) -c $< $(CFLAGSD) -o $@
$(OBJSDIRD)%d.o:	$(BASICMATHDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIRD)
					@$(CC) -c $< $(CFLAGSD) -o $@
$(OBJSDIRD)%d.o:	$(VECTORSDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIRD)
					@$(CC) -c $< $(CFLAGSD) -o $@
$(OBJSDIRD)%d.o:	$(MATRIXDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIRD)
					@$(CC) -c $< $(CFLAGSD) -o $@
$(OBJSDIRD)%d.o:	$(STANDARDDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIRD)
					@$(CC) -c $< $(CFLAGSD) -o $@
$(OBJSDIRD)%d.o:	$(GCDIR)%.c $(DEPS)
					@echo "Compiling $<"
					@mkdir -p $(OBJSDIRD)
					@$(CC) -c $< $(CFLAGSD) -o $@


all:				$(NAME)

debug:				$(OBJSD) Makefile
					@ar -rcs $(NAMED) $(OBJSD)

$(NAME):			$(OBJS) Makefile
					@ar -rcs $(NAME) $(OBJS)

clean:
					@rm -f $(OBJSDIR)*.o
					@rm -f $(OBJSDIRD)*.o

fclean: clean
					@rm -f $(NAME)
					@rm -f $(NAMED)

re: fclean all
