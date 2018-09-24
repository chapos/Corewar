/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 15:04:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/24 09:40:13 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "../../srcs/libft/includes/libft.h"

# define USAGE "Usage: ./asm <sourcefile.s>\n"
# define FILE_NAME_ERR "Wrong file format\n"
# define OPEN_SOURCE_ERR "Can't open source file "
# define OPEN_OUTPUT_ERR "Can't create or open output file "
# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

typedef enum		e_instruction
{
	e_live = 1,
	e_ld = 2,
	e_st = 3,
	e_add = 4,
	e_sub = 5,
	e_and = 6,
	e_or = 7,
	e_xor = 8,
	e_zjmp = 9,
	e_ldi = 10,
	e_sti = 11,
	e_fork = 12,
	e_lld = 13,
	e_lldi = 14,
	e_lfork = 15,
	e_aff = 16,
	not_instruction = 17
}					t_instruction;

typedef enum		e_argument
{
	e_register = 1,
	e_direct = 2,
	e_undirect = 3
}					t_argument;

typedef struct		s_op
{
	int				value;
	char			op;
}					t_expr;

typedef struct		s_argument_data
{
	t_argument		type;
	uint32_t		value;
	bool			lable;
	char			*label_name;
	t_expr			expr;
	bool			end_mark;
}					t_argument_data;

typedef struct		s_instruction_data
{
	t_instruction	type;
	t_argument_data	args[4];
	size_t			arguments_count;
	size_t			instruction_size;
	uint8_t			codage;
}					t_instr_data;

typedef struct		s_label
{
	char			*name;
	uint32_t		bytes_position;
}					t_label;

typedef struct		s_bot
{
	char			*bot_name;
	char			*bot_comment;
	uint32_t		bot_size;
	char			buff[COMMENT_LENGTH];
	uint32_t		separator;
	uint32_t		magic_header;
	t_instr_data	*instructions;
}					t_bot;

typedef struct		s_validation
{
	size_t			line_counter;
	bool			name_readed;
	bool			comment_readed;
	bool			multiline_string;
	size_t			name_size;
	size_t			comment_size;
	char			*line;
	int				chars_counter;
}					t_validation;

typedef struct		s_db
{
	t_bot			bot;
	t_validation	v_data;
	int				output_fd;
	int				source_fd;
	t_label			*labels;
	size_t			labels_counter;
	size_t			inst_counter;
	bool			arithmetic;
}					t_db;

void				read_source_file(t_db *db);
void				read_name_and_comment(t_db *db);
void				clean_and_exit(t_db *db, const char *log);
void				read_multiline_string(t_db *db, bool is_name);
uint32_t			big_little_endian(uint32_t n, bool four_bytes);
t_instruction		get_instruction(const char *line);
size_t				validate_and_save_lable(t_db *db);
void				handle_live_instruction(t_db *db, const char *instruction);
void				handle_ld_lld_instruction(t_db *db,
						const char *inst, t_instruction type);
void				handle_st_instruction(t_db *db, const char *inst);
void				handle_add_instruction(t_db *db, const char *inst);
void				handle_sub_instruction(t_db *db, const char *inst);
void				handle_and_or_xor_instruction(t_db *db,
						const char *inst, t_instruction type);
void				handle_zjmp_instruction(t_db *db, const char *inst);
void				handle_ldi_lldi_instruction(t_db *db,
						const char *inst, t_instruction type);
void				handle_sti_instruction(t_db *db, const char *inst);
void				handle_fork_lfork_instruction(t_db *db,
						const char *inst, t_instruction type);
void				handle_aff_instruction(t_db *db, const char *inst);
size_t				handle_direct_argument(t_db *db,
		const char *instruction, int a_n);
size_t				handle_indirect_argument(t_db *db,
		const char *inst, int a_n);
size_t				handle_register_argument(t_db *db,
		const char *inst, int a_n);
size_t				calc_codage_and_instruction_size(t_db *db);
void				allocate_new_instruction(t_db *db);
size_t				get_direct_arg_size_by_name(t_instruction name);
void				set_labels_to_instructions(t_db *db);
uint32_t			calculate_label_position(t_db *db, size_t i, size_t j);
void				write_result(t_db *db, char *file_name);
const char			*skip_whitespaces(const char *line);
void				validate_and_save_instruction_ext(t_db *db,
		char *instruction);
size_t				handle_expression(t_db *db,
		const char *inst, size_t l, int a_n);
void				do_calculation(t_db *db);
void				jesus_save_me(t_db *db, const char *inst, int a_n);

#endif
