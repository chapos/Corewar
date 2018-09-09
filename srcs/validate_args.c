/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 11:55:39 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/03 15:40:13 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static int	a_check(t_arg *arg, t_arg_type parg)
{
	int		res;

	res = 0;
	if (parg & T_DIR && arg->type == T_DIR)
		res = 1;
	else if (parg & T_IND && arg->type == T_IND)
		res = 1;
	else if ((parg & T_REG && arg->type == T_REG) &&
				(arg->readed > 0 && arg->readed <= REG_NUMBER))
		res = 1;
	else if (!parg)
		res = 1;
	return (res);
}

int			validate_args(t_args *args, t_pargs *pargs)
{
	int		res;

	res = 1;
	res &= a_check(&args->arg1, pargs->arg1);
	res &= a_check(&args->arg2, pargs->arg2);
	res &= a_check(&args->arg3, pargs->arg3);
	res &= a_check(&args->arg4, pargs->arg4);
	return (res);
}
