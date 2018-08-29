/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:22:51 by rpetluk           #+#    #+#             */
/*   Updated: 2018/08/28 19:07:11 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void init_vm(t_vm *vm)
{
	vm->flags.n = -1;
	//vm->game_cycle = 1;
}

void print_player(t_player *players)
{
	int count;

	count = 1;
	write(1, "Introducing contestants...\n", 27);
	while (players)
	{
		write(1, "* Player ", 9);
		ft_putnbr(count);
		write(1, ", weighing ", 11);
		ft_putnbr(players->head.prog_size);
		write(1, " bytes, \"", 9);
		ft_putstr(players->head.prog_name);
		write(1, "\" (\"", 4);
		ft_putstr(players->head.comment);
		write(1, "\") !\n", 5);
		count++;
		players = players->next;
	}
	//* Player 1, weighing 325 bytes, "Celebration Funebre v0.99pl42" ("Jour J") !
}

int ft_usage()
{
	ft_printf("Usage: ./corewar [-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>\n"
					  "    -a        : Prints output from \"aff\" (Default is to hide it)\n"
					  "#### TEXT OUTPUT MODE ##########################################################\n"
					  "    -d N      : Dumps memory after N cycles then exits\n"
					  "    -s N      : Runs N cycles, dumps memory, pauses, then repeats\n"
					  "    -v N      : Verbosity levels, can be added together to enable several\n"
					  "                - 0 : Show only essentials\n"
					  "                - 1 : Show lives\n"
					  "                - 2 : Show cycles\n"
					  "                - 4 : Show operations (Params are NOT litteral ...)\n"
					  "                - 8 : Show deaths\n"
					  "                - 16 : Show PC movements (Except for jumps)\n"
					  "#### BINARY OUTPUT MODE ########################################################\n"
					  "    -b        : Binary output mode for corewar.42.fr\n"
					  "    --stealth : Hides the real contents of the memory\n"
					  "#### NCURSES OUTPUT MODE #######################################################\n"
					  "    -n        : Ncurses output mode\n"
					  "    --stealth : Hides the real contents of the memory\n"
					  "################################################################################\n");
	return (0);
}

int main(int argc, char **argv)
{

	t_vm	vm;

	ft_memset(&vm, 0, sizeof(t_vm));
	init_vm(&vm);
	read_argv(&vm, argc, argv);
	if (!vm.players)
	{
		ft_usage();
		exit (1);
	}
	write_in_map(vm.map, vm.players);

	player_create_car(vm.players , &vm.cars);

	print_player(vm.players);

	play_while(&vm);

	free_all(&vm);
	return (0);
}

