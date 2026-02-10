CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -MP -MMD
RLFLAGS = -lreadline

NAME    = minishell
VALNAME = minishell_val

VAL_CFLAGS = $(CFLAGS) -O0 -g3

SRCS    = ft_cmds_init.c \
	ft_expand_dq.c \
	ft_expander.c \
	ft_free.c \
	ft_getenv.c \
	ft_gloabal.c \
	ft_ifs.c \
	ft_is.c \
	ft_match_found.c \
	ft_minishell_printer.c \
	ft_pipeline.c \
	ft_redir_init.c \
	ft_remove_quotes.c \
	ft_sort_token.c \
	ft_superglue_ifs.c \
	ft_unquoted_expansion.c \
	ft_free_cmds.c \
	main.c

OBJS        = $(SRCS:.c=.o)
DEPS        = $(OBJS:.o=.d)

VAL_OBJS    = $(SRCS:.c=.val.o)
VAL_DEPS    = $(VAL_OBJS:.o=.d)
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all \
           --track-origins=yes --suppressions=readline.supp

LIBFT   = libft/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(RLFLAGS) $(LIBFT) -o $(NAME)

# New target: val
val: $(LIBFT) $(VALNAME)

valrun: val
	$(VALGRIND) ./$(VALNAME)

$(VALNAME): $(VAL_OBJS) $(LIBFT)
	$(CC) $(VAL_CFLAGS) $(VAL_OBJS) $(RLFLAGS) $(LIBFT) -o $(VALNAME)

$(LIBFT):
	$(MAKE) -C libft bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.val.o: %.c
	$(CC) $(VAL_CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS) $(DEPS) $(VAL_OBJS) $(VAL_DEPS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME) $(VALNAME)

re: fclean all

-include $(DEPS) $(VAL_DEPS)

.PHONY: all val valrun clean fclean re

