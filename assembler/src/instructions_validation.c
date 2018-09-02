/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 15:47:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/02 15:47:00 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

bool	is_instruction(const char *line)
{
	if (ft_strnequ(line, "live", 4) || ft_strnequ(line, "ld", 2) ||
			ft_strnequ(line, "st", 2) || ft_strnequ(line, "add", 3) ||
			ft_strnequ(line, "sub", 3) || ft_strnequ(line, "and", 3) ||
			ft_strnequ(line, "or", 2) || ft_strnequ(line, "xor", 3) ||
			ft_strnequ(line, "zjmp", 4) || ft_strnequ(line, "ldi", 3) ||
			ft_strnequ(line, "sti", 3) || ft_strnequ(line, "fork", 4) ||
			ft_strnequ(line, "lld", 3) || ft_strnequ(line, "lldi", 4) ||
			ft_strnequ(line, "lfork", 5) || ft_strnequ(line, "aff", 3))
		return (true);
	return (false);
}
