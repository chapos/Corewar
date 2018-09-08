/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:33:26 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/07 18:50:16 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};
*/

/*
** 01 ff ff ff ff
*/

/*
** Treat them like exceptions
int		dsp_live(t_carriage *carriage, unsigned char *map, t_op *op_tab)
{
	unsigned int arg;

	arg = *((unsigned int *)&map[carriage->pc]);
}

int		dsp_fork(t_carriage *carriage, unsigned char *map, t_op *op_tab)
{
}
*/

void	print_regs(unsigned int *reg)
{
	int i;

	i = 1;
	while (i < REG_NUMBER)
		printf("%.8X ", reg[i++]);
	printf("%.8X\n", reg[i]);
}

static void	init_dsps(t_dsp *dsp)
{
	dsp[0].exec_cmd = dsp_live;
	dsp[1].exec_cmd = dsp_ld;
	dsp[2].exec_cmd = dsp_st;
	dsp[3].exec_cmd = dsp_add;
	dsp[4].exec_cmd = dsp_sub;
	dsp[5].exec_cmd = dsp_and;
	dsp[6].exec_cmd = dsp_or;
	dsp[7].exec_cmd = dsp_xor;
	dsp[8].exec_cmd = dsp_zjmp;
	dsp[9].exec_cmd = dsp_ldi;
	dsp[10].exec_cmd = dsp_sti;
	dsp[11].exec_cmd = dsp_fork;
	dsp[12].exec_cmd = dsp_lld;
	dsp[13].exec_cmd = dsp_lldi;
	dsp[14].exec_cmd = dsp_lfork;
	dsp[15].exec_cmd = dsp_aff;
}

static void init_prints(t_dsp *dsp)
{
	dsp[0].print_cmd = print_live;
	dsp[1].print_cmd = print_ld;
	dsp[2].print_cmd = print_st;
	dsp[3].print_cmd = print_add;
	dsp[4].print_cmd = print_sub;
	dsp[5].print_cmd = print_and;
	dsp[6].print_cmd = print_or;
	dsp[7].print_cmd = print_xor;
	dsp[8].print_cmd = print_zjmp;
	dsp[9].print_cmd = print_ldi;
	dsp[10].print_cmd = print_sti;
	dsp[11].print_cmd = print_fork;
	dsp[12].print_cmd = print_lld;
	dsp[13].print_cmd = print_lldi;
	dsp[14].print_cmd = print_lfork;
	dsp[15].print_cmd = print_aff;
}

void	init_dsp(t_dsp *dsp)
{
	init_dsps(dsp);
	init_prints(dsp);
}
