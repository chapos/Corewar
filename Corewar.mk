# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Corewar.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/14 19:02:12 by oevtushe          #+#    #+#              #
#    Updated: 2018/09/24 09:47:45 by oevtushe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CW_NAME				:= corewar

CW_DEPF				:= op.h
CW_SRCF				:= player.c						\
					   init_dsp.c					\
					   ft_byterev_us16.c			\
					   ft_byterev_ui32.c			\
					   read_data_from_map.c			\
					   init_args.c					\
					   write_int_in_map.c			\
					   dsp_ld.c						\
					   dsp_lld.c					\
					   dsp_st.c						\
					   dsp_and.c					\
					   dsp_sub.c					\
					   dsp_add.c					\
					   dsp_or.c						\
					   dsp_xor.c					\
					   dsp_zjmp.c					\
					   dsp_ldi.c					\
					   dsp_lldi.c					\
					   dsp_sti.c					\
					   dsp_aff.c					\
					   dsp_fork.c					\
					   dsp_lfork.c					\
					   dsp_live.c           		\
					   map.c						\
					   flag.c      					\
					   vm.c							\
					   errors.c    					\
					   carriage.c           		\
					   corewar_lib.c        		\
					   normalize_pc.c				\
					   print_pc_movement.c			\
					   print_pnum.c					\
					   play_while.c         		\
					   validate_args.c				\
					   print.c              		\
					   visual.c             		\
					   bonus_func.c         		\
					   visual_list.c        		\
					   command_processing.c 		\
					   live_processing.c    		\
					   colors.c             		\
					   vdraw_line.c         		\
					   color_caret.c        		\
					   color_live.c         		\
					   color_player.c       		\
					   vinterrupt.c         		\
					   vplayer_num.c        		\
					   vprint_map.c         		\
					   vprint_text.c        		\
					   vput_cars.c          		\
					   command_processing_help.c

CW_DEPS_DIR			:= includes
CW_SRCS_DIR			:= srcs
CW_OBJS_DIR			:= objs
CW_DEPS				:= $(CW_DEPF:%=$(CW_DEPS_DIR)/%)
CW_SRCS				:= $(CW_SRCF:%=$(CW_SRCS_DIR)/%)
CW_OBJS				:= $(CW_SRCF:%.c=$(CW_OBJS_DIR)/%.o)

FT_DIR				:= $(CW_SRCS_DIR)/libft
FT_NAME				:= $(FT_DIR)/libft.a

ASM_DIR				:= assembler
ASM_NAME			:= asm
