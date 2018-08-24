/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:50:47 by rpetluk           #+#    #+#             */
/*   Updated: 2018/08/23 16:37:35 by oevtushe         ###   ########.fr       */
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
# define IDX_MOD				(MEM_SIZE / 8)
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

//////
#include "../srcs/libft/includes/libft.h"
#include "../srcs/ft_printf/includes/ft_printf.h"
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

# define CHECK_REG(type,reg) ((type) == T_REG && (reg) > 0 && (reg) <= REG_NUMBER)

typedef	struct		s_possible_args
{
	t_arg_type		one;
	t_arg_type		two;
	t_arg_type		three;
	t_arg_type		four;
}					t_possible_args;

typedef struct		s_arg
{
	int				readed;
	int				value;
	t_arg_type		type;
	char			size;
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
	int					num_player;
	int					carry;
	int					life;
	int					comand;
	int					wait;
	unsigned int		reg[REG_NUMBER + 1];
	struct s_carriage	*next;
}					t_carriage;

typedef struct		s_visual
{
	char			*op_names[16];
	t_args			args;
	unsigned char	op;
	int				pn;
}					t_visual;

typedef	struct		s_reader
{
	size_t		(*read_dir)(int *val, int pos, unsigned char *map);
	size_t		(*read_ind)(int *val, int pos, unsigned char *map);
}					t_reader;

typedef struct		s_ama_dispetcher
{
	int			(*exec_cmd)(t_carriage*, unsigned char*, t_visual*, int*);
	void		(*print_cmd)(t_carriage *carriage, t_visual *visual);
}					t_ama_dispatcher;

typedef struct 		s_player
{
	int					num_player;
	int					live;
	t_header			head;
	unsigned char		*code;
	char 				*file_name;
//	t_list				*cars;
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
	t_carriage			*cars;
	t_flags				flags;
	unsigned char		map[MEM_SIZE];
}					t_vm;

void	ft_byterev_us16(unsigned short *i);
void	ft_byterev_ui32(unsigned int *i);
void	read_args_from_map(int pc, unsigned char *map, t_args *args, t_reader reader);
size_t	read_int_from_map(int *val, int pos, unsigned char *map);
size_t	read_short_from_map(int *val, int pos, unsigned char *map);
void	init_args(t_carriage *carriage, unsigned char *map, t_args *args);
void	write_int_in_map(int *val, int pos, unsigned char *map);

int		dsp_ld(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);
int		dsp_st(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);
int		dsp_add(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);
int		dsp_sub(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);
int		dsp_and(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);
int		dsp_or(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);
int		dsp_xor(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);
int		dsp_zjmp(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);
int		dsp_ldi(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);
int		dsp_sti(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);
int		dsp_lld(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);
int		dsp_lldi(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);
int		dsp_aff(t_carriage *carriage, unsigned char *map, t_visual *visual, int *shift);

int		cmd_fork(t_carriage *father, unsigned char *map, t_carriage **root);
int		cmd_lfork(t_carriage *father, unsigned char *map, t_carriage **root);
//void	init_dsp(int (**dsp)(t_carriage*, unsigned char*, t_visual*));
void	init_dsp(t_ama_dispatcher *dsp);
int		write_in_map(unsigned char map[], t_player *player);

int play_while(t_vm *vm);
int		read_player(t_player *player, int fd);
int		read_argv(t_vm *vm, int ac, char **av);
int		count_players(t_player *player);
int		add_player(t_player **player, int n, char *file_name);
void	free_all(t_vm *vm);
void	add_car(t_carriage **cars, t_carriage *car);
int		player_create_car(t_player *players, t_carriage **cars);
//free
int		del_cars(t_carriage **cars, int num_player);
int		del_plaeyr(t_player **players, int num_player);
void					free_all(t_vm *vm);
//errors
void 	error_many_champions(t_vm *vm);
void 	error_read_file(t_vm *vm, char *file_name);
void 	error_not_validate_file(t_vm *vm, char *file_name);
void 	error_differ_prog_size(t_vm *vm, char *file_name);
void 	error_big_prog_size(t_vm * vm, char *file_name, int prog_size);
//

void	print_map(unsigned char *map, t_carriage *cars);

void	print_add(t_carriage *carriage, t_visual *visual);
void	print_st(t_carriage *carriage, t_visual *visual);
void	print_ld(t_carriage *carriage, t_visual *visual);
void	print_add(t_carriage *carriage, t_visual *visual);
void	print_sub(t_carriage *carriage, t_visual *visual);
void	print_and(t_carriage *carriage, t_visual *visual);
void	print_or(t_carriage *carriage, t_visual *visual);
void	print_xor(t_carriage *carriage, t_visual *visual);
void	print_zjmp(t_carriage *carriage, t_visual *visual);
void	print_ldi(t_carriage *carriage, t_visual *visual);
void	print_sti(t_carriage *carriage, t_visual *visual);
void	print_lld(t_carriage *carriage, t_visual *visual);
void	print_lldi(t_carriage *carriage, t_visual *visual);
void	print_aff(t_carriage *carriage, t_visual *visual);

#endif
