/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_from_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 11:56:42 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/22 19:51:26 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static int	read_arg(int pc, t_pair *pair,
				unsigned int acb_mask, t_reader reader)
{
	int				res;
	int				shift;
	unsigned char	*map;

	res = 0;
	shift = 0;
	map = (unsigned char *)pair->fst;
	if (acb_mask == 0x80)
	{
		shift = reader.read_dir(&((t_arg *)pair->scd)->readed, pc, map);
		((t_arg *)pair->scd)->type = T_DIR;
	}
	else if (acb_mask == 0x40)
	{
		((t_arg *)pair->scd)->readed = map[pc];
		((t_arg *)pair->scd)->type = T_REG;
		shift = sizeof(unsigned char);
	}
	else if (acb_mask == 0xc0)
	{
		shift = reader.read_ind(&((t_arg *)pair->scd)->readed, pc, map);
		((t_arg *)pair->scd)->type = T_IND;
	}
	((t_arg *)pair->scd)->size = shift;
	return (shift);
}

/*
** Read instruction arguments
*/

void		read_args_from_map(int pc, unsigned char *map,
							t_args *args, t_reader reader)
{
	unsigned char	acb;
	int				shift;
	t_pair			pair;

	shift = 1;
	acb = map[(pc + 1) % MEM_SIZE];
	pair.fst = map;
	pair.scd = &args->arg1;
	shift += read_arg((pc + shift + 1) % MEM_SIZE,
					&pair, acb & ARG_MASK1, reader);
	pair.scd = &args->arg2;
	shift += read_arg((pc + shift + 1) % MEM_SIZE,
					&pair, (acb & ARG_MASK2) << 2, reader);
	pair.scd = &args->arg3;
	shift += read_arg((pc + shift + 1) % MEM_SIZE,
					&pair, (acb & ARG_MASK3) << 4, reader);
	pair.scd = &args->arg4;
	shift += read_arg((pc + shift + 1) % MEM_SIZE,
					&pair, (acb & ARG_MASK4) << 6, reader);
}

size_t		read_short_from_map(int *val, int pos, unsigned char *map)
{
	short			safe;
	unsigned char	*p;

	safe = 0;
	pos %= MEM_SIZE;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	p = (unsigned char *)&safe;
	if ((pos + sizeof(short) <= MEM_SIZE))
		ft_memcpy(&safe, &map[pos], sizeof(short));
	else
	{
		ft_memcpy(p, &map[pos], MEM_SIZE - pos);
		p += MEM_SIZE - pos;
		ft_memcpy(p, map, sizeof(short) - (MEM_SIZE - pos));
	}
	ft_byterev_us16((unsigned short *)&safe);
	*val = safe;
	return (sizeof(short));
}

size_t		read_int_from_map(int *val, int pos, unsigned char *map)
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
	ft_byterev_ui32((unsigned int *)val);
	return (sizeof(int));
}
