# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Templates.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sasha <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/05 12:30:58 by sasha             #+#    #+#              #
#    Updated: 2018/08/14 12:53:29 by rpetluk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Templates for basic project compilation
#
# Templates description:
#
# 	BASIC		->	objects dir creation and
# 					objects compilation with
# 					pretty output
#	
#	EXTRALIB	->	Calls for other makefile to compile
#					additional library
#
#	LIB			->	Make a lib from objects
#
#	BINARY		->	Make a binary file from objects and libs
#
#
# Variables that has to be defined before using templates:
#
# 	* <PFX>_NAME			->	a name of binary/library
# 	* <PFX>_SRCS			->	sorces for current project
# 	* <PFX>_OBJS			->	object files for current project
# 	* <PFX>_DEPS			->	*.h files for current project
# 	* <PFX>_DEPS_DIR		->	dir where *.h located
# 	* <PFX>_OBJS_DIR		->	dir with objs files
# 	* <PFX>_SRCS_DIR		->	dir with srcs files
# 	* <PFX>_ALL_DEPS		->	all *.h files needed
# 								for current project
# 	* <PFX>_ALL_OBJS_DIRS	->	all objs dirs for current
# 								project
# 	* <PFX>_ALL_DEPS_DIRS	->	all deps dirs that will
# 								be created
# 	* <PFX>_ALL_SRCS		->	all srcs needed for
# 								current project
# 	* <PFX>_ALL_EXTRA_LIBS	->	all additional librarys (names)
# 								needed for this project
# 	* ALL_OBJS_DIRS ..
#
# <PFX> - stands for 'prefix'.
#
# Concise advantages and disadvantages of *_template1 and *_template2:
#
# 	*_template1	->	recompile modified files when one of *.c *.h *.o files was
# 					changed. If changed file is one from the sub-level library
# 					(current lib depends on) than nothing will be recompiled.
# 					So it useful only for root librarys.
#
# 	*_template2	->	recompile modified files when one of *.c *.h files was changed.
# 					Also recompiles project if sub-level library files was changed.
# 					But absence of/modifying *.o files won't be a reason for recompiling.
#
# NOTICE:	use only templates with the same number in the end, so that if you use
# 			BINARY_template1 and want to use EXTRALIB_template you have to choose
# 			EXTRALIB_template1, etc..

RM			 		:= rm -rf
AR			 		:= ar
CC			 		:= gcc
ARFLAGS		 		:= rc
CFLAGS_COMPILE		:= -Wall -Werror -Wextra
CFLAGS_LINKAGE      := $CFLAGS_COMPILE
MFLAGS		 		:= --no-print-directory -C

define BINARY_template1
$$($(1)_NAME): $$($(1)_ALL_OBJS)
	@$$(call EXEC_P,$$@)
	@$$(CC) $$(CFLAGS_LINKAGE) -o $$($(1)_NAME) $$^ $$($(2)_NAME)
endef

define BINARY_template2
$$($(1)_NAME): $$($(1)_ALL_EXTRA_LIBS) $$($(1)_OBJS)
	@$$(call EXEC_P,$$@)
	@$$(CC) $$(CFLAGS_LINKAGE) -o $$($(1)_NAME) $$^ $$($(2)_NAME)
endef

define BASIC_template
ifeq ($$(MAKELEVEL),0)
WCOMPILE_P = @$(call COMPILE_P,$$@)
WDIR_CREATE_P = @$(call DIR_CREATE_P,$$@)
else
WCOMPILE_P = @$(call COMPILE_P,$$(@:%=$$(RPTH)/%))
WDIR_CREATE_P = @$(call DIR_CREATE_P,$$($(1)_OBJS_DIR:$$($(1)_DIR)/%=$$(RPTH)/%))
endif

$$($(1)_OBJS_DIR)/%.o: $$($(1)_SRCS_DIR)/%.c $$($(1)_ALL_DEPS)
	$$(WCOMPILE_P)
	@$(CC) $(CFLAGS_COMPILE) -o $$@ -c $$< $$($(1)_ALL_DEPS_DIRS:%=-I%)
$$($(1)_OBJS): |$$($(1)_ALL_OBJS_DIRS)

$$($(1)_ALL_OBJS_DIRS):
	$$(WDIR_CREATE_P)
	@mkdir $$@

re: fclean all

.PHONY: all clean fclean re obj
endef

define EXTRALIB_template1
$$($(1)_OBJS_DIR)/%.o: $$($(1)_SRCS_DIR)/%.c $$($(1)_DEPS)
	@$$(MAKE) $(3) RPTH=$$($(1)_DIR) $$(MFLAGS) $$($(1)_DIR)
endef

define EXTRALIB_template2
$$($(1)_NAME): $$($(1)_ALL_SRCS) $$($(1)_ALL_DEPS)
	@$$(MAKE) $(3) RPTH=$$($(1)_DIR) $$(MFLAGS) $$($(1)_DIR)
endef

define LIB_template
$$($(1)_NAME): $$($(1)_ALL_OBJS)
	@$$(call MKLIB_P,$(2))
	@$$(AR) $$(ARFLAGS) $$($(1)_NAME) $$?
	@ranlib $$($(1)_NAME)
	@$$(call DONE_P)
endef
