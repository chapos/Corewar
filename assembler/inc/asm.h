/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 15:04:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/08/18 15:04:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"
# include "op.h"

# define USAGE "Usage: ./asm <sourcefile.s>\n"
# define FILE_NAME_ERR "Wrong file format\n"
# define OPEN_SOURCE_ERR "Can't open source file "
# define OPEN_OUTPUT_ERR "Can't create or open output file "

typedef struct	s_bot
{
	char 			*bot_name;
	char 			*bot_comment;
	uint32_t		bot_size;
	char 			buff[COMMENT_LENGTH];
	uint32_t 		separator;
	uint32_t		magic_header;
}					t_bot;

typedef struct		s_validation
{
	size_t			line_counter;
	bool			name_readed;
	bool			comment_readed;
	bool			multiline_string;
	size_t			name_size;
	size_t			comment_size;
	char 			*line;
}					t_validation;

typedef struct		s_db
{
	t_bot			bot;
	t_validation	v_data;
	int				output_fd;
	int 			source_fd;
}					t_db;

void				read_source_file(t_db *db);
void 				read_name_and_comment(t_db *db);
void				clean_and_exit(t_db *db, const char *log);
void				read_multiline_string(t_db *db, bool is_name);
uint32_t			big_little_endian(uint32_t n);

#endif

