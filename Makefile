# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atok <atok@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 18:40:56 by wyap              #+#    #+#              #
#    Updated: 2023/12/22 15:02:19 by atok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src/
SRC = main.c utils/ft_split.c utils/ft_strlen.c utils/ft_strjoin.c utils/ft_strcmp.c\
		utils/ft_strncmp.c utils/ft_isalnum.c utils/ft_strtrim.c utils/ft_strchr.c\
		utils/ft_strdup.c utils/ft_substr.c parsing/parse_pipe.c expanding/store_env.c\
		utils/utils1.c utils/doubly.c parsing/ft_check_arrow.c\
		parsing/ft_check_quote.c parsing/ft_indexing.c parsing/ft_replace.c
# parsing/loop_to_pair.c
OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

GCC = gcc
INCL = -I /usr/local/opt/readline/include
RM = rm -rf
CFLAGS += -Wall -Wextra -Werror $(INCL)
FSAN = -fsanitize=address -g3
READLINE_MAC = 

.PHONY = all clean fclean re debug

# Artie's PC: -lncurses flag required
$(NAME): $(OBJ)
	$(GCC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline -lncurses -L /usr/local/opt/readline/lib
# $(READLINE_MAC)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(NAME)_debug
	@echo $(RM) *.dSYM

re: fclean all

debug: $(OBJ)
	$(GCC) $(CFLAGS) $(OBJ) $(FSAN) -o $(NAME)_debug -lreadline -lncurses -L /usr/local/opt/readline/lib