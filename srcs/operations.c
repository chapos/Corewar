/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 19:04:52 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/15 19:34:19 by oevtushe         ###   ########.fr       */
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

void	ft_byterev_s16(short *i)
{
	*i = (*i >> 8 & 0xff) |
		(*i << 8 & 0xff00);
}

void	ft_byterev_i32(int *i)
{
	*i = (*i >> 24 & 0xff) |
		(*i << 8 & 0xff0000) |
		(*i >> 8 & 0xff00) |
		(*i << 24 & 0xff000000);
}

int		read_arg(int pc, unsigned char *map, unsigned int acb_mask, int *shift, t_arg *arg)
{
	int		res;

	res = 0;
	// Direct
	if (acb_mask == 0x80)
	{
		arg->value = *(int *)&map[pc + *shift + 1];
		ft_byterev_i32(&arg->value);
		arg->type = T_DIR;
		arg->size = DIR_SIZE;
		*shift += sizeof(int);
	}
	// Register
	else if (acb_mask == 0x40)
	{
		arg->value = map[pc + *shift + 1];
		arg->type = T_REG;
		arg->size = 1;
		*shift += sizeof(unsigned char);
	}
	// Indirect
	else if (acb_mask == 0xc0)
	{
		arg->value = *(short *)&map[pc + *shift + 1];
		ft_byterev_s16((short *)&arg->value);
		arg->type = T_IND;
		arg->size = IND_SIZE;
		*shift += sizeof(short);
	}
	return (res);
}

void	parse_args(int pc, unsigned char *map, t_args *args)
{
	unsigned char	acb;
	int				shift;

	shift = 1;
	acb = map[pc + 1];
	read_arg(pc, map, acb & ARG_MASK1, &shift, &args->arg1);
	read_arg(pc, map, (acb & ARG_MASK2) << 2, &shift, &args->arg2);
	read_arg(pc, map, (acb & ARG_MASK3) << 4, &shift, &args->arg3);
	read_arg(pc, map, (acb & ARG_MASK4) << 6, &shift, &args->arg4);
}

void	read_int_from_map(int *val, int pos, unsigned char *map)
{
	unsigned char	*p;

	if (pos < 0)
		pos = MEM_SIZE + pos;
	pos %= MEM_SIZE;
	p = (unsigned char *)val;
	if ((pos + sizeof(int) <= MEM_SIZE))
		ft_memcpy(val, &map[pos], sizeof(int));
	else
	{
		ft_memcpy(p, &map[pos], MEM_SIZE - pos);
		p += MEM_SIZE - pos;
		ft_memcpy(p, map, sizeof(int) - (MEM_SIZE - pos));
	}
}

/*
** Modifies carry
** Has ACB
*/

int		dsp_ld(t_carriage *carriage, unsigned char *map)
{
	unsigned char	acb;
	t_args			args;
	int				res;

	res = 0;
	acb = map[carriage->pc + 1];
	ft_memset(&args, 0, sizeof(t_args));
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2))
	{
		parse_args(carriage->pc, map, &args);
		if (args.arg2.type == T_REG)
		{
			if (args.arg1.type == T_DIR)
			{
				carriage->reg[args.arg2.value] = args.arg1.value;
				carriage->carry = args.arg1.value == 0 ? 1 : 0;
				res = 1;
			}
			else if (args.arg1.type == T_IND)
			{
				args.arg1.value %= IDX_MOD;
				read_int_from_map(&args.arg1.value, carriage->pc + args.arg1.value, map);
				ft_byterev_i32(&args.arg1.value);
				carriage->carry = args.arg1.value == 0 ? 1 : 0;
				res = 1;
			}
		}
		carriage->pc += args.arg1.size + args.arg2.size + 1;
	}
	++carriage->pc;
	carriage->pc %= MEM_SIZE;
	return (res);
}

// (args.arg1.value > 0 && args.arg1.value <= REG_NUMBER) -> may be # define

/*
** Function writes int in map. Possible memory circles considered, negative
** numbers too.
*/

void	write_int_in_map(int *val, int pos, unsigned char *map)
{
	unsigned char	*p;

	if (pos < 0)
		pos = MEM_SIZE + pos;
	pos %= MEM_SIZE;
	p = (unsigned char *)val;
	if ((pos + sizeof(int) <= MEM_SIZE))
		ft_memcpy(&map[pos], val, sizeof(int));
	else
	{
		ft_memcpy(&map[pos], p, MEM_SIZE - pos);
		p += MEM_SIZE - pos;
		ft_memcpy(map, p, sizeof(int) - (MEM_SIZE - pos));
	}
}

int		dsp_st(t_carriage *carriage, unsigned char *map)
{
	unsigned char	acb;
	int				res;
	t_args			args;
	int				rev;

	res = 0;
	acb = map[carriage->pc + 1];
	ft_memset(&args, 0, sizeof(t_args));
	if ((acb & ARG_MASK1) && (acb & ARG_MASK2))
	{
		parse_args(carriage->pc, map, &args);
		// Even if first argument is invalid
		if (args.arg1.type == T_REG || args.arg2.type == T_IND || args.arg2.type == T_REG)
		{
			if (args.arg1.type == T_REG && (args.arg1.value > 0 && args.arg1.value <= REG_NUMBER))
			{
				if (args.arg2.type == T_REG && (args.arg1.value > 0 && args.arg1.value <= REG_NUMBER))
					carriage->reg[args.arg2.value] = carriage->reg[args.arg1.value];
				else if (args.arg2.type == T_IND)
				{
					args.arg2.value %= IDX_MOD;
					rev = carriage->reg[args.arg1.value];
					ft_byterev_i32(&rev);
					write_int_in_map(&rev, carriage->pc + args.arg2.value, map);
				}
				res = 1;
			}
			carriage->pc += 1 + args.arg1.size + args.arg2.size;
		}
	}
	++carriage->pc;
	carriage->pc %= MEM_SIZE;
	return (res);
}

int		main(void)
{
	t_carriage		carriage;
	const int		map_size = 21;
	unsigned char	map[map_size];

	ft_memset(map, 0, map_size);
	carriage.pc = 0;
	map[0] = 2;
	map[1] = 0xD0;
	map[2] = 0xff;
	map[3] = 0xfd;
	map[4] = 0x02;
	map[5] = 0x00;
	//
	map[7] = 3;
	map[8] = 0x70;
	map[9] = 0x2;
	map[10] = 0xff;
	map[11] = 0xf8;
	map[17] = 0x7f;
	map[18] = 0xff;
	map[19] = 0xff;
	map[20] = 0xff;

	dsp_ld(&carriage, map);
	dsp_st(&carriage, map);
	return (0);
}
