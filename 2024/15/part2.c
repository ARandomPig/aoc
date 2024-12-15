/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/15 15:06:58 by tomoron          ###   ########.fr       */
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

static int move(char **map, int dir[2], int pos[2], char c, int check)
{
	int np[2];

	np[0] = pos[0] + dir[0];
	np[1] = pos[1] + dir[1];
	if(map[np[0]][np[1]] == '#')
		return(0);
	if(map[np[0]][np[1]] == '.')
	{
		if(!check)
		{
			map[np[0]][np[1]] = c;
			map[pos[0]][pos[1]] = '.';
		}
		return(1);
	}
	if((map[np[0]][np[1]] == ']'
				&& move(map, dir, (int [2]){np[0], np[1] - 1},'[', check)
				&& ((dir[1] == -1 && check)  || move(map, dir, np, ']', check)))
			|| (map[np[0]][np[1]] == '['
				&& move(map, dir, (int [2]){np[0], np[1] + 1},']', check)
				&& ((dir[1] == 1 && check) || move(map, dir, np, '[', check)))
		)
	{
		if(!check)
		{
			map[np[0]][np[1]] = c;
			map[pos[0]][pos[1]] = '.';
		}
		return(1);
	}
	return(0);
}

static long int calc_score(char **map)
{
	int i;
	int j;
	long int res;

	i = 0;
	res = 0;
	while(map[i] && map[i][0] == '#')
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == '[')
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
		if(move(map, dir, (int [2]){robot->y, robot->x}, map[robot->y][robot->x], 1))
		{
			move(map, dir, (int [2]){robot->y, robot->x}, map[robot->y][robot->x], 0);
			robot->y += dir[0];
			robot->x += dir[1];
		}
		line++;
	}
}

void enlarge_line(char *src, char *dest)
{
	int i;

	i = 0;
	while(*src)
	{
		if(*src == '#')
		{
			dest[i] = '#';
			dest[i + 1] = '#';
		}
		if(*src == 'O')
		{
			dest[i] = '[';
			dest[i + 1] = ']';
		}
		if(*src == '@')
		{
			dest[i] = '@';
			dest[i + 1] = '.';
		}
		if(*src == '.')
		{
			dest[i] = '.';
			dest[i + 1] = '.';
		}
		src++;
		i += 2;
	}
}

char **enlarge_map(char **map)
{
	char **res;
	int width;
	int height;
	int i;

	height = 0;
	while(map[height][0] == '#')
		height++;
	width = 0;
	while(map[0][width])
		width++;
	width *= 2;
	res = malloc((height + 1) * sizeof(char *));
	res[height] = 0;
	i = 0;
	while(i < height)
	{
		res[i] = malloc(width + 1);
		res[i][width] = 0;
		enlarge_line(map[i], res[i]);
		i++;
	}
	return(res);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	long int res;
	t_robot robot;	
	char **instr;

	instr = split;

	while(**instr == '#')
		instr++;
	split = enlarge_map(split);
	robot = get_robot(split);
	while(*instr)
	{
		exec_line(split, *instr, &robot);
		instr++;
	}
	res = calc_score(split);
	return(res);
}
