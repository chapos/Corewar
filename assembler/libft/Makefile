NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror -c
INC_DIR = ./includes/
SRC_DIR = ./src/
OBJ_DIR = ./obj/
FIND_SRC_FILES = $(shell find ./src -type f | grep -E "\.c$$")
FIND_SRC_SUBDIRS = $(shell find ./src -type d -mindepth 1)
SRC_SUBDIRS = $(FIND_SRC_SUBDIRS:$(SRC_DIR)%=%)
SRC = $(FIND_SRC_FILES:$(SRC_DIR)%=%)
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@mkdir $(addprefix $(OBJ_DIR), $(SRC_SUBDIRS))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -I=$(INC_DIR) $(FLAGS) $< -o $@

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\r\033[38;5;117m✓ $(NAME) created\033[0m\033[K\n"

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@printf "\r\033[38;5;202m✗ clean binaries\033[0m\033[K\n"

fclean: clean
	@rm -f $(NAME)
	@printf "\r\033[38;5;196m✗ fclean $(NAME)\033[0m\033[K\n"

re: fclean all
