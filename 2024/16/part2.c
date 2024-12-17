/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/17 15:34:55 by tomoron          ###   ########.fr       */
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
	t_pos			from;
	uint32_t		score;
	int				dir[2];
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_lst;

typedef struct s_pos_lst
{
	int x;
	int y;
	uint32_t score;
	struct s_pos_lst *next;
} t_pos_lst;


static void get_char(char **map, t_pos *pos, char c)
{
	pos->y = 0;
	while(map[pos->y])
	{
		pos->x = 0;
		while(map[pos->y][pos->x])
		{
			if(map[pos->y][pos->x] == c)
				return;
			pos->x++;
		}
		pos->y++;
	}
}

static char dir_to_bit(int *dir)
{
	if(dir[1] == 1)
		return(0b1);
	if(dir[1] == -1)
		return(0b10);
	if(dir[0] == 1)
		return(0b100);
	if(dir[0] == -1)
		return(0b1000);
	return(0);
}

static int get_new_pos(t_lst **lst, char **vis, t_pos *pos, uint32_t *score, int *dir, t_pos *from)
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
	from->x = sel->from.x;
	from->y = sel->from.y;
	free(sel);
	if(vis[pos->y][pos->x] & (dir_to_bit(dir)))
		return(get_new_pos(lst, vis, pos, score, dir, from));
	return(1);
}

static void add_lst(t_lst **lst, uint32_t score, t_pos pos, int dir[2], t_pos *from)
{
	t_lst *new;
	
	new = malloc(sizeof(t_lst));
	new->dir[0] = dir[0];
	new->dir[1] = dir[1];
	new->pos.x = pos.x;
	new->pos.y = pos.y;
	new->score = score;
	new->next = *lst;
	if(from)
	{
		new->from.x = from->x;
		new->from.y = from->y;
	}
	else
	{
		new->from.x = -1;
		new->from.y = -1;
	}
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

static void add_path(t_pos_lst **path, t_pos pos, uint32_t score)
{
	t_pos_lst *new;
	t_pos_lst *tmp;
	
	if(*path && (*path)->score > score)
		*path = 0;
	tmp = *path;
	while(tmp)
	{
		if(tmp->x == pos.x && tmp->y == pos.y)
			return;
		tmp = tmp->next;
	}
//	if(*path && (*path)->score < score)
//		return ;
	new = malloc(sizeof(t_pos_lst));
	new->score = score;
	new->x = pos.x;
	new->y = pos.y;
	new->next = *path;
	*path = new;
}

static uint32_t dijkstra(char **map, t_pos *pos, char **visited, t_pos_lst ***path)
{
	int dir[2];
	int tmp[2];
	t_lst *lst;
	t_pos from;
	uint32_t score;
	uint32_t min_score;

	lst = 0;
	min_score = -1;
	add_lst(&lst, 0, *pos, (int [2]){0, 1}, 0);
	while(get_new_pos(&lst, visited, pos, &score, dir, &from))
	{
		visited[pos->y][pos->x] |= dir_to_bit(dir);
		if(map[pos->y][pos->x] == '#')
			continue;
		if(map[pos->y][pos->x] == 'E' && min_score > score)
			min_score = score;
		if(from.x != -1 && from.y != -1)
			add_path(path[pos->y] + pos->x, from, score);
		if(map[pos->y + dir[0]][pos->x + dir[1]] != '#')
			add_lst(&lst, score + 1, (t_pos){pos->x + dir[1], pos->y + dir[0]}, dir, pos);
		rotate_dir(dir, 0, tmp);
		if(map[pos->y + tmp[0]][pos->x + tmp[1]] != '#')
			add_lst(&lst, score + 1000, *pos, tmp, &from);
		rotate_dir(dir, 1, tmp);
		if(map[pos->y + tmp[0]][pos->x + tmp[1]] != '#')
			add_lst(&lst, score + 1000, *pos, tmp, &from);
	}
	return (min_score);
}

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

static int fill_path_map(t_pos_lst ***path, int x, int y, char **map, uint32_t score)
{
	t_pos_lst *cur;
	int res;

	res = 0;

	cur = path[y][x];
	if(map[y][x] == 'S')
		return(1);
	while(cur)
	{
		if(cur->score <= score)
			res += fill_path_map(path, cur->x, cur->y, map, cur->score);
		cur = cur->next;
	}
	if(res)
		map[y][x] = 'O';
	return(res);
}

long int get_result(t_pos_lst ***path, t_pos pos, char **map, uint32_t score)
{
	long int res;
	int i;
	int j;

	res = 0;
	fill_path_map(path, pos.x, pos.y, map, score);	
	i = 0;
	while(map[i])
	{
		printf("%s\n", map[i]);
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'O')
				res++;
			j++;
		}
		i++;
	}	
	return(res + 1);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	t_pos pos;
	t_pos_lst ***path;
	char **visited;
	uint32_t score;
	long int res;

	get_char(split, &pos, 'S');
	visited = create_map(split, 0, 1);
	path = create_map(split, 0, sizeof(t_pos_lst *));
	score = dijkstra(split, &pos, visited, path);
	get_char(split, &pos, 'E');
	res = get_result(path, pos, split, score);
	return(res);
}
