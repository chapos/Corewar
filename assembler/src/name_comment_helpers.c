/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 12:08:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/24 18:42:08 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static void	concat_new_line_char(t_db *db, bool is_name)
{
	if (is_name)
	{
		db->v_data.name_size += 1;
		db->bot.bot_name = (char*)realloc(db->bot.bot_name,
			ft_strlen(db->bot.bot_name) + 2);
		ft_strncat(db->bot.bot_name, "\n", 1);
	}
	else
	{
		db->v_data.comment_size += 1;
		db->bot.bot_comment = (char*)realloc(db->bot.bot_comment,
			ft_strlen(db->bot.bot_comment) + 2);
		ft_strncat(db->bot.bot_comment, "\n", 1);
	}
}

static void	concat_multiline_string(t_db *db, bool is_name, size_t size)
{
	if (is_name)
	{
		db->v_data.name_size += size;
		db->bot.bot_name = (char*)realloc(db->bot.bot_name,
			ft_strlen(db->bot.bot_name) + size + 1);
		ft_strncat(db->bot.bot_name, db->v_data.line, size);
	}
	else
	{
		db->v_data.comment_size += size;
		db->bot.bot_comment = (char*)realloc(db->bot.bot_comment,
			ft_strlen(db->bot.bot_comment) + size + 1);
		ft_strncat(db->bot.bot_comment, db->v_data.line, size);
	}
}

static void	validate_multiline(t_db *db, bool is_name)
{
	size_t i;
	size_t j;

	i = 0;
	while (db->v_data.line[i] != '\"')
		++i;
	j = i + 1;
	while (ft_iswhitespace(db->v_data.line[j]))
		++j;
	if (db->v_data.line[j] != '\0' && db->v_data.line[j] != ';'
		&& db->v_data.line[j] != '#')
		clean_and_exit(db, "SYNTAX ERROR");
	concat_multiline_string(db, is_name, i);
	db->v_data.multiline_string = false;
}

void		read_multiline_string(t_db *db, bool is_name)
{
	int gnl_ret_val;

	ft_strdel(&db->v_data.line);
	while (db->v_data.multiline_string)
	{
		concat_new_line_char(db, is_name);
		gnl_ret_val = get_next_line(db->source_fd, &db->v_data.line);
		db->v_data.chars_counter += (ft_strlen(db->v_data.line) + 1);
		++db->v_data.line_counter;
		if (gnl_ret_val == 0 || gnl_ret_val == -1)
			clean_and_exit(db, "THERE IS NO NAME OR COMMENT");
		if (!ft_strchr(db->v_data.line, '\"'))
		{
			concat_multiline_string(db, is_name, ft_strlen(db->v_data.line));
			ft_strdel(&db->v_data.line);
		}
		else
			validate_multiline(db, is_name);
	}
}
