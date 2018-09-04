/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpetluk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 10:07:35 by rpetluk           #+#    #+#             */
/*   Updated: 2018/09/01 10:07:37 by rpetluk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"

void	error_many_champions(t_vm *vm)
{
	write(2, "Too many champions\n", 19);
	free_all(vm);
}

void	error_read_file(t_vm *vm, char *file_name)
{
	write(2, "Can't read source file ", 23);
	write(2, file_name, ft_strlen(file_name));
	write(2, "\n", 1);
	free_all(vm);
}

void	error_not_validate_file(t_vm *vm, char *file_name)
{
	write(2, "File ", 5);
	write(2, file_name, ft_strlen(file_name));
	write(2, " has an invalid header\n", 23);
	free_all(vm);
}

void	error_differ_prog_size(t_vm *vm, char *file_name)
{
	write(2, "File ", 5);
	write(2, file_name, ft_strlen(file_name));
	write(2, " has a code size that differ from what its header says\n", 55);
	free_all(vm);
}

void	error_big_prog_size(t_vm *vm, char *file_name, int prog_size)
{
	write(2, "Error: File ", 12);
	write(2, file_name, ft_strlen(file_name));
	write(2, " has too large a code (", 23);
	ft_putnbr_fd(prog_size, 2);
	write(2, " bytes > 682 bytes)\n", 20);
	free_all(vm);
}
