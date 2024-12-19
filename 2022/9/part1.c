/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/19 18:17:10 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libft/libft.h"
#include "structs.h"

t_instruction get_instruction(char *line)
{
	t_instruction res;
	
	res.dir[0] = 0;
	res.dir[1] = 0;
	res.rep = 0;
	if(!line[0])
		return(res);

	if(line[0] == 'U')
		res.dir[0] = -1;
	if(line[0] == 'D')
		res.dir[0] = 1;
	if(line[0] == 'L')
		res.dir[1] = -1;
	if(line[0] == 'R')
		res.dir[1] = 1;
	res.rep = ft_atoi(line + 2);
	return(res);
}

static void move_tail(int tail[2], int head[2])
{
	float dist;

	dist = sqrt(pow(tail[0] - head[0], 2) + pow(tail[1] - head[1], 2));
	if(dist < 1.5)
		return;
	if(tail[0] < head[0])
		tail[0]++;
	else if(tail[0] > head[0])
		tail[0]--;
	if(tail[1] < head[1])
		tail[1]++;
	else if(tail[1] > head[1])
		tail[1]--;
	dist = sqrt(pow(tail[0] - head[0], 2) + pow(tail[1] - head[1], 2));
}

static void add_pos(t_pos **lst, int *pos)
{
	t_pos *tmp;
	t_pos *last;

	tmp = *lst;
	last = 0;
	while(tmp)
	{
		if(tmp->pos[0] == pos[0] && tmp->pos[1] == pos[1])
			return;
		last = tmp;
		tmp = tmp->next;
	}
	tmp = malloc(sizeof(t_pos));
	tmp->pos[0] = pos[0];
	tmp->pos[1] = pos[1];
	tmp->next = 0;
	if(!last)
		*lst = tmp;
	else
		last->next = tmp;
}

static long int len_pos(t_pos *lst)
{
	long int res;

	res = 0;
	while(lst)
	{
		res++;
		lst = lst->next;
	}
	return(res);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	int i;
	int head[2];
	int tail[2];
	t_instruction instr;
	t_pos *lst;
	t_pos *tmp;
	long int res;

	i = 0;
	ft_bzero(head, sizeof(int) * 2);
	ft_bzero(tail, sizeof(int) * 2);
	lst = 0;
	while(split[i])
	{
		instr = get_instruction(split[i]);
		while(instr.rep > 0)
		{
			add_pos(&lst, tail);
			head[0] += instr.dir[0];
			head[1] += instr.dir[1];
			move_tail(tail, head);
			instr.rep--;
		}
		i++;
	}
	add_pos(&lst, tail);
	res = len_pos(lst);
	while(lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	return(res);
}
