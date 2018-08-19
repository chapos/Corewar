/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 15:02:27 by eyevresh          #+#    #+#             */
/*   Updated: 2018/08/18 15:02:38 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static int	open_source_file(const char *file_name)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(OPEN_SOURCE_ERR, STDERR_FILENO);
		ft_putstr_fd(file_name, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		exit(0);
	}
	return (fd);
}

static int	create_output_file(char *file_name)
{
	int		fd;
	char	*name_offset;
	char	*new_name;

	name_offset = ft_strrchr(file_name, '.');
	*name_offset = '\0';
	new_name = ft_strjoin(file_name, ".cor");
	fd = open(new_name, O_RDWR | O_CREAT, 777);
	if (fd == -1)
	{
		ft_putstr_fd(OPEN_OUTPUT_ERR, STDERR_FILENO);
		ft_putstr_fd(new_name, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		ft_strdel(&new_name);
		exit(0);
	}
	ft_strdel(&new_name);
	return (fd);
}

static void	check_file_name(const char *file_name)
{
	const char *name_offset;

	name_offset = ft_strrchr(file_name, '.');
	if (name_offset == NULL || ft_strlen(name_offset) != 2
		|| name_offset[1] != 's')
	{
		ft_putstr_fd(FILE_NAME_ERR, STDERR_FILENO);
		exit(0);
	}
}

int			main(int argc, char **argv)
{
	int source_fd;
	int output_fd;

	if (argc < 2)
	{
		ft_putstr_fd(USAGE, STDERR_FILENO);
		exit(0);
	}
	check_file_name(argv[argc - 1]);
	source_fd = open_source_file(argv[argc - 1]);
	output_fd = create_output_file(argv[argc - 1]);
	return (0);
}
