#include "../includes/op.h"

void			push_back_vcars(t_vcars **begin, int c_pair, int stored_to, int len)
{
	t_vcars				*temp;

	if (*begin == NULL)
	{
		*begin = (t_vcars*)malloc(sizeof(t_vcars));
		(*begin)->c_pair = c_pair;
		(*begin)->stored_to = stored_to;
		if (len == 4)
			(*begin)->cycles = 49;
		else
			(*begin)->cycles = 50;
		(*begin)->len = len;
		(*begin)->next = NULL;
	}
	else
	{
		temp = *begin;
		while (temp->next)
			temp = temp->next;
		temp->next = (t_vcars*)malloc(sizeof(t_vcars));
		temp->next->c_pair = c_pair;
		temp->next->stored_to = stored_to;
		if (len == 4)
			temp->next->cycles = 49;
		else
			temp->next->cycles = 50;
		temp->next->len = len;
		temp->next->next = NULL;
	}
}

void			del_front_vcars(t_vcars **begin)
{
	t_vcars				*temp;

	if (*begin)
	{
		temp = (*begin)->next;
		free(*begin);
		*begin = temp;
	}
}

void			del_vcars(t_vcars **begin)
{
	t_vcars				*temp;

	while (*begin)
	{
		temp = (*begin)->next;
		free(*begin);
		*begin = temp;
	}
}
