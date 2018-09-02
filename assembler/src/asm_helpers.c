/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 14:28:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/08/21 14:28:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

uint32_t	big_little_endian(uint32_t n)
{
	uint32_t result;

	result = ((n >> 24) & 0xff) | ((n << 8) & 0xff0000)
			| ((n >> 8) & 0xff00) | ((n << 24) & 0xff000000);
	return (result);
}

void		clean_and_exit(t_db *db, const char *log)
{
	size_t i;

	if (log != NULL)
		ft_dprintf(STDERR_FILENO, "{red}ERROR[line %zu] - %s\n{def}",
												db->v_data.line_counter, log);
	ft_strdel(&db->v_data.line);
	ft_strdel(&db->bot.bot_comment);
	ft_strdel(&db->bot.bot_name);
	i = 0;
	while (i < db->labels_counter)
		ft_strdel(&db->labels[i++].name);
	if (db->labels != NULL)
		free(db->labels);
	exit(0);
}
