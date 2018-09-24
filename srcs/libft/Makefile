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
	@printf "\033[2KCompiling: $(@)\r"
	@$(CC) -I=$(INC_DIR) $(FLAGS) $< -o $@

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
