/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_pc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 19:29:55 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/22 19:49:37 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
** With this function we assure that PC is valid
*/

int		normalize_pc(int pc)
{
	pc %= MEM_SIZE;
	if (pc < 0)
		pc = MEM_SIZE + pc;
	return (pc);
}
