/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 16:32:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/02 16:32:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static bool		is_duplicate(t_db *db, const char *label_name)
{
	size_t i;

	i = 0;
	while (i < db->labels_counter)
	{
		if (ft_strequ(db->labels[i].name, label_name))
			return (true);
		++i;
	}
	return (false);
}

static void		add_label(t_db *db, const size_t label_length)
{
	char *label_name;

	label_name = ft_strsub(db->v_data.line, 0, label_length);
	if (db->labels == NULL)
	{
		db->labels = (t_label*)malloc(sizeof(t_label));
		db->labels[0].name = ft_strdup(label_name);
		db->labels[0].bytes_position = db->bot.bot_size;
		++db->labels_counter;
	}
	else
	{
		if (is_duplicate(db, label_name))
		{
			ft_strdel(&label_name);
			return ;
		}
		db->labels = realloc(db->labels, sizeof(t_label) *
				(db->labels_counter + 1));
		db->labels[db->labels_counter].name = ft_strdup(label_name);
		db->labels[db->labels_counter].bytes_position = db->bot.bot_size;
		++db->labels_counter;
	}
	ft_strdel(&label_name);
}

size_t			validate_and_save_lable(t_db *db)
{
	size_t i;

	i = 0;
	while (ft_strchr(LABEL_CHARS, db->v_data.line[i]))
		++i;
	if (db->v_data.line[i] != ':')
		clean_and_exit(db, "LABEL SYNTAX ERROR");
	add_label(db, i);
	return (i + 1);
}

static uint32_t	get_size_before_curr_instruction(t_db *db, size_t i)
{
	uint32_t	res;
	size_t		k;

	res = 0;
	k = 0;
	while (k < i)
	{
		res += db->bot.instructions[k].instruction_size;
		++k;
	}
	return (res);
}

uint32_t		calculate_label_position(t_db *db, size_t i, size_t j)
{
	uint32_t	res;
	bool		label_exist;
	size_t		k;

	label_exist = false;
	res = 0;
	k = 0;
	while (k < db->labels_counter)
	{
		if (ft_strequ(db->labels[k].name,
				db->bot.instructions[i].args[j].label_name))
		{
			label_exist = true;
			res = db->labels[k].bytes_position
					- get_size_before_curr_instruction(db, i);
			break ;
		}
		++k;
	}
	if (!label_exist)
		clean_and_exit(db, "NOT EXISTING LABEL NAME IN ARGUMENT");
	return (res);
}
