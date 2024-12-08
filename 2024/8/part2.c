/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/08 13:37:39 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static long int get_nb_antinode_char(char **map, char **locations, int limits[2], int ref_pos[2])
{
	char c;
	long int res;
	int pos[2];
	int np[2];
	int diff[2];

	res = 0;
	c = map[ref_pos[0]][ref_pos[1]];
	pos[0] = 0;
	while(map[pos[0]])
	{
		pos[1] = 0;
		while(map[pos[0]][pos[1]])
		{
			if(ref_pos[0] != pos[0] && ref_pos[1] != pos[1] && map[pos[0]][pos[1]] == c)
			{
				diff[0] = pos[0] - ref_pos[0];
				diff[1] = pos[1] - ref_pos[1];
				np[0] = ref_pos[0];
				np[1] = ref_pos[1];
				while(np[0] >= 0 && np[0] < limits[0] && np[1] >= 0 && np[1] < limits[1])
				{
					if(locations[np[0]][np[1]] != '#')
						res++;
					locations[np[0]][np[1]] = '#';
					np[0] -= diff[0];
					np[1] -= diff[1];
				}
				np[0] = pos[0];
				np[1] = pos[1];
				while(np[0] >= 0 && np[0] < limits[0] && np[1] >= 0 && np[1] < limits[1])
				{
					if(locations[np[0]][np[1]] != '#')
						res++;
					locations[np[0]][np[1]] = '#';
					np[0] += diff[0];
					np[1] += diff[1];
				}
			}
			pos[1]++;
		}
		pos[0]++;
	}
	map[ref_pos[0]][ref_pos[1]] = '.';
	return(res);
}

static long int find_antinode(char **map, int height, int width)
{
	int x;
	int y;
	long int res;
	char **locations;

	y = 0;
	res = 0;
	locations = malloc(height * sizeof(char *));
	while(y < height)
	{
		locations[y] = malloc(width);
		ft_memset(locations[y], '.', width);
		y++;
	}
	y = 0;
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if(map[y][x] != '.') 
				res += get_nb_antinode_char(map, locations, (int [2]){height, width}, (int [2]){y, x});
			x++;
		}
		y++;
	}
	y = 0;
	while(y < height)
	{
		free(locations[y]);
		y++;
	}
	free(locations);
	return(res);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	int height;
	int width;
	long int res;

	height = 0;
	while(split[height])
		height++;
	width = 0;
	while(split[0][width])
		width++;
	res = find_antinode(split, height, width);
	return(res);
}
