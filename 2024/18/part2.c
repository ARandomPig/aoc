/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/18 14:19:27 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft/libft.h"

typedef struct s_pos
{
	int x;
	int y;
} t_pos;

typedef struct s_lst
{
	t_pos			pos;
	uint32_t		score;
	int				dir[2];
	struct s_lst	*next;
}	t_lst;

static void *create_map(char **map, uint8_t fill, int bloc_size)
{
	int width;
	int height;
	int i;
	void **res;

	height = 0;
	while(map[height])
		height++;
	width = 0;
	while(map[0][width])
		width++;
	res = malloc((height + 1) * sizeof(void *));	
	i = 0;
	while(i < height)
	{
		res[i] = malloc((width + 1) * bloc_size);
		ft_memset(res[i], fill, width * bloc_size);
		((char **)res)[i][width * bloc_size] = 0;
		i++;
	}
	return(res);
}

static int get_new_pos(t_lst **lst, char **vis, t_pos *pos, uint32_t *score, int *dir)
{
	t_lst *cur;
	t_lst *sel;
	t_lst *p_sel;
	t_lst *prev;
	uint32_t min;

	if(!*lst)
		return(0);
	cur = *lst;
	sel = 0;
	p_sel = 0;
	prev = 0;
	min = -1;
	while(cur)
	{
		if(cur->score < min)	
		{
			sel = cur;
			p_sel = prev;
			min = cur->score;
		}
		prev = cur;
		cur = cur->next;
	}
	if(*lst && sel == *lst)
		*lst = (*lst)->next;
	if(p_sel)
		p_sel->next = sel->next;
	sel->next = 0;
	*score = sel->score;
	pos->x = sel->pos.x;
	pos->y = sel->pos.y;
	dir[0] = sel->dir[0];
	dir[1] = sel->dir[1];
	free(sel);
	if(vis[pos->y][pos->x])
		return(get_new_pos(lst, vis, pos, score, dir));
	return(1);
}

static void add_lst(t_lst **lst, uint32_t score, t_pos pos, int dir[2])
{
	t_lst *new;
	
	new = malloc(sizeof(t_lst));
	new->dir[0] = dir[0];
	new->dir[1] = dir[1];
	new->pos.x = pos.x;
	new->pos.y = pos.y;
	new->score = score;
	new->next = *lst;
	*lst = new;
}

static int	*rotate_dir(int dir[2], int inv, int *res)
{
	res[0] = 0;
	res[1] = 0;
	if(dir[0])	
		res[1] = dir[0];	
	if(dir[1])
		res[0] = dir[1];
	if(inv)
	{
		res[0] = -res[0];
		res[1] = -res[1];
	}
	return(res);
}

static int is_valid_move(char **map, int y, int x)
{
	return(x >= 0 && y >= 0 && map[y] && map[y][x] == '.');
}

static uint32_t dijkstra(char **map, t_pos *pos, int corner)
{
	int dir[2];
	int tmp[2];
	char **visited;
	uint32_t **dists;
	t_lst *lst;
	uint32_t score;

	visited = create_map(map, 0, 1);
	dists = create_map(map, 255, sizeof(uint32_t));
	lst = 0;
	add_lst(&lst, 0, *pos, (int [2]){0, 1});
	while(get_new_pos(&lst, visited, pos, &score, dir))
	{
		if(dists[pos->y][pos->x] > score)
			dists[pos->y][pos->x] = score;
		visited[pos->y][pos->x] = 1;
		if(map[pos->y][pos->x] == '#')
			continue;
		if(is_valid_move(map, pos->y + dir[0], pos->x + dir[1]))
			add_lst(&lst, score + 1, (t_pos){pos->x + dir[1], pos->y + dir[0]}, dir);
		rotate_dir(dir, 0, tmp);
		if(is_valid_move(map, pos->y + tmp[0], pos->x + tmp[1]))
			add_lst(&lst, score + 1, (t_pos){pos->x + tmp[1], pos->y + tmp[0]}, tmp);
		rotate_dir(dir, 1, tmp);
		if(is_valid_move(map, pos->y + tmp[0], pos->x + tmp[1]))
			add_lst(&lst, score + 1, (t_pos){pos->x + tmp[1], pos->y + tmp[0]}, tmp);
	}
	if(dists[corner][corner] != (uint32_t) -1)
		return(dists[corner][corner]);
	return(0);
}

static char **create_map_size(int size, char fill)
{
	int i;
	char **res;

	res = malloc((size + 1) * sizeof(char *));
	res[size] = 0;
	i = 0;
	while(i < size)
	{
		res[i] = malloc(size + 1);
		res[i][size] = 0;
		ft_memset(res[i], fill, size);
		i++;
	}
	return(res);
}

static void get_nbrs(char *line, int *x, int *y)
{
	while(*line && !ft_isdigit(*line))
		line++;
	*x = ft_atoi(line);
	while(ft_isdigit(*line))
		line++;
	while(*line && !ft_isdigit(*line))
		line++;
	*y = ft_atoi(line);
}

long int resolve_part2(char *input, char **split)
{
	char **map;
	(void)input;
	int x;
	int y;
	int i;

	map = create_map_size(71, '.');
	(void)map;
	i = 1024;
	while(split[i])
	{
		get_nbrs(split[i], &x, &y);
		map[y][x] = '#';
		if(dijkstra(map,&((t_pos){0, 0}), 70) == 0)
		{
			printf("real res : %d,%d\n", x, y);
			return(i);
		}
		i++;
	}
	return(-1);
}
