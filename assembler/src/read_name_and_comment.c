/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_name_and_comment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 13:59:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/24 18:42:11 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static void	validate_syntax(t_db *db, const char *tmp, bool is_name)
{
	size_t i;

	i = 0;
	if (*tmp != '\"')
		clean_and_exit(db, "SYNTAX ERROR");
	++tmp;
	while (tmp[i] != '\"' && tmp[i] != '\0')
		++i;
	if (is_name)
		db->v_data.name_size = i;
	else
		db->v_data.comment_size = i;
	if (tmp[i] == '\0')
	{
		db->v_data.multiline_string = true;
		return ;
	}
	++i;
	while (ft_iswhitespace(tmp[i]))
		++i;
	if (tmp[i] != '#' && tmp[i] != ';' && tmp[i] != '\0')
		clean_and_exit(db, "SYNTAX ERROR");
}

static void	read_name(t_db *db)
{
	char *tmp;

	if (db->v_data.name_readed)
		clean_and_exit(db, "THERE IS ALREADY ONE NAME");
	tmp = db->v_data.line + 5;
	while (ft_iswhitespace(*tmp))
		++tmp;
	validate_syntax(db, tmp, true);
	++tmp;
	db->bot.bot_name = ft_strnew(db->v_data.name_size);
	ft_strncpy(db->bot.bot_name, tmp, db->v_data.name_size);
	if (db->v_data.multiline_string)
		read_multiline_string(db, true);
	if (db->v_data.name_size > PROG_NAME_LENGTH)
		clean_and_exit(db, "CHAMPION NAME TOO LONG (MAX LENGTH 128)");
	db->v_data.name_readed = true;
}

static void	read_comment(t_db *db)
{
	char *tmp;

	if (db->v_data.comment_readed)
		clean_and_exit(db, "THERE IS ALREADY ONE COMMENT");
	tmp = db->v_data.line + 8;
	while (ft_iswhitespace(*tmp))
		++tmp;
	validate_syntax(db, tmp, false);
	++tmp;
	db->bot.bot_comment = ft_strnew(db->v_data.comment_size);
	ft_strncpy(db->bot.bot_comment, tmp, db->v_data.comment_size);
	if (db->v_data.multiline_string)
		read_multiline_string(db, false);
	if (db->v_data.comment_size > COMMENT_LENGTH)
		clean_and_exit(db, "CHAMPION COMMENT TOO LONG (MAX LENGTH 2048)");
	db->v_data.comment_readed = true;
}

static void	validate_line(t_db *db)
{
	char *tmp;

	tmp = db->v_data.line;
	db->v_data.line = ft_strtrim(tmp);
	ft_strdel(&tmp);
	if (db->v_data.line[0] == '#' || db->v_data.line[0] == ';'
		|| ft_strequ(db->v_data.line, ""))
		return ;
	if (!ft_strnequ(db->v_data.line, ".name", 5) &&
			!ft_strnequ(db->v_data.line, ".comment", 8))
		clean_and_exit(db, "SYNTAX ERROR");
	ft_strnequ(db->v_data.line, ".name", 5) ? read_name(db) : read_comment(db);
}

void		read_name_and_comment(t_db *db)
{
	int		gnl_ret_value;

	while (!db->v_data.name_readed || !db->v_data.comment_readed)
	{
		gnl_ret_value = get_next_line(db->source_fd, &db->v_data.line);
		db->v_data.chars_counter += (ft_strlen(db->v_data.line) + 1);
		++db->v_data.line_counter;
		if (gnl_ret_value == 0 || gnl_ret_value == -1)
			clean_and_exit(db, "THERE IS NO NAME OR COMMENT");
		else if (ft_strequ(db->v_data.line, ""))
			;
		else
			validate_line(db);
		ft_strdel(&db->v_data.line);
	}
}
