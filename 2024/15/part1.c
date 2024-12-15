/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/15 14:45:04 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct s_robot
{
	int x;
	int y;
}	t_robot;

static t_robot get_robot(char **map)
{
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == '@')	
			{
				map[i][j] = '.';	
				return((t_robot){j, i});
			}
			j++;
		}
		i++;
	}
	return((t_robot){0, 0});
}

static void try_move(char **map, int dir[2], t_robot *robot)
{
	int i;
	int j;

	i = robot->y + dir[0];
	j = robot->x + dir[1];
	while(map[i][j] == 'O')
	{
		i += dir[0];	
		j += dir[1];
	}
	if(map[i][j] == '#')
		return;
	robot->y += dir[0];
	robot->x += dir[1];
	if(map[robot->y][robot->x] == 'O')
	{
		map[robot->y][robot->x] = '.';
		map[i][j] = 'O';
	}
}

static long int calc_score(char **map)
{
	int i;
	int j;
	long int res;

	i = 0;
	res = 0;
	while(map[i][0] == '#')
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'O')
				res += (100 * i) + j;
			j++;	
		}
		i++;
	}
	return(res);
}

static void exec_line(char **map, char *line, t_robot *robot)
{
	int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	int *dir;
	while(*line)
	{
		switch(*line)
		{
			case '^':
				dir = dirs[0];
				break;
			case 'v':
				dir = dirs[1];
				break;
			case '<':
				dir = dirs[2];
				break;
			default:
				dir = dirs[3];
				break;
		}
		try_move(map, dir, robot);
		line++;
	}
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	long int res;
	t_robot robot;	
	char **instr;

	instr = split;
	while(**instr == '#')
		instr++;
	robot = get_robot(split);
	while(*instr)
	{
		exec_line(split, *instr, &robot);
		instr++;
	}
	res = calc_score(split);
	return(res);
}
