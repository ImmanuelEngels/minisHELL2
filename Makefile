# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imengels <imengels@student.42vienna.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/22 13:50:48 by imengels          #+#    #+#              #
#    Updated: 2025/10/22 13:50:50 by imengels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -lreadline -MP -MMD
NAME    = minishell 

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
	main.c

OBJS    = $(SRCS:.c=.o)
DEPS    = $(OBJS:.o=.d)

LIBFT   = libft/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS) $(DEPS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re

