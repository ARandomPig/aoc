/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/10 12:31:18 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static long int find_trails(char **map, int pos[2], char **locations)
{
	char c;
	long int res;

	c = map[pos[0]][pos[1]];
	res = 0;
	if(c == '9' && !locations[pos[0]][pos[1]])
	{
		locations[pos[0]][pos[1]] = 1;
		return(1);
	}
	if(map[pos[0] + 1] && map[pos[0] + 1][pos[1]] == c + 1)
		res += find_trails(map, (int [2]){pos[0] + 1, pos[1]}, locations);
	if(pos[0] - 1 >= 0 && map[pos[0] - 1][pos[1]] == c + 1)
		res += find_trails(map, (int [2]){pos[0] - 1, pos[1]}, locations);
	if(map[pos[0]][pos[1] + 1] && map[pos[0]][pos[1] + 1] == c + 1)
		res += find_trails(map, (int [2]){pos[0], pos[1] + 1}, locations);
	if(pos[1] - 1 >= 0 && map[pos[0]][pos[1] - 1] == c + 1)
		res += find_trails(map, (int [2]){pos[0], pos[1] - 1}, locations);
	return(res);	
}

static void reset_locations(char **locations, int height, int width)
{
	int i;

	i = 0;
	while(i < height)
	{
		ft_bzero(locations[i], width);
		i++;
	}
}

static char **create_map(char **split, int *height, int *width)
{
	char **res;

	*height = 0;
	*width = 0;
	while(split[*height])
		(*height)++;
	while(split[0][*width])
		(*width)++;
	res = malloc(*height * sizeof(char *));
	*height = 0;
	while(split[*height])
	{
		res[*height] = malloc(*width);
		(*height)++;
	}
	reset_locations(res, *height, *width);
	return(res);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	int i;
	int j;
	long int res;
	char **locations;
	int height;
	int width;

	locations = create_map(split, &height, &width);
	i = 0;
	res = 0;
	while(split[i])
	{
		j = 0;
		while(split[i][j])
		{
			if(split[i][j] == '0')
			{
				reset_locations(locations, height, width);
				res += find_trails(split, (int [2]){i, j}, locations);
			}
			j++;
		}
		i++;
	}
	return(res);
}
