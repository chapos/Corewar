/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dsp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 11:12:56 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/22 19:46:43 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	init_dsps(t_dsp *dsp)
{
	dsp[0].exec_cmd = dsp_live;
	dsp[1].exec_cmd = dsp_ld;
	dsp[2].exec_cmd = dsp_st;
	dsp[3].exec_cmd = dsp_add;
	dsp[4].exec_cmd = dsp_sub;
	dsp[5].exec_cmd = dsp_and;
	dsp[6].exec_cmd = dsp_or;
	dsp[7].exec_cmd = dsp_xor;
	dsp[8].exec_cmd = dsp_zjmp;
	dsp[9].exec_cmd = dsp_ldi;
	dsp[10].exec_cmd = dsp_sti;
	dsp[11].exec_cmd = dsp_fork;
	dsp[12].exec_cmd = dsp_lld;
	dsp[13].exec_cmd = dsp_lldi;
	dsp[14].exec_cmd = dsp_lfork;
	dsp[15].exec_cmd = dsp_aff;
}

static void	init_prints(t_dsp *dsp)
{
	dsp[0].print_cmd = print_live;
	dsp[1].print_cmd = print_ld;
	dsp[2].print_cmd = print_st;
	dsp[3].print_cmd = print_add;
	dsp[4].print_cmd = print_sub;
	dsp[5].print_cmd = print_and;
	dsp[6].print_cmd = print_or;
	dsp[7].print_cmd = print_xor;
	dsp[8].print_cmd = print_zjmp;
	dsp[9].print_cmd = print_ldi;
	dsp[10].print_cmd = print_sti;
	dsp[11].print_cmd = print_fork;
	dsp[12].print_cmd = print_lld;
	dsp[13].print_cmd = print_lldi;
	dsp[14].print_cmd = print_lfork;
	dsp[15].print_cmd = print_aff;
}

/*
** Init array with pointers to funcitons that executes/prints
** instructions.
*/

void		init_dsp(t_dsp *dsp)
{
	init_dsps(dsp);
	init_prints(dsp);
}
