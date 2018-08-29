/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_from_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 11:56:42 by oevtushe          #+#    #+#             */
/*   Updated: 2018/08/28 18:59:06 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static int	read_arg(int pc, t_pair *pair, unsigned int acb_mask, t_reader reader)
{
	int				res;
	char			size;
	int				shift;
	unsigned char	*map;
	t_arg			*arg;

	res = 0;
	shift = 0;
	arg = (t_arg *)pair->scd;
	map = (unsigned char *)pair->fst;
	// Direct
	if (acb_mask == 0x80)
	{
		size = reader.read_dir(&arg->readed, pc, map);
		shift = size;
		arg->type = T_DIR;
		arg->size = size;
	}
	// Register
	else if (acb_mask == 0x40)
	{
		arg->readed = map[pc];
		arg->type = T_REG;
		arg->size = 1;
		shift = sizeof(unsigned char);
	}
	// Indirect
	else if (acb_mask == 0xc0)
	{
		size = reader.read_ind(&arg->readed, pc, map);
		shift = size;
		arg->type = T_IND;
		arg->size = size;
	}
	return (shift);
}

void		read_args_from_map(int pc, unsigned char *map, t_args *args, t_reader reader)
{
	unsigned char	acb;
	int				shift;
	t_pair			pair;

	// acb
	shift = 1;
	acb = map[(pc + 1) % MEM_SIZE];
	pair.fst = map;
	pair.scd = &args->arg1;
	shift += read_arg((pc + shift + 1) % MEM_SIZE, &pair, acb & ARG_MASK1, reader);
	pair.scd = &args->arg2;
	shift += read_arg((pc + shift + 1) % MEM_SIZE, &pair, (acb & ARG_MASK2) << 2, reader);
	pair.scd = &args->arg3;
	shift += read_arg((pc + shift + 1) % MEM_SIZE, &pair, (acb & ARG_MASK3) << 4, reader);
	pair.scd = &args->arg4;
	shift += read_arg((pc + shift + 1) % MEM_SIZE, &pair, (acb & ARG_MASK4) << 6, reader);
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
