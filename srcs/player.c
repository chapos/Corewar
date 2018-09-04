/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 15:42:23 by oevtushe          #+#    #+#             */
/*   Updated: 2018/09/03 19:26:56 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

int			add_player(t_player **player, int n, char *file_name)
{
	t_player		*new;
	t_player		*temp;

	temp = *player;
	new = (t_player *)malloc(sizeof(t_player));
	new->next = NULL;
	new->file_name = file_name;
	new->num_player = n;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*player = new;
	return (0);
}

static int	read_prog(int fd, unsigned int prog_size, unsigned char **code)
{
	unsigned char	*prog;

	prog = (unsigned char *)malloc(prog_size + 1);
	if (read(fd, prog, prog_size + 1) != prog_size)
	{
		free(prog);
		return (-1);
	}
	*code = prog;
	return (0);
}

int			read_header(t_player *player, int fd)
{
	read(fd, &player->head, sizeof(t_header));
	ft_byterev_ui32(&player->head.magic);
	if (player->head.magic != COREWAR_EXEC_MAGIC)
	{
		close(fd);
		return (1);
	}
	ft_byterev_ui32(&player->head.prog_size);
	if (read_prog(fd, player->head.prog_size, &player->code))
	{
		close(fd);
		return (2);
	}
	if (player->head.prog_size > CHAMP_MAX_SIZE)
	{
		close(fd);
		return (3);
	}
	close(fd);
	return (0);
}
