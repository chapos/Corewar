/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:44:04 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/22 19:43:20 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	init_single(t_carriage *carriage, unsigned char *map, t_arg *arg)
{
	if (CHECK_REG(arg->type, arg->readed))
		arg->value = carriage->reg[arg->readed];
	else if (arg->type == T_IND)
		read_int_from_map(&arg->value, carriage->pc + arg->readed, map);
	else
		arg->value = arg->readed;
}

/*
** Load T_IND and T_REG where needed into internal struct val
*/

void		init_args(t_carriage *carriage, unsigned char *map, t_args *args)
{
	init_single(carriage, map, &args->arg1);
	init_single(carriage, map, &args->arg2);
	init_single(carriage, map, &args->arg3);
	init_single(carriage, map, &args->arg4);
}
