
#include "../includes/op.h"

void error_many_champions(t_vm *vm)
{
	write(2, "Too many champions\n", 19);
	free_all(vm);
	exit(1);
}

void error_read_file(t_vm *vm, char *file_name)
{
	write(2, "Can't read source file ", 23);
	write(2, file_name, ft_strlen(file_name));
	write(2, "\n", 1);
	free_all(vm);
	exit(1);
}

void error_not_validate_file(t_vm *vm, char *file_name)
{
	write(2, "File ", 5);
	write(2, file_name, ft_strlen(file_name));
	write(2, " has an invalid header\n", 23);
	free_all(vm);
	exit(1);
}

void error_differ_prog_size(t_vm *vm, char *file_name)
{
	write(2, "File ", 5);
	write(2, file_name, ft_strlen(file_name));
	write(2, " has a code size that differ from what its header says\n", 55);
	free_all(vm);
	exit(1);
}
void error_big_prog_size(t_vm *vm, char *file_name, int prog_size)
{
	write(2, "File ", 5);
	write(2, file_name, ft_strlen(file_name));
	write(2, " has too large a code (", 23);
	ft_putnbr_fd(prog_size, 2);
	write(2, " > 682 bytes)\n", 14);
	free_all(vm);
	exit(1);
}
