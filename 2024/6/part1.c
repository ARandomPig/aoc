/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/06 12:39:11 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct s_guard
{
	int pos[2];
	int dir[2];
} t_guard;

static void find_guard(char **split, int *x, int *y)
{
	char c;

	*y = 0;
	while(split[*y])
	{
		*x = 0;
		while(split[*y][*x])
		{
			c = split[*y][*x];
			if(c == '^' || c == '>' || c == 'v' || c == '<')
				return ;
			(*x)++;
		}
		(*y)++;
		
	}
}

static int is_on_map(char **map, int x, int y)
{
	return(y >= 0 && x >= 0 && map[y] && map[y][x]);
}

static void next_dir(int *dir)
{
	if(dir[0] == -1 && dir[1] == 0)
	{
		dir[0] = 0;
		dir[1] = 1;
	}
	else if(dir[0] == 0 && dir[1] == 1)
	{
		dir[0] = 1;
		dir[1] = 0;
	}
	else if(dir[0] == 1 && dir[1] == 0)
	{
		dir[0] = 0;
		dir[1] = -1;
	}
	else if(dir[0] == 0 && dir[1] == -1)
	{
		dir[0] = -1;
		dir[1] = 0;
	}
}

static void move(char **map, t_guard *guard)
{
	int nx;
	int ny;

	ny = guard->pos[0] + guard->dir[0];
	nx = guard->pos[1] + guard->dir[1];
	if(is_on_map(map, nx, ny) && map[ny][nx] == '#')
	{
		next_dir(guard->dir);
		move(map, guard);
		return ;
	}
	map[guard->pos[0]][guard->pos[1]] = 'X';
	guard->pos[0] = ny;
	guard->pos[1] = nx;
}

static long int count_char(char **map, char c)
{
	int x;
	int y;
	long int res;

	res = 0;
	y = 0;
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if(map[y][x] == c)
				res++;
			x++;
		}
		y++;
	}
	return(res);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	int x;
	int y;
	t_guard guard;
	long int res;

	find_guard(split, &x, &y);
	guard.pos[0] = y;
	guard.pos[1] = x;
	guard.dir[0] = (1 * (split[y][x] == 'v')) + (-1 * (split[y][x] == '^'));
	guard.dir[1] = (1 * (split[y][x] == '>')) + (-1 * (split[y][x] == '<'));
	while(is_on_map(split, guard.pos[1], guard.pos[0]))
		move(split, &guard);
	res = count_char(split, 'X');	
	return(res);
}
