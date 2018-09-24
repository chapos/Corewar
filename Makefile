# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile2                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/24 08:46:02 by oevtushe          #+#    #+#              #
#    Updated: 2018/09/24 10:44:51 by oevtushe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include				Corewar.mk

RM			 		:= rm -rf
AR			 		:= ar
CC			 		:= gcc
ARFLAGS		 		:= rc
CFLAGS_COMPILE		:= -Wall -Werror -Wextra
CFLAGS_LINKAGE      := -lncurses -lpthread
MFLAGS		 		:= --no-print-directory -C

all: $(FT_NAME) $(CW_NAME) $(ASM_NAME)

$(FT_NAME):
	@$(MAKE) $(MFLAGS) $(FT_DIR)

$(ASM_NAME):
	@$(MAKE) $(MFLAGS) $(ASM_DIR)
	@mv $(ASM_DIR)/$(ASM_NAME) .

$(CW_NAME): $(CW_OBJS)
	@$(CC) $(CFLAGS_LINKAGE) -o $(CW_NAME) $^ $(FT_NAME)
	@printf "\r\033[38;5;117m✓ $(CW_NAME) created\033[0m\033[K\n"

$(CW_OBJS_DIR)/%.o: $(CW_SRCS_DIR)/%.c $(CW_DEPS)
	@printf "\033[2KCompiling: $(@)\r"
	@$(CC) $(CFLAGS_COMPILE) -o $@ -c $< $(CW_DEPS_DIR:%=-I%)

$(CW_OBJS): |$(CW_OBJS_DIR)

$(CW_OBJS_DIR):
	@mkdir $@

clean:
	@$(RM) $(CW_OBJS_DIR)
	@$(MAKE) clean $(MFLAGS) $(FT_DIR)
	@$(MAKE) clean $(MFLAGS) $(ASM_DIR)

fclean: clean
	@$(RM) $(CW_NAME)
	@$(MAKE) fclean $(MFLAGS) $(FT_DIR)
	@$(MAKE) fclean $(MFLAGS) $(ASM_DIR)
	@$(RM) $(ASM_NAME:$(ASM_DIR)/%=%)
	@printf "\r\033[38;5;196m✗ fclean $(CW_NAME)\033[0m\033[K\n"

re: fclean all

.PHONY: all clean fclean re
