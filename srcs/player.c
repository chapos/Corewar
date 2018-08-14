
#include "op.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

//int ft_read_unsigned_int(int fd)
//{
//	unsigned int	ret;
//	unsigned char	c;
//	int i;
//
//	i = 1;
//	ret = 0;
//	while (i--)
//	{
//		if (read(fd, &c, 1) == -1)
//			return (-1);
//		ret |= c;
//		if (i)
//			ret <<= 8;
//	}
//	printf("%u\n", ret);
//	return (ret);
//}
//
//int ft_read_char(int fd,char *ret, int count)
//{
//	if (read(fd, ret, count) == -1)
//			return (-1);
//	return (0);
//}
//
//int write_in_player(t_header *head)
//{
//
//	int fd;
//	unsigned char p[4];
//	unsigned char c;
//	unsigned int *t;
//
//	if (-1 == (fd = open("Gagnant.cor", O_RDONLY)))
//		return (-1);
//	head->magic = ft_read_unsigned_int(fd);
//	ft_read_char(fd, head->prog_name, 128);
//	ft_read_unsigned_int(fd);
//	head->prog_size = ft_read_unsigned_int(fd);
//	ft_read_char(fd, head->comment, 2048);
//
//	printf("%u\n", head->magic);
//	printf("%s\n", head->prog_name);
//	printf("%u\n", head->prog_size);
//	printf("%s\n", head->comment);
//
////	(read(fd, &c, 1));
////	{
////		printf("%c\n", (c));
////	}
//
//	return (0);
//
//}

int ft_swap_unsigned_int_byte(unsigned int *swap)
{
	*swap = ((*swap << 24) & 0xff000000)
				 | (*swap << 8 & 0x00ff0000)
				 | (*swap >> 8 & 0x0000ff00)
				 | (*swap >> 24 & 0x000000ff);
	return (0);
}

void	read_prog(int fd, unsigned int prog_size, unsigned char **code)
{
	unsigned char *prog;

	prog = (unsigned char *)malloc(prog_size);
	read(fd, prog, prog_size);
	prog[prog_size] = '\0';
	*code = prog;
}

int read_player(t_player *player, int fd)
{
	read(fd, &player->head, sizeof(t_header));
	ft_swap_unsigned_int_byte(&player->head.magic);
	ft_swap_unsigned_int_byte(&player->head.prog_size);
	read_prog(fd, player->head.prog_size, &player->code);

	close(fd);

	return (0);
}

int read_players(t_list **players, int ac, char **av)
{
	int i;
	int fd;

	i = 1;
	t_player player;

	while (i < ac)
	{
		if (-1 == (fd = open(av[i], O_RDONLY)))
			return (-1);
		read_player(&player, fd);
		ft_lstappend(players, ft_lstnew(&player, sizeof(player)));
		i++;
	}

	return (0);
}
