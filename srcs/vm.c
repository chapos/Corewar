/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:22:51 by rpetluk           #+#    #+#             */
/*   Updated: 2018/08/30 16:02:26 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	init_vm(t_vm *vm)
{
	vm->flags.n = -1;
	vm->lives_in_cur_period = 1;
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
