# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/14 11:48:34 by rpetluk           #+#    #+#              #
#    Updated: 2018/08/19 15:41:53 by oevtushe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include			Corewar.mk

CFLAGS			+= -g

all: $(CW_NAME)

$(eval $(call BINARY_template2,CW,FTP))
$(eval $(call BASIC_template,CW))
$(eval $(call EXTRALIB_template2,FTP,libftp,all))

clean:
	@$(RM) $(CW_OBJS_DIR)
	@$(MAKE) clean $(MFLAGS) $(FTP_DIR)

fclean: clean
	@$(RM) $(CW_NAME)
	@$(MAKE) fclean $(MFLAGS) $(FTP_DIR)
