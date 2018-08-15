# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Corewar.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/14 19:02:12 by oevtushe          #+#    #+#              #
#    Updated: 2018/08/14 19:23:54 by oevtushe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CW_NAME				:= corewar_ours

CW_DEPS_DIR			:= includes
CW_SRCS_DIR			:= srcs
CW_OBJS_DIR			:= objs

FT_DIR				:= $(CW_SRCS_DIR)/libft
FTP_DIR				:= $(CW_SRCS_DIR)/ft_printf

include				$(FT_DIR)/Pretty.mk
include				$(FTP_DIR)/Libftp.mk
include				$(FT_DIR)/Templates.mk

CW_DEPF				:= op.h
CW_SRCF				:=  player.c	\
					   operations.c	\
					   map.c
					   #vm.c			\

CW_DEPS				:= $(CW_DEPF:%=$(CW_DEPS_DIR)/%)
CW_SRCS				:= $(CW_SRCF:%=$(CW_SRCS_DIR)/%)
CW_OBJS				:= $(CW_SRCF:%.c=$(CW_OBJS_DIR)/%.o)
CW_ALL_DEPS			:= $(FTP_ALL_DEPS) $(CW_DEPS)
CW_ALL_DEPS_DIRS	:= $(FTP_ALL_DEPS_DIRS) $(CW_DEPS_DIR)
CW_ALL_SRCS			:= $(FTP_SRCS) $(CW_SRCS)
CW_ALL_EXTRA_LIBS	:= $(FTP_NAME)
CW_ALL_OBJS_DIRS	:= $(CW_OBJS_DIR)
