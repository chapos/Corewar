/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 12:45:55 by rpetluk           #+#    #+#             */
/*   Updated: 2018/09/24 16:58:59 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int		sound_kill_car(void)
{
	if (system("afplay dindon2.mp3"))
		exit(100);
	return (0);
}

void	flags_s(t_vm *vm)
{
	char	c;

	if (vm->game_cycle % vm->flags.s == 0)
	{
		print_map(vm->map);
		read(1, &c, 1);
	}
}

void	flags_d(t_vm *vm)
{
	if (vm->flags.d == vm->game_cycle)
	{
		print_map(vm->map);
		free_all(vm);
	}
}

void	init_op_arr(t_op *op)
{
	op[0] = (t_op){{T_DIR, 0, 0, 0}, 1, 10, 1};
	op[1] = (t_op){{T_DIR | T_IND, T_REG, 0, 0}, 2, 5, 1};
	op[2] = (t_op){{T_REG, T_IND | T_REG, 0, 0}, 3, 5, 1};
	op[3] = (t_op){{T_REG, T_REG, T_REG, 0}, 4, 10, 1};
	op[4] = (t_op){{T_REG, T_REG, T_REG, 0}, 5, 10, 1};
	op[5] = (t_op){{T_REG | T_DIR | T_IND,
					T_REG | T_IND | T_DIR, T_REG, 0}, 6, 6, 1};
	op[6] = (t_op){{T_REG | T_IND | T_DIR,
					T_REG | T_IND | T_DIR, T_REG, 0}, 7, 6, 1};
	op[7] = (t_op){{T_REG | T_IND | T_DIR,
					T_REG | T_IND | T_DIR, T_REG, 0}, 8, 6, 1};
	op[8] = (t_op){{T_DIR, 0, 0, 0}, 9, 20, 0};
	op[9] = (t_op){{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG, 0}, 10, 25, 1};
	op[10] = (t_op){{T_REG, T_REG | T_DIR | T_IND,
					T_DIR | T_REG, 0}, 11, 25, 1};
	op[11] = (t_op){{T_DIR, 0, 0, 0}, 12, 800, 0};
	op[12] = (t_op){{T_DIR | T_IND, T_REG, 0, 0}, 13, 10, 1};
	op[13] = (t_op){{T_REG | T_DIR | T_IND, T_DIR | T_REG,
					T_REG, 0}, 14, 50, 1};
	op[14] = (t_op){{T_DIR, 0, 0, 0}, 15, 1000, 0};
	op[15] = (t_op){{T_REG, 0, 0, 0}, 16, 2, 1};
}
