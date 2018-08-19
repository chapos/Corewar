/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:33:26 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/19 14:30:02 by oevtushe         ###   ########.fr       */
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

void	print_map(unsigned char *map, const int map_size)
{
	int		i;

	i = 0;
	while (i < map_size)
	{
		ft_printf("%.2x ", map[i]);
		if (i && i % 64 == 0)
			ft_putchar('\n');
		++i;
	}
	if (i % 64)
		ft_putchar('\n');
}

void	print_regs(unsigned int *reg)
{
	int i;

	i = 1;
	while (i < REG_NUMBER)
		ft_printf("%.8X ", reg[i++]);
	ft_printf("%.8X\n", reg[i]);
}

void	init_dsp(int (**dsp)(t_carriage*, unsigned char*))
{
	dsp[0] = NULL;
	dsp[1] = dsp_ld;
	dsp[2] = dsp_st;
	dsp[3] = dsp_add;
	dsp[4] = dsp_sub;
	dsp[5] = dsp_and;
	dsp[6] = dsp_or;
	dsp[7] = dsp_xor;
	dsp[8] = dsp_zjmp;
	dsp[9] = dsp_ldi;
	dsp[10] = dsp_sti;
	dsp[11] = NULL;
	dsp[12] = dsp_lld;
	dsp[13] = dsp_lldi;
	dsp[14] = NULL;
	dsp[15] = dsp_aff;
}

int		main(void)
{
	t_carriage		carriage;
	const int		map_size = 21;
	unsigned char	map[map_size];
	int				(*dsp[16])(t_carriage*, unsigned char*);

	init_dsp(dsp);
	ft_memset(&carriage, 0, sizeof(t_carriage));
	ft_memset(map, 0, map_size);
	carriage.reg[1] = 0xffffffff;
	map[0] = 0x03;
	map[1] = 0x70;
	map[2] = 0x01;
	map[3] = 0x00;
	map[4] = 0x05;
	dsp[map[0] - 1](&carriage, map);
	print_map(map, map_size);
	return (0);
}
