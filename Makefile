# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wyap <wyap@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 18:40:56 by wyap              #+#    #+#              #
#    Updated: 2023/11/06 18:45:54 by wyap             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell


SRC_DIR = src/
SRC = 
OBJ = $(addprefix, $(SRC_DIR), $(SRC:.c=.o))

GCC = gcc
INCL = -I ./incl 
RM = rm -rf
CFLAGS += -Wall -Wextra -Werror $(INCL)
FSAN = -fsanitize=address -g3
READLINE_MAC = 

.PHONY = all clean fclean re debug

$(NAME): $(OBJ)
	$(GCC) $(CFLAGS) $(OBJ) -o $(NAME)
# $(READLINE_MAC)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	@echo $(RM) *.dSYM

re: fclean all

# debug: $(OBJ)