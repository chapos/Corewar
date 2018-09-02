CC = gcc
ASM = asm
FLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libft/
INC_DIR = ./inc/
SRC_DIR = ./src/
LIBFT = $(LIBFT_DIR)libft.a
SRC = $(addprefix $(SRC_DIR), asm_helpers.c asm_main.c name_comment_helpers.c read_name_and_comment.c read_source_file.c instructions_validation.c label_handling.c)
OBJ = $(SRC:.c=.o)
INC = $(INC_DIR)asm.h

.PHONY: all clean fclean re

all: $(ASM)

%.o: $(SRC)%.c
	@$(CC) $(FLAGS) -I=$(INC_DIR) $< -o $@

$(ASM): $(OBJ) $(LIBFT) $(INC)
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
	@printf "\r\033[38;5;196m✗ fclean $(ASM) libft.a\033[0m\033[K\n"

re: fclean all
