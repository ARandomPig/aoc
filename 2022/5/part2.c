/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/10/29 02:54:08 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft/libft.h"
#include "structs.h"

static t_stack_list *get_next_stack_node(t_stack_list **stacks, t_stack_list *cur)
{
	if(!*stacks)
		*stacks = ft_calloc(1, sizeof(t_stack_list));
	if(!cur)
		return(*stacks);
	if(!cur->next)
		cur->next = ft_calloc(1, sizeof(t_stack_list));
	return(cur->next);
}

static void add_crate(t_stack_list *node, char letter)
{
	t_crate *bottom;
	t_crate *tmp;

	bottom = node->crate;
	while(bottom && bottom->prev)
		bottom = bottom->prev;

	tmp = ft_calloc(1, sizeof(t_crate));
	tmp->letter = letter;
	tmp->prev = 0;

	if(bottom)
		bottom->prev = tmp;
	else
		node->crate = tmp;
}

static void get_line_crates(char *line, t_stack_list **stacks)
{
	int i;
	int len;
	t_stack_list *cur;

	i = 1;
	len = ft_strlen(line);
	cur = get_next_stack_node(stacks, 0);
	while(i < len)
	{
		if(line[i] >= 'A' && line[i] <= 'Z')
			add_crate(cur, line[i]);
		i += 4;
		cur = get_next_stack_node(stacks, cur);
	}
}

static t_stack_list *parse_input_stacks(char **split)
{
	t_stack_list *stacks;
	int i;

	i = 0;
	stacks = 0;
	while(split[i] && ft_strlen(split[i]) > 2 && !(split[i][1] >= '0' && split[i][1] <= '9'))
	{
		get_line_crates(split[i], &stacks);
		i++;
	}
	return(stacks);
}

static t_instruction parse_instruction(char *line)
{
	t_instruction res;

	res.nb = 1;
	res.from = 1;
	res.to = 1;
	if(line && ft_strlen(line) >= 18)
	{
		line += 5;
		res.nb = ft_atoi(line);
		while(*line >= '0' && *line <='9')
			line++;
		line += 6;
		res.from = ft_atoi(line);
		while(*line >= '0' && *line <='9')
			line++;
		line += 4;
		res.to = ft_atoi(line);
	}
	return(res);
}

static t_stack_list *stack_from_index(t_stack_list *stacks, int index)
{
	int i;

	i = 1;
	while(stacks->next && i < index)
	{
		stacks = stacks->next;
		i++;
	}
	return(stacks);
}

static void print_stack(t_stack_list *stack)
{
	if(!stack->crate)
		return;
	printf("%c", stack->crate->letter);
	return;
	t_crate *tmp;

	tmp = stack->crate;
	while(tmp)
	{
		printf("%c",tmp->letter);
		tmp = tmp->prev;
	}
	printf("\n");
}

static void print_result(t_stack_list *stacks)
{
	while(stacks)
	{
		print_stack(stacks);
		stacks = stacks->next;
	}
	printf("\n");
}

static void exec_instruction(int rep, t_stack_list *from, t_stack_list *to)
{
	int i;
	t_crate *tmp;
	t_crate *top;

	i = 1;
	top = from->crate;
	tmp = top;
	while(i < rep && tmp->prev)
	{
		tmp = tmp->prev;
		i++;
	}
	from->crate = tmp->prev;
	tmp->prev = to->crate;
	to->crate = top;
}

static void do_all_instructions(char **split,t_stack_list *stacks)
{
	int i;
	t_instruction instr;

	(void)stacks;
	i = 0;
	while(split[i] && (split[i][0] == ' ' || split[i][0] == '['))
		i++;
	while(split[i])
	{
		instr = parse_instruction(split[i]);
		exec_instruction(instr.nb, stack_from_index(stacks, instr.from), stack_from_index(stacks, instr.to));
		i++;
	}
}

static void free_stacks(t_stack_list *stacks)
{
	void *tmp;

	while(stacks)
	{
		while(stacks->crate)
		{
			tmp = stacks->crate->prev;
			free(stacks->crate);
			stacks->crate = tmp;
		}
		tmp = stacks->next;
		free(stacks);
		stacks = tmp;
	}
}


long int resolve_part2(char *input, char **split)
{
	(void)input;
	(void)split;
	t_stack_list *stacks;

	stacks = parse_input_stacks(split);
	do_all_instructions(split, stacks);
	print_result(stacks);
	free_stacks(stacks);
	return(0);
}
