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

const char	*skip_whitespaces(const char *line)
{
	while (ft_iswhitespace(*line))
		++line;
	return (line);
}

uint32_t	big_little_endian(uint32_t n, bool four_bytes)
{
	uint32_t result;

	if (four_bytes)
	{
		result = ((n >> 24) & 0xff) | ((n << 8) & 0xff0000)
			| ((n >> 8) & 0xff00) | ((n << 24) & 0xff000000);
	}
	else
		result = ((n >> 8) & 0xff) | ((n << 8) & 0xff00);
	return (result);
}

void		allocate_new_instruction(t_db *db)
{
	size_t i;

	if (db->bot.instructions == NULL)
	{
		db->bot.instructions = (t_instr_data*)malloc(sizeof(t_instr_data));
		++db->inst_counter;
	}
	else
	{
		db->bot.instructions = realloc(db->bot.instructions,
			sizeof(t_instr_data) * (db->inst_counter + 1));
		++db->inst_counter;
	}
	i = 0;
	while (i < 4)
	{
		db->bot.instructions[db->inst_counter - 1].args[i].expr.op = '\0';
		db->bot.instructions[db->inst_counter - 1].args[i].expr.value = 0;
		db->bot.instructions[db->inst_counter - 1].args[i].label_name = NULL;
		++i;
	}
	db->bot.instructions[db->inst_counter - 1].codage = 0;
}

static void	clean_instructions(t_db *db)
{
	size_t i;
	size_t j;

	if (db->bot.instructions != NULL)
	{
		i = 0;
		while (i < db->inst_counter)
		{
			j = 0;
			while (j < 4)
			{
				ft_strdel(&db->bot.instructions[i].args[j].label_name);
				++j;
			}
			++i;
		}
		free(db->bot.instructions);
	}
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
	if (db->labels != NULL)
	{
		while (i < db->labels_counter)
			ft_strdel(&db->labels[i++].name);
		free(db->labels);
	}
	clean_instructions(db);
	exit(0);
}
