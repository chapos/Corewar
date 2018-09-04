/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:22:51 by rpetluk           #+#    #+#             */
/*   Updated: 2018/09/04 09:47:10 by rpetluk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	init_op_arr(t_op *op)
{
	op[0] = (t_op){{T_DIR, 0, 0, 0}, 1, 10, 1};
	op[1] = (t_op){{T_DIR | T_IND, T_REG, 0, 0}, 2, 5, 1};
	op[2] = (t_op){{T_REG, T_IND | T_REG, 0, 0}, 3, 5, 1};
	op[3] = (t_op){{T_REG, T_REG, T_REG, 0}, 4, 10, 1};
	op[4] = (t_op){{T_REG, T_REG, T_REG, 0}, 5, 10, 1};
	op[5] = (t_op){{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG, 0}, 6, 6, 1};
	op[6] = (t_op){{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG, 0}, 7, 6, 1};
	op[7] = (t_op){{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG, 0}, 8, 6, 1};
	op[8] = (t_op){{T_DIR, 0, 0, 0}, 9, 20, 0};
	op[9] = (t_op){{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG, 0}, 10, 25, 1};
	op[10] = (t_op){{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG, 0}, 11, 25, 1};
	op[11] = (t_op){{T_DIR, 0, 0, 0}, 12, 800, 0};
	op[12] = (t_op){{T_DIR | T_IND, T_REG, 0, 0}, 13, 10, 1};
	op[13] = (t_op){{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG, 0}, 14, 50, 1};
	op[14] = (t_op){{T_DIR, 0, 0, 0}, 15, 1000, 0};
	op[15] = (t_op){{T_REG, 0, 0, 0}, 16, 2, 1};
}

void init_vm(t_vm *vm)
{
	vm->flags.n = -1;
	vm->lives_in_cur_period = 1;
	init_op_arr(vm->ops);
}

void	print_player(t_player *players)
{
	int			count;

	count = 1;
	ft_printf("Introducing contestants...\n");
	while (players)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				count, players->head.prog_size,
				players->head.prog_name, players->head.comment);
		count++;
		players = players->next;
	}
}

int		ft_usage(void)
{
	printf("Usage: ./corewar [-d N -s N -v N -n N -a] <champion1.cor> <...>\n"
				"#### TEXT OUTPUT MODE #################################\n"
				"-d N : Dumps memory after N cycles then exits\n"
				"-s N : Runs N cycles, dumps memory, pauses, then repeats\n"
				"-v N "
				": Verbosity levels, can be added together to enable several\n"
				"       - 0 : Show only essentials\n"
				"       - 1 : Show lives\n"
				"       - 2 : Show cycles\n"
				"       - 4 : Show operations (Params are NOT litteral ...)\n"
				"       - 8 : Show deaths\n"
				"       - 16 : Show PC movements (Except for jumps)\n"
				"#### NCURSES OUTPUT MODE #################################\n"
				"    -n        : Ncurses output mode\n"
				"##########################################################\n");
	return (0);
}

void	lishnaja_fykcija(t_vm *vm)
{
	t_player	*players;

	players = vm->players;
	while (players->next)
		players = players->next;
	vm->winner = players->num_player;
}

int		main(int argc, char **argv)
{
	t_vm		vm;

	ft_memset(&vm, 0, sizeof(t_vm));
	init_vm(&vm);
	read_argv(&vm, argc, argv);
	if (!vm.players)
	{
		ft_usage();
		free_all(&vm);
	}
	write_in_map(vm.map, vm.players);
	player_create_car(vm.players, &vm.cars);
	print_player(vm.players);
	lishnaja_fykcija(&vm);
	play_while(&vm);
	print_winner(vm.players, vm.winner);
	free_all(&vm);
	return (0);
}
