/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:50:47 by rpetluk           #+#    #+#             */
/*   Updated: 2018/09/24 16:59:38 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include "../srcs/libft/includes/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# include <ncurses.h>
# include <zconf.h>
# include <pthread.h>
# include <math.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define COLOR_BORDER			30
# define COLOR1					31
# define COLOR2					32
# define COLOR3					33
# define COLOR4					34
# define COLOR5					35
# define COLOR6					36
# define COLOR7					37
# define COLOR8					38
# define COLOR9					39
# define COLOR10				40

typedef char	t_arg_type;

# define T_NONE					0
# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

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

# define CHECK_REG(t,r) ((t) == T_REG && (r) > 0 && (r) <= REG_NUMBER)
# define CH_ALL(t,v) (CHECK_REG((t),(v)) || (t) == T_DIR || (t) == T_IND)
# define EXS_DSP(x) ((x) > 0 && (x) < 17)
# define CHECK_MC(x) ((x) && (x) % MAX_CHECKS == 0)

typedef struct			s_vcars
{
	int					c_pair;
	int					stored_to;
	int					cycles;
	int					len;
	struct s_vcars		*next;
}						t_vcars;

typedef struct			s_visual
{
	WINDOW				*map;
	WINDOW				*text;
	int					pause;
	int					lim;
	pthread_t			keys_thread;
	t_vcars				*vcars;
}						t_visual;

typedef	struct			s_pargs
{
	t_arg_type			arg1;
	t_arg_type			arg2;
	t_arg_type			arg3;
	t_arg_type			arg4;
}						t_pargs;

typedef struct			s_arg
{
	int					readed;
	int					value;
	t_arg_type			type;
	char				size;
}						t_arg;

typedef struct			s_args
{
	t_arg				arg1;
	t_arg				arg2;
	t_arg				arg3;
	t_arg				arg4;

	int					shift;
	int					stored_to;
	int					valid_live;
	int					st_reg;
}						t_args;

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

typedef struct			s_carriage
{
	int					num_car;
	int					pc_prev;
	int					pc;
	int					num_player;
	int					carry;
	int					life;
	int					last_live_cn;
	int					command;
	int					wait;
	unsigned int		reg[REG_NUMBER + 1];
	struct s_carriage	*next;
}						t_carriage;

typedef	struct			s_reader
{
	size_t				(*read_dir)(int *val, int pos, unsigned char *map);
	size_t				(*read_ind)(int *val, int pos, unsigned char *map);
}						t_reader;

typedef struct			s_player
{
	int					num_player;
	int					last_live;
	int					licp;
	t_header			head;
	unsigned char		*code;
	char				*file_name;
	struct s_player		*next;
}						t_player;

typedef struct			s_flags
{
	int					v;
	unsigned			s;
	unsigned			d;
	int					n;
	int					a;
	int					visual;
	int					sound;
}						t_flags;

typedef	struct			s_op
{
	t_pargs				pargs;
	int					opc;
	int					wait;
	int					has_acb;
}						t_op;

typedef struct			s_vm
{
	t_player			*players;
	t_carriage			*cars;
	t_flags				flags;
	unsigned char		map[MEM_SIZE];
	t_op				ops[16];
	t_args				args;
	unsigned int		process_counter;
	unsigned int		game_cycle;
	unsigned int		alicp;
	int					winner;
	pthread_t			sound;
	int					sound_game_cycle;
	t_visual			*visual;
}						t_vm;

typedef struct			s_dsp
{
	int					(*exec_cmd)(t_carriage *carriage, t_vm *vm);
	void				(*print_cmd)(t_carriage *carriage, t_vm *vm);
}						t_dsp;

/*
**							Operations 'n related stuff
** -----------------------------------------------------------------------------
*/

int						dsp_ld(t_carriage *carriage, t_vm *vm);
int						dsp_st(t_carriage *carriage, t_vm *vm);
int						dsp_add(t_carriage *carriage, t_vm *vm);
int						dsp_sub(t_carriage *carriage, t_vm *vm);
int						dsp_and(t_carriage *carriage, t_vm *vm);
int						dsp_or(t_carriage *carriage, t_vm *vm);
int						dsp_xor(t_carriage *carriage, t_vm *vm);
int						dsp_zjmp(t_carriage *carriage, t_vm *vm);
int						dsp_ldi(t_carriage *carriage, t_vm *vm);
int						dsp_sti(t_carriage *carriage, t_vm *vm);
int						dsp_lld(t_carriage *carriage, t_vm *vm);
int						dsp_lldi(t_carriage *carriage, t_vm *vm);
int						dsp_aff(t_carriage *carriage, t_vm *vm);
int						dsp_fork(t_carriage *father, t_vm *vm);
int						dsp_lfork(t_carriage *father, t_vm *vm);
int						dsp_live(t_carriage *carriage, t_vm *vm);

void					ft_byterev_us16(unsigned short *i);
void					ft_byterev_ui32(unsigned int *i);
void					read_args_from_map(int pc, unsigned char *map,
							t_args *args, t_reader reader);
size_t					read_int_from_map(int *val, int pos,
							unsigned char *map);
size_t					read_short_from_map(int *val, int pos,
							unsigned char *map);
void					init_args(t_carriage *carriage,
							unsigned char *map, t_args *args);
void					write_int_in_map(int *val, int pos,
							unsigned char *map);
void					init_op_arr(t_op *op);
void					init_dsp(t_dsp *dsp);
int						write_in_map(unsigned char map[], t_player *player);
int						normalize_pc(int pc);

void					print_add(t_carriage *carriage, t_vm *vm);
void					print_st(t_carriage *carriage, t_vm *vm);
void					print_ld(t_carriage *carriage, t_vm *vm);
void					print_add(t_carriage *carriage, t_vm *vm);
void					print_sub(t_carriage *carriage, t_vm *vm);
void					print_and(t_carriage *carriage, t_vm *vm);
void					print_or(t_carriage *carriage, t_vm *vm);
void					print_xor(t_carriage *carriage, t_vm *vm);
void					print_zjmp(t_carriage *carriage, t_vm *vm);
void					print_ldi(t_carriage *carriage, t_vm *vm);
void					print_sti(t_carriage *carriage, t_vm *vm);
void					print_lld(t_carriage *carriage, t_vm *vm);
void					print_lldi(t_carriage *carriage, t_vm *vm);
void					print_aff(t_carriage *carriage, t_vm *vm);
void					print_lfork(t_carriage *carriage, t_vm *vm);
void					print_fork(t_carriage *carriage, t_vm *vm);
void					print_live(t_carriage *carriage, t_vm *vm);

void					print_pc_movement(int cur_pos, int shift,
							unsigned char *map);
void					print_pnum(int num);

/*
**								Game management
** -----------------------------------------------------------------------------
*/

void					play_while(t_vm *vm);
int						is_time_to_run(t_vm *vm, t_carriage *carriage);
void					refresh_players(t_player *players);
void					protect_visual(t_vm *vm);
int						read_header(t_player *player, int fd);
int						read_argv(t_vm *vm, int ac, char **av);
int						count_players(t_player *player);
int						add_player(t_player **player, int n, char *file_name);
void					add_car(t_carriage **cars, t_carriage *car);
int						player_create_car(t_player *players,
							t_carriage **cars);
int						validate_args(t_args *args, t_pargs *pargs);
void					del_cars(t_vm *vm, int ctd);
void					free_all(t_vm *vm);
void					error_many_champions(t_vm *vm);
void					error_read_file(t_vm *vm, char *file_name);
void					error_not_validate_file(t_vm *vm, char *file_name);
void					error_differ_prog_size(t_vm *vm, char *file_name);
void					error_big_prog_size(t_vm *vm, char *file_name,
							int prog_size);
void					print_winner(t_player *players, int winner);
void					print_map(unsigned char *map);
int						sound_kill_car(void);
void					flags_s(t_vm *vm);
void					flags_d(t_vm *vm);

/*
**								Visualization
** -----------------------------------------------------------------------------
*/

void					visual(t_vm *vm);
void					interrupt(t_vm *vm);
void					wait_end(t_vm *vm);
void					renew_ctd(t_vm *vm, unsigned int ctd);
void					renew_lives(t_vm *vm);
void					draw_line(t_vm *vm, int coord);
void					draw_empty_line(t_vm *vm, int coord);
int						put_car(t_vm *vm);
void					push_back_vcars(t_vcars **begin, int c_pair,
							int stored_to, int len);
void					del_front_vcars(t_vcars **begin);
void					del_vcars(t_vcars **begin);
void					command_processing(t_carriage *tcar,
							t_vm *vm, int len);
void					on_color_player50(int num_player, t_vm *vm);
void					off_color_player50(int num_player, t_vm *vm);
void					cycles_decrease(t_vm *vm);
void					on_color_player(int num_player, t_vm *vm);
void					off_color_player(int num_player, t_vm *vm);
int						on_color_caret(int cp, t_vm *vm);
void					off_color_caret(int cp, t_vm *vm);
void					live_processing(t_carriage *tcar, t_vm *vm,
							int len);
void					on_color_live(int cp, t_vm *vm);
void					off_color_live(int cp, t_vm *vm);
void					print_back_live(t_vm *vm);
void					vdel_car(t_vm *vm, t_carriage *tcar);
void					print_back(t_vm *vm);
void					cycle_decrease_to_end(t_vm *vm);
void					create_colors(void);
void					on_color_caret_back(int cp, t_vm *vm);
void					off_color_caret_back(int cp, t_vm *vm);
void					on_color_player_t(int num_player, t_vm *vm);
void					off_color_player_t(int num_player, t_vm *vm);
int						number_of_players(t_player *players);
int						player_num(t_player *player, t_vm *vm);
size_t					len_number(int i);
void					wprint_map(t_vm *vm);
void					wprint_text(t_vm *vm);
void					destroy_win(WINDOW *win);
void					help_print_back(t_vm *vm, int y, int x);
int						second_command(t_vm *vm);

#endif
