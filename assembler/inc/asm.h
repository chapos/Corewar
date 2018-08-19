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
# include "../libft/includes/libft.h"
# include "op.h"

# define USAGE "Usage: ./asm <sourcefile.s>\n"
# define FILE_NAME_ERR "Wrong file format\n"
# define OPEN_SOURCE_ERR "Can't read source file "
# define OPEN_OUTPUT_ERR "Can't create or open output file "

typedef struct	s_bot t_bot;

typedef struct	s_db
{
	t_bot		bot;
	int			output_fd;
	int 		source_fd;
}				t_db;

struct	s_bot
{
	char 		*bot_name;
	char 		*bot_comment;
	uint32_t	bot_size;
};

void			read_source_file(t_db *db);

#endif
