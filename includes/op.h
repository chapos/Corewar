/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:50:47 by rpetluk           #+#    #+#             */
/*   Updated: 2018/08/15 11:26:29 by oevtushe         ###   ########.fr       */
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
# define MEM_SIZE				21//(4*1024)
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

#include "libft.h"
#include "ft_printf.h"

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

/*
** 0xc0 -> 11 00 00 00
** 0x30 -> 00 11 00 00
** 0x0c -> 00 00 11 00
** 0x03 -> 00 00 00 11
*/

# define ARG_MASK1			0xC0
# define ARG_MASK2			0x30
# define ARG_MASK3			0x0C
# define ARG_MASK4			0x03

typedef	struct		s_possible_args
{
	t_arg_type		one;
	t_arg_type		two;
	t_arg_type		three;
	t_arg_type		four;
}					t_possible_args;

typedef struct		s_arg
{
	int				value;
	t_arg_type		type;
	unsigned char	size;
}					t_arg;

typedef struct		s_args
{
	t_arg		arg1;
	t_arg		arg2;
	t_arg		arg3;
	t_arg		arg4;
}					t_args;

typedef	struct		s_op
{
	char			*name;
	int				argc;
	t_possible_args	args;
	int				opc;
	int				cycle;
	char			*descr;
	int				acb;
	int				idk;
}					t_op;

typedef struct		s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_carriage
{
	int					pc;
	int					carry;

	int					life;
	int					comand;
	int					wait;
	int					reg[REG_NUMBER];
}					t_carriage;

typedef struct 		s_player
{
	int					num_player;
	t_header			head;
	unsigned char		*code;
//	t_list				*car;
}						t_player;

//typedef struct		s_vm
//{
//	t_list				*players;
//	unsigned char		map[MEM_SIZE];
//}					t_vm;

int		write_in_map(unsigned char map[], t_list *players);
//int		read_player(t_player *players);
int read_players(t_list **players, int ac, char **av);

#endif
