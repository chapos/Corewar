/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args_from_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:32:08 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/18 16:29:20 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static int	read_arg(int pc, unsigned char *map, unsigned int acb_mask, int *shift, t_arg *arg)
{
	int		res;

	res = 0;
	// Direct
	if (acb_mask == 0x80)
	{
		arg->readed = *(int *)&map[pc + *shift + 1];
		ft_byterev_ui32((unsigned int *)&arg->readed);
		arg->type = T_DIR;
		arg->size = DIR_SIZE;
		*shift += sizeof(int);
	}
	// Register
	else if (acb_mask == 0x40)
	{
		arg->readed = map[pc + *shift + 1];
		arg->type = T_REG;
		arg->size = 1;
		*shift += sizeof(unsigned char);
	}
	// Indirect
	else if (acb_mask == 0xc0)
	{
		arg->readed = *(short *)&map[pc + *shift + 1];
		ft_byterev_us16((unsigned short *)&arg->readed);
		//arg->value %= IDX_MOD;
		arg->readed = (short)arg->readed;
		arg->type = T_IND;
		arg->size = IND_SIZE;
		*shift += sizeof(short);
	}
	return (res);
}

void		read_args_from_map(int pc, unsigned char *map, t_args *args)
{
	unsigned char	acb;
	int				shift;

	shift = 1;
	acb = map[pc + 1];
	read_arg(pc, map, acb & ARG_MASK1, &shift, &args->arg1);
	read_arg(pc, map, (acb & ARG_MASK2) << 2, &shift, &args->arg2);
	read_arg(pc, map, (acb & ARG_MASK3) << 4, &shift, &args->arg3);
	read_arg(pc, map, (acb & ARG_MASK4) << 6, &shift, &args->arg4);
}

void	read_short_from_map(short *val, int pos, unsigned char *map)
{
	unsigned char	*p;

	pos %= MEM_SIZE;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	p = (unsigned char *)val;
	if ((pos + sizeof(short) <= MEM_SIZE))
		ft_memcpy(val, &map[pos], sizeof(short));
	else
	{
		ft_memcpy(p, &map[pos], MEM_SIZE - pos);
		p += MEM_SIZE - pos;
		ft_memcpy(p, map, sizeof(short) - (MEM_SIZE - pos));
	}
}

void	read_int_from_map(int *val, int pos, unsigned char *map)
{
	unsigned char	*p;

	pos %= MEM_SIZE;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	p = (unsigned char *)val;
	if ((pos + sizeof(int) <= MEM_SIZE))
		ft_memcpy(val, &map[pos], sizeof(int));
	else
	{
		ft_memcpy(p, &map[pos], MEM_SIZE - pos);
		p += MEM_SIZE - pos;
		ft_memcpy(p, map, sizeof(int) - (MEM_SIZE - pos));
	}
}
