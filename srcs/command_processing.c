/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailkiv <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:16:54 by ailkiv            #+#    #+#             */
/*   Updated: 2018/09/22 16:19:34 by ailkiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

static int		num_player(int num_player, t_vm *vm)
{
	int			i;
	t_player	*temp;

	i = 1;
	temp = vm->players;
	while (temp)
	{
		if (temp->num_player == num_player)
			return (i);
		i++;
		temp = temp->next;
	}
	return (0);
}

static int		c_pair(int num)
{
	if (num == 1)
		return (COLOR_PAIR(15));
	else if (num == 2)
		return (COLOR_PAIR(16));
	else if (num == 3)
		return (COLOR_PAIR(17));
	else if (num == 4)
		return (COLOR_PAIR(18));
	return (0);
}

void			command_processing(t_carriage *tcar, t_vm *vm, int len)
{
	int			x;
	int			y;
	int			i;
	int			temp;

	i = 0;
	temp = vm->args.stored_to % MEM_SIZE;
	if (temp < 0)
		temp = temp + MEM_SIZE;
	push_back_vcars(&(vm->visual->vcars),
			c_pair(num_player(tcar->num_player, vm)), temp, len);
	while (i < len)
	{
		y = (temp) / 64 + 2;
		x = (temp) % 64 * 3 + 3;
		on_color_player50(num_player(tcar->num_player, vm), vm);
		mvwprintw(vm->visual->map, y, x, "%02x", vm->map[temp]);
		off_color_player50(num_player(tcar->num_player, vm), vm);
		temp++;
		if (temp > MEM_SIZE - 1)
			temp = 0;
		i++;
	}
}

void			print_back(t_vm *vm)
{
	int			x;
	int			y;
	int			i;

	i = 0;
	while (i < vm->visual->vcars->len)
	{
		y = (vm->visual->vcars->stored_to) / 64 + 2;
		x = (vm->visual->vcars->stored_to) % 64 * 3 + 3;
		if (second_command(vm))
			help_print_back(vm, y, x);
		vm->visual->vcars->stored_to++;
		if (vm->visual->vcars->stored_to > MEM_SIZE - 1)
			vm->visual->vcars->stored_to = 0;
		i++;
	}
}

void			cycles_decrease(t_vm *vm)
{
	t_vcars		*vcars;

	if (vm->visual->vcars)
	{
		while (vm->visual->vcars && vm->visual->vcars->cycles <= 0)
		{
			if (vm->visual->vcars->len == 4)
				print_back(vm);
			else
				print_back_live(vm);
			del_front_vcars(&(vm->visual->vcars));
		}
		vcars = vm->visual->vcars;
		while (vcars)
		{
			vcars->cycles--;
			vcars = vcars->next;
		}
	}
}
