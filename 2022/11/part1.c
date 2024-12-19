/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/19 23:22:50 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef enum e_op
{
	MUL,
	ADD,
	SQR
} t_op;

typedef struct s_items
{
	int	value;
	struct s_items *next;
}	t_items;

typedef struct s_monkey
{
	t_items *items;
	t_op op;
	int op_nb;
	int test_div;
	int to_true;
	int to_false;
	long int nb_inspect;
}	t_monkey;

static int count_monkeys(char **split)
{
	int len;

	len = 0;
	while(*split)
	{
		if(**split == 'M')
			len++;
		split++;
	}
	return(len);
}

static t_items *get_items(char *line)
{
	t_items *res;
	t_items *new;
	t_items *last;

	last = 0;
	res = 0;
	while(*line)
	{
		new = malloc(sizeof(t_items));
		while(*line && !ft_isdigit(*line))
			line++;
		new->value = ft_atoi(line);
		new->next = 0;
		if(!last)
			res = new;	
		else
			last->next = new;
		last = new;
		while(ft_isdigit(*line))
			line++;
	}
	return(res);
}

static void get_op(t_monkey *monkey, char *line)
{
	while(*line && *line != '*' && *line != '+')
		line++;
	if(!*line)
		exit(1);
	if(!ft_strcmp(line, "* old"))
	{
		monkey->op = SQR;
		monkey->op_nb = 0;
		return ;
	}
	if(*line == '*')
		monkey->op = MUL;
	else
		monkey->op = ADD;
	line++;
	monkey->op_nb = ft_atoi(line);
}

static int get_first_nb(char *line)
{
	while(*line && !ft_isdigit(*line))
		line++;
	return(ft_atoi(line));
}

static t_monkey *get_monkeys(char **split, int *len)
{
	t_monkey *res;
	int i;

	*len = count_monkeys(split);
	res = malloc(*len * sizeof(t_monkey));
	i = 0;
	while(*split)
	{
		split++;
		res[i].items = get_items(*split);
		split++;
		get_op(res + i, *split);
		split++;
		res[i].test_div = get_first_nb(*split);
		split++;
		res[i].to_true = get_first_nb(*split);
		split++;
		res[i].to_false = get_first_nb(*split);
		split++;
		i++;
	}
	return(res);
}

void give_item(t_monkey *from, t_monkey *to)
{
	t_items *item;
	t_items *dest;

	item = from->items;
	from->items = item->next;
	item->next = 0;
	if(!to->items)
		to->items = item;
	else
	{
		dest = to->items;
		while(dest->next)
			dest = dest->next;
		dest->next = item;
	}

}

void handle_items(t_monkey *monkeys, t_monkey *cur)
{
	while(cur->items)
	{
		cur->nb_inspect++;
		if(cur->op == MUL)
			cur->items->value *= cur->op_nb;
		else if(cur->op == ADD)
			cur->items->value += cur->op_nb;
		else if(cur->op == SQR)
			cur->items->value *= cur->items->value;
		cur->items->value /= 3;
		if(cur->items->value % cur->test_div == 0)
			give_item(cur, monkeys + cur->to_true);
		else
			give_item(cur, monkeys + cur->to_false);
	}
}

static void loop_all_monkeys(t_monkey *monkeys, int nb_monkey)
{
	int i = 0;

	while(i < nb_monkey)
	{
		handle_items(monkeys, monkeys + i);
		i++;
	}
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	int nb_monkey;
	int i;
	long int top[2];
	t_monkey *monkeys;

	monkeys = get_monkeys(split, &nb_monkey);
	i = 0;
	while(i < 20)
	{
		loop_all_monkeys(monkeys, nb_monkey);
		i++;
	}
	top[0] = 0;
	top[1] = 0;
	i = 0;
	while(i < nb_monkey)
	{
		if(monkeys[i].nb_inspect > top[0])
		{
			top[1] = top[0];
			top[0] = monkeys[i].nb_inspect;
		}
		else if(monkeys[i].nb_inspect > top[1])
			top[1] = monkeys[i].nb_inspect;
		i++;
	}
	return(top[0] * top[1]);
}
