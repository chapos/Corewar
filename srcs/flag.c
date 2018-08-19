
#include "../includes/op.h"



int flag_n(t_player *players, int n)
{
	while (players)
	{
		if (players->num_player == n)
			return (1);
		players = players->next;
	}
	return (0);
}

int if_flag(t_flags *flag, char *s1, char *s2)
{
	if (s2 && !ft_strcmp(s1, "-v"))
	{
		if (ft_isvldint(s2))
			flag->v = ft_atoi(s2);
		return (1);
	}
	if (s2 && !ft_strcmp(s1, "-s"))
	{
		if (ft_isvldint(s2))
			flag->s = ft_atoi(s2);
		return (1);
	}
	if (s2 && !ft_strcmp(s1, "-dump"))
	{
		if (ft_isvldint(s2))
			flag->d = ft_atoi(s2);
		return (1);
	}
	if (s2 && !ft_strcmp(s1, "-n"))
	{
		if (ft_isvldint(s2))
			flag->n = ft_atoi(s2);
		return (1);
	}
	return (0);
}

int read_plaer(t_vm *vm)
{
	int fd;
	int error;
	t_player *temp;

	temp = vm->players;
	while (temp)
	{
		if (-1 == (fd = open(temp->file_name, O_RDONLY)))
			error_read_file(vm, temp->file_name);
		else
		{
			if ((error = read_player(temp, fd)))
			{
				if (error == 1)
					error_not_validate_file(vm, temp->file_name);
				if (error == 2)
					error_differ_prog_size(vm, temp->file_name);
				if (error == 3)
					error_big_prog_size(vm, temp->file_name, temp->head.prog_size);
			}
		}
		temp = temp->next;
	}
	return (0);
}

int read_arg(t_vm *vm, int ac, char **av)
{
	int i;
	int count;

	count = 0;
	i = 1;

	while (ac > i)
	{
		if (!if_flag(&vm->flags, av[i],av[i + 1]))
		{
			while (flag_n(vm->players, vm->flags.n))
				vm->flags.n--;
			add_player(&vm->players, vm->flags.n, av[i]);
			count++;
			if (count > 4)
				error_many_champions(vm);
		}
		else
			i++;
		i++;
	}
	read_plaer(vm);
	return (0);
}