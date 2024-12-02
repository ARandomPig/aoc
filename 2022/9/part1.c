/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/11/04 13:32:41 by tomoron          ###   ########.fr       */
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
		res.dir[1] = -1;
	if(line[0] == 'D')
		res.dir[1] = 1;
	if(line[0] == 'L')
		res.dir[0] = -1;
	if(line[0] == 'R')
		res.dir[0] = 1;
	res.rep = ft_atoi(line + 2);
	return(res);
}

static void move_tail(int tail[2], int head[2])
{
	int dist_up;
	int dist_side;

	dist_up = tail[0] - head[0];
	dist_side = tail[1] - head[1];
	if(dist_up == -2)
		tail[0] = head[0] - 1;
	if(dist_up == 2)
		tail[0] = head[0] + 1;
	if(dist_side == -2)
		tail[1] = head[1] - 1;
	if(dist_side == 2)
		tail[1] = head[1] + 1;
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	int i;
	int head[2];
	int tail[2];
	t_instruction instr;

	i = 0;
	ft_bzero(head, sizeof(int) * 2);
	ft_bzero(tail, sizeof(int) * 2);
	while(split[i])
	{
		instr = get_instruction(split[i]);
		while(instr.rep > 0)
		{
			head[0] += instr.dir[0];
			head[1] += instr.dir[1];
			printf("%d, %d\n", head[0], head[1]);
			move_tail(tail, head);
			instr.rep--;
		}
		i++;
	}
	return(0);
}
