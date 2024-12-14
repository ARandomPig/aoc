/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/14 15:16:48 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "mlx/mlx.h"
#include "libft/libft.h"

#define MAX_UP 103
#define MAX_LEN 101
#define ROBOT_SIZE 8

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

static char **create_map(void)
{
	char **res;
	int i;

	res = malloc((MAX_UP + 2) * sizeof(char *));
	res[MAX_UP + 1] = 0;
	i = 0;
	while(i < MAX_UP + 1)
	{
		res[i] = malloc(MAX_LEN + 2);
		i++;
	}
	return(res);	
}

void set_pos(unsigned int *img, unsigned long pos, unsigned int color)
{
	int i;
	int j;

	i = 0;
	while(i < ROBOT_SIZE)
	{
		j = 0;
		while(j < ROBOT_SIZE)
		{
			img[pos + (i * MAX_LEN * ROBOT_SIZE) + j] = color;
			j++;
		}
		i++;
	}
}

void fill_map(void *img, t_robot *robot)
{
	unsigned long pos;
	int a;

	img = mlx_get_data_addr(img,&a, &a, &a);
	bzero(img, (MAX_LEN * ROBOT_SIZE) * (MAX_UP * ROBOT_SIZE) * sizeof(unsigned int));
	while(robot)
	{
		pos = robot->pos_x * ROBOT_SIZE + (robot->pos_y * (MAX_LEN * ROBOT_SIZE) * ROBOT_SIZE);
		set_pos(img, pos, 0xFFFFFF);
		robot = robot->next;
	}
}

static int loop_fnc(t_data *data)
{
	fill_map(data->img, data->robot);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0 ,0);
	printf("res : %d\n", data->res);
	update_pos(data->robot);
	data->res++;
	usleep(20000);
	return(0);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	t_robot *robot;
	long int res;
	t_data data;

	robot = 0;
	res = 0;
	while(*split)
	{
		add_robot(&robot, *split);
		split++;
	}
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, MAX_LEN * ROBOT_SIZE, MAX_UP * ROBOT_SIZE, "language : eyes");
	data.img = mlx_new_image(data.mlx, MAX_LEN * ROBOT_SIZE, MAX_UP * ROBOT_SIZE);
	data.robot = robot;
	data.res = 0;
	mlx_loop_hook(data.mlx, loop_fnc, &data);
	mlx_loop(data.mlx);
	while(1)
		;;
//	fill_show_map(map, robot);
	(void)get_result;
	(void)create_map;
	(void)update_pos;
	return(res);
}
