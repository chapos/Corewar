/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_lib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:53:11 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/22 12:56:53 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void			free_all(t_vm *vm)
{
	t_player	*temp;

	if (vm->flags.visual && vm->visual != NULL)
		wait_end(vm);
	while (vm->players)
	{
		temp = vm->players->next;
		free(vm->players->code);
		free(vm->players);
		vm->players = temp;
	}
	exit(1);
}

void			protect_visual(t_vm *vm)
{
	vm->flags.v = 0;
	vm->flags.s = 0;
	vm->flags.d = 0;
	vm->flags.a = 0;
}
