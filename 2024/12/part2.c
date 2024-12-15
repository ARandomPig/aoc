/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/15 19:05:03 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "libft/libft.h"

typedef struct s_point
{
	int x;
	int y;
	struct s_point *next;
} t_point;

static char **create_locations(char **map, char fill)
{
	int width;
	int height;
	char **res;
	int i;

	height = 0;
	while(map[height])
		height++;
	width = 0;
	while(map[0][width])
		width++;
	res = malloc((height + 1) * sizeof(char *));	
	res[height] = 0;
	i = 0;
	while(i < height)
	{
		res[i] = malloc(width + 1);
		res[i][width] = 0;
		memset(res[i],fill, width);
		i++;
	}
	return(res);
}

char is_char(char **map, int y, int x, char c)
{
	int height;
	int width;

	height = 0;
	while(map[height])
		height++;
	width = 0;
	while(map[0][width])
		width++;
	if(y < 0 || x < 0 || y >= height || x >= width)
		return(0);
	return(map[y][x] == c);
	
}

static int is_counted(t_point *counted, int x, int y)
{
	while(counted)
	{
		if(counted->x == x && counted->y == y)
			return(1);
		counted = counted->next;
	}
	return(0);
}

static void add_point(t_point **strt, int x, int y)
{
	t_point *new;

	new = malloc(sizeof(t_point));
	new->x = x;
	new->y = y;
	new->next = *strt;
	*strt = new;
}

static int check_surroundings(char **map, int pos[2], char c, int reset)
{
	static t_point *counted;
	t_point *tmp;
	int res;
	int x;
	int y;

	if(reset)
	{
		while(counted)
		{
			tmp = counted->next;
			free(counted);
			counted = tmp;
		}
		return(0);
	}
	if(is_counted(counted, pos[1], pos[0]))
		return(0);
	y = pos[0];
	x = pos[1];
	res = 0;
	if((is_char(map, y, x - 1, c) && is_char(map, y - 1, x, c)) || (!is_char(map, y, x - 1, c) && !is_char(map, y - 1, x, c) && is_char(map, y - 1, x - 1, c)))
		res++;
	if((is_char(map, y, x + 1, c) && is_char(map, y - 1, x, c)) || (!is_char(map, y, x + 1, c) && !is_char(map, y - 1, x, c) && is_char(map, y - 1, x + 1, c)))
		res++;
	if((is_char(map, y, x + 1, c) && is_char(map, y + 1, x, c)) || (!is_char(map, y, x + 1, c) && !is_char(map, y + 1, x, c) && is_char(map, y + 1, x + 1, c)))
		res++;
	if((is_char(map, y, x - 1, c) && is_char(map, y + 1, x, c)) || (!is_char(map, y, x - 1, c) && !is_char(map, y + 1, x, c) && is_char(map, y + 1, x - 1, c)))
		res++;
	add_point(&counted, x, y);
	return(res);
}

static int get_area_perimetter(char **map, int pos[2], int perimetter, char **locations, char c, char **tmp)
{
	int res;

	if(perimetter && pos[0] >= 0 && pos[1] >= 0 && map[pos[0]] && map[pos[0]][pos[1]] && locations[pos[0]][pos[1]])
		return(0);
	if(pos[0] < 0 || pos[1] < 0 || !map[pos[0]] || map[pos[0]][pos[1]] != c)
	{
		if(perimetter)
			return(check_surroundings(map, pos, c, 0));
		else
			return(0);
	}
	res = 0;
	res += !perimetter && c == map[pos[0]][pos[1]];
	if(perimetter)
		locations[pos[0]][pos[1]] = 1;
	else
	{
		tmp[pos[0]][pos[1]] = c;
		map[pos[0]][pos[1]] = '.';
	}
	res += get_area_perimetter(map, (int [2]){pos[0] - 1, pos[1]}, perimetter, locations, c, tmp);
	res += get_area_perimetter(map, (int [2]){pos[0], pos[1] + 1}, perimetter, locations, c, tmp);
	res += get_area_perimetter(map, (int [2]){pos[0] + 1, pos[1]}, perimetter, locations, c, tmp);
	res += get_area_perimetter(map, (int [2]){pos[0], pos[1] - 1}, perimetter, locations, c, tmp);
	if(perimetter)
	{
		res += get_area_perimetter(map, (int [2]){pos[0] + 1, pos[1] - 1}, perimetter, locations, c, tmp);
		res += get_area_perimetter(map, (int [2]){pos[0] + 1, pos[1] + 1}, perimetter, locations, c, tmp);
		res += get_area_perimetter(map, (int [2]){pos[0] - 1, pos[1] - 1}, perimetter, locations, c, tmp);
		res += get_area_perimetter(map, (int [2]){pos[0] - 1, pos[1] + 1}, perimetter, locations, c, tmp);
	}
	return(res);
}

static long int calc_price(char **map, int x, int y)
{
	int area;
	int perimetter;
	char **locations;
	char **tmp;
	
	locations = create_locations(map, 0);
	tmp = create_locations(map, '.');
	area = get_area_perimetter(map,(int [2]){y, x}, 0, locations, map[y][x], tmp);
	perimetter = get_area_perimetter(tmp, (int [2]){y, x}, 1, locations, tmp[y][x], 0);
	check_surroundings(0, (int [2]){0, 0}, 0, 1);
	ft_free_str_arr(locations);
	ft_free_str_arr(tmp);
	return(area * perimetter);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	int i;
	int j;
	long int res;

	i = 0;
	res = 0;
	while(split[i])
	{
		j = 0;
		while(split[i][j])
		{
			if(split[i][j] != '.')
				res += calc_price(split, j, i);
			j++;
		}
		i++;
	}
	return(res);
}
