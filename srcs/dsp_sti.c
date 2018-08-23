/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsp_sti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 12:46:11 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/23 15:32:42 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	print_sti(t_carriage *carriage, t_visual *visual)
{
	ft_printf("%s r%hhu %d %d\n", visual->op_names[visual->op - 1], (unsigned char)visual->args.arg1.readed, visual->args.arg2.value, visual->args.arg3.value);
	ft_printf("-> store to %d + %d = %d (with pc and mod %d)\n",
			visual->args.arg2.value, visual->args.arg3.value,
			visual->args.arg2.value + visual->args.arg3.value,
			carriage->pc);
}

int		dsp_sti(t_carriage *carriage, unsigned char *map, t_visual *visual)
{
	unsigned char	acb;
	int				res;
	t_args			args;
	int				addr;
	int				rev;

	res = 0;
	visual->op = map[carriage->pc];
	acb = map[(carriage->pc + 1) % MEM_SIZE];
	ft_memset(&args, 0, sizeof(t_args));
	if ((acb & ARG_MASK1) || (acb & ARG_MASK2) || (acb & ARG_MASK3))
	{
		read_args_from_map(carriage->pc, map, &args, (t_reader){read_short_from_map, read_short_from_map});
		if (CHECK_REG(args.arg1.type, args.arg1.readed) && (acb & ARG_MASK2) &&
				(args.arg3.type == T_DIR || CHECK_REG(args.arg3.type, args.arg3.readed)))
		{
			init_args(carriage, map, &args);
			addr = args.arg2.value + args.arg3.value;
			rev = args.arg1.value;
			ft_byterev_ui32((unsigned int *)&rev);
			write_int_in_map(&rev, carriage->pc + addr, map);
			res = 1;
		}
		visual->args = args;
		carriage->pc += 1 + args.arg1.size + args.arg2.size + args.arg3.size;
	}
	++carriage->pc;
	carriage->pc %= MEM_SIZE;
	return (res);
}
