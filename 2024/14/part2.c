/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/14 16:20:20 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "libft/libft.h"

#define MAX_UP 103
#define MAX_LEN 101

typedef struct s_robot
{
	int pos_x;
	int pos_y;
	int vel_x;
	int vel_y;
	struct s_robot *next;
}	t_robot;

typedef struct s_data
{
	void *mlx;
	void *win;
	void *img;
	t_robot *robot;
	int res;
}	t_data;

static void add_robot(t_robot **robot, char *line)
{
	t_robot *new;

	new = malloc(sizeof(t_robot));
	while(*line && !ft_isdigit(*line) && *line != '-')
		line++;
	new->pos_x = atoi(line);
	while(ft_isdigit(*line) || *line == '-')
		line++;
	line++;
	new->pos_y = atoi(line);
	while(ft_isdigit(*line))
		line++;

	while(*line && !ft_isdigit(*line) && *line != '-')
		line++;
	new->vel_x = atoi(line);
	while(ft_isdigit(*line) || *line == '-')
		line++;
	line++;
	new->vel_y = atoi(line);
	while(ft_isdigit(*line))
		line++;
	new->next = *robot;
	*robot = new;
}

static void update_pos(t_robot *robot)
{
	while(robot)
	{
		robot->pos_x = (robot->pos_x + (robot->vel_x));
		robot->pos_y = (robot->pos_y + (robot->vel_y));
		robot->pos_x %= MAX_LEN;
		robot->pos_y %= MAX_UP;
		if(robot->pos_x < 0)
			robot->pos_x += MAX_LEN;
		if(robot->pos_y < 0)
			robot->pos_y += MAX_UP;
		robot = robot->next;
	}
}

static char **create_map(char fill)
{
	char **res;
	int i;

	res = malloc((MAX_UP + 2) * sizeof(char *));
	res[MAX_UP + 1] = 0;
	i = 0;
	while(i < MAX_UP + 1)
	{
		res[i] = malloc(MAX_LEN + 2);
		memset(res[i], fill, MAX_LEN + 1);
		res[i][MAX_LEN + 1] = 0;
		i++;
	}
	return(res);	
}

void fill_map(char **map, t_robot *robot)
{
	int i;

	i = 0;
	while(map[i])
	{
		memset(map[i], '.', MAX_LEN + 1);
		map[i][MAX_LEN + 1] = 0;
		i++;
	}
	while(robot)
	{
		map[robot->pos_y][robot->pos_x] = '#';
		robot = robot->next;
	}
}

static int count_area(char **map, int pos[2], char **locations)
{
	int res;

	res = 0;
	if(pos[0] < 0 || pos[1] < 0 || !map[pos[0]] || !map[pos[0]][pos[1]] || locations[pos[0]][pos[1]] != '.' || map[pos[0]][pos[1]] != '#')
		return(0);
	locations[pos[0]][pos[1]] = '#';
	res += count_area(map, (int [2]){pos[0] + 1, pos[1]}, locations);
	res += count_area(map, (int [2]){pos[0] - 1, pos[1]}, locations);
	res += count_area(map, (int [2]){pos[0], pos[1] + 1}, locations);
	res += count_area(map, (int [2]){pos[0], pos[1] - 1}, locations);
	return(res + (map[pos[0]][pos[1]] == '#'));
}

static int is_easter_egg(char **map)
{
	int i;
	int j;
	char **locations;

	locations = create_map('.');
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(count_area(map, (int [2]){i, j}, locations) > 50)
				return(1);
			j++;
		}
		i++;
	}
	ft_free_str_arr(locations);
	return(0);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	t_robot *robot;
	long int res;
	char **map;

	robot = 0;
	res = 0;
	while(*split)
	{
		add_robot(&robot, *split);
		split++;
	}
	map = create_map('.');
	fill_map(map,robot);
	while(!is_easter_egg(map))
	{
		update_pos(robot);
		res++;
		fill_map(map,robot);
	}
	return(res);
}
