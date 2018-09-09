/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:56:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/09 16:56:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

size_t	handle_direct_argument(t_db *db, const char *instruction, int arg_num)
{
	size_t length;

	length = 0;
	if (instruction[length] == ':')
	{
		++length;
	}
	else
	{

	}
	return (length);
}
