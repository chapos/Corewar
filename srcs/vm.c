/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:22:51 by rpetluk           #+#    #+#             */
/*   Updated: 2018/08/14 12:30:34 by rpetluk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void init_vm(t_vm *vm)
{
	vm->flags.v = 0;
	vm->flags.s = 0;
	vm->flags.d = 0;
	vm->flags.n = -1;
	vm->players = NULL;
}

void print_map(unsigned char *map)
{
	unsigned int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			printf("str N: %d ", (i / 64) + 1);
		printf("%.2x ", map[i]);
		i++;
		if (i % 64 == 0)
			printf("\n");
	}
}

int main(int argc, char **argv)
{

	t_vm				vm;

	init_vm(&vm);
	read_arg(&vm, argc, argv);

	write_in_map(vm.map, vm.players);

	print_map(vm.map);

//	ft_printf("%d\n", vm.flags.v);
//	ft_printf("%d\n", vm.flags.s);
//	ft_printf("%d\n", vm.flags.d);
//	ft_printf("%d\n", vm.flags.n);

	free_all(&vm);

	return (0);
}
