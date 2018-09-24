# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/24 09:25:15 by oevtushe          #+#    #+#              #
#    Updated: 2018/09/24 10:52:55 by oevtushe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
ASM := asm
FLAGS := -Wall -Wextra -Werror
LIBFT_DIR := ../srcs/libft/
INC_DIR := ./inc/
SRC_DIR := ./src/
LIBFT := $(LIBFT_DIR)libft.a
SRC := $(addprefix $(SRC_DIR), asm_helpers.c asm_main.c name_comment_helpers.c read_name_and_comment.c read_source_file.c instructions_validation.c label_handling.c arguments_handlers.c writing_result.c instructions_validation_ext1.c instructions_validation_ext2.c instructions_validation_ext3.c arithmetic_handling.c)
OBJ := $(SRC:.c=.o)
INC := $(INC_DIR)asm.h

.PHONY: all clean fclean re

all: $(ASM)

%.o: %.c $(INC)
	@printf "\033[2KCompiling: $(@)\r"
	@$(CC) $(FLAGS) -c $< -o $@

$(ASM): $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) -I$(INC_DIR) $(OBJ) -o $(ASM) -L$(LIBFT_DIR) -lft
	@printf "\r\033[38;5;117m✓ $(ASM) created\033[0m\033[K\n"

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(ASM)
	@rm -f $(LIBFT)
	@printf "\r\033[38;5;196m✗ fclean $(ASM) \033[0m\033[K\n"

re: fclean all
