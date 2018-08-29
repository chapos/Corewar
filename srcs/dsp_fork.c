#include "../includes/op.h"

void	print_fork(t_carriage *carriage, t_args *args)
{
	int	val;

	val = (carriage->pc + args->arg1.value) % MEM_SIZE;
	print_pnum(carriage->num_car);
	ft_printf("fork %d (%d)\n", args->arg1.value, val);
}

int		dsp_fork(t_carriage *father, t_vm *vm)
{
	int			npos;
	t_carriage	*son;

	son = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	ft_memset(&vm->args, 0, sizeof(t_args));
	ft_memcpy(son, father, sizeof(t_carriage));
	read_short_from_map(&npos, father->pc + 1, vm->map);
	npos %= IDX_MOD;
	vm->args.arg1.readed = npos;
	vm->args.arg1.value = npos;
	son->pc = normalize_pc(npos + father->pc);
	son->num_car = ++vm->process_counter;
	son->command = 0;
	add_car(&vm->cars, son);
	vm->args.shift = 2;
	return (1);
}
