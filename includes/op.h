/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:50:47 by rpetluk           #+#    #+#             */
/*   Updated: 2018/08/14 12:52:04 by rpetluk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_COREWAR_H
# define COREWAR_COREWAR_H

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER			4
# define MAX_PLAYERS				4
# define MEM_SIZE				(4*1024)
# define IDX_MOD					(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR				'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING			".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA				50
# define NBR_LIVE				21
# define MAX_CHECKS				10

#include "../srcs/libft/includes/libft.h"
#include "../srcs/ft_printf/includes/ft_printf.h"


//////
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
//////

/*
**
*/

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_carriage
{
	int					position;
	int					carry;
	int					num_gamer;

	int					life;
	int					comand;
	int					wait;
	struct s_carriage	*next;
}					t_carriage;

typedef struct 		s_player
{
	int					num_player;
	t_header			head;
	unsigned char		*code;
	char 				*file_name;
//	t_list				*car;
	struct s_player		*next;
}						t_player;

typedef struct		s_flags
{
	int					v;
	int					s;
	int					d;
	int					n;
}					t_flags;

typedef struct		s_vm
{
	t_player			*players;
	t_flags				flags;
	unsigned char		map[MEM_SIZE];
}					t_vm;


int		write_in_map(unsigned char map[], t_player *player);

int						read_player(t_player *player, int fd);
int						read_arg(t_vm *vm, int ac, char **av);
int						count_players(t_player *player);
int						add_player(t_player **player, int n, char *file_name);

void					free_all(t_vm *vm);
//errors
void error_many_champions(t_vm *vm);
void error_read_file(t_vm *vm, char *file_name);
void error_not_validate_file(t_vm *vm, char *file_name);
void error_differ_prog_size(t_vm *vm, char *file_name);
void error_big_prog_size(t_vm * vm, char *file_name, int prog_size);
//



#endif
