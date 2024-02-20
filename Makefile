# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atok <atok@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 18:40:56 by wyap              #+#    #+#              #
#    Updated: 2024/02/20 18:20:53 by atok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src/
SRC = main.c utils/ft_split.c utils/ft_strlen.c utils/ft_strjoin.c\
		utils/ft_strcmp.c utils/ft_strncmp.c utils/ft_isalnum.c\
		utils/ft_strtrim.c utils/ft_strchr.c utils/ft_isalpha.c\
		utils/ft_strdup.c utils/ft_substr.c parsing/parse_pipe.c\
		utils/utils1.c utils/doubly.c utils/ft_itoa.c parsing/ft_checker.c\
		parsing/node_checker.c parsing/trim_quotes.c parsing/ft_indexing.c\
		parsing/parser.c parsing/combine.c expanding/ft_replace.c\
		expanding/store_env.c expanding/expand_utils.c expanding/get_multiline.c\
		builtins/builtin_utils.c builtins/echo.c builtins/export.c\
		builtins/check_export.c builtins/update_env.c builtins/unset.c\
		builtins/exit.c execute/replace_cmdv2.c execute/execute0.c builtins/cd.c\
		builtins/pwd.c execute/swap_node.c execute/execute1.c execute/init_exe.c\
		execute/no_child.c utils/signal_util.c parsing/index_quote_arrw.c\
		expanding/errno.c execute/rdr.c execute/execute2.c\
		parsing/ft_split_cmd.c # << 

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

GCC = gcc
INCL = -I /usr/local/opt/readline/include
RM = rm -rf
CFLAGS += -Wall -Wextra -Werror $(INCL)
FSAN = -fsanitize=address -g3 -ggdb

.PHONY = all clean fclean re debug

$(NAME): $(OBJ)
	$(GCC) $(CFLAGS) -ggdb -g3 $(OBJ) -o $(NAME) -lreadline -lncurses -L /usr/local/opt/readline/lib

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(NAME)_debug
	@$(RM) *.dSYM

re: fclean all

debug: $(OBJ)
	$(GCC) $(CFLAGS) $(OBJ) $(FSAN) -o $(NAME)_debug -lreadline -lncurses -L /usr/local/opt/readline/lib