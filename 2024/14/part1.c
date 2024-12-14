/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/14 12:59:57 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
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
		robot->pos_x = (robot->pos_x + (robot->vel_x * 100));
		robot->pos_y = (robot->pos_y + (robot->vel_y * 100));
		robot->pos_x %= MAX_LEN;
		robot->pos_y %= MAX_UP;
		if(robot->pos_x < 0)
			robot->pos_x += MAX_LEN;
		if(robot->pos_y < 0)
			robot->pos_y += MAX_UP;
		robot = robot->next;
	}
}

static long int get_result(t_robot *robot)
{
	long int tiles[4];

	bzero(tiles, 4 * sizeof(long int));
	while(robot)
	{
		robot->pos_x -= (MAX_LEN / 2);
		robot->pos_y -= (MAX_UP / 2);
		if(robot->pos_x < 0 && robot->pos_y < 0)
			tiles[0]++;
		else if(robot->pos_x > 0 && robot->pos_y < 0)
			tiles[1]++;
		else if(robot->pos_x < 0 && robot->pos_y > 0)
			tiles[2]++;
		else if(robot->pos_x > 0 && robot->pos_y > 0)
			tiles[3]++;
		robot = robot->next;
	}
	return(tiles[0] * tiles[1] * tiles[2] * tiles[3]);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	t_robot *robot;
	long int res;

	robot = 0;
	res = 0;
	while(*split)
	{
		add_robot(&robot, *split);
		split++;
	}
	update_pos(robot);
	res = get_result(robot);
	return(res);
}
