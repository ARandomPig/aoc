/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/20 15:16:55 by tomoron          ###   ########.fr       */
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
	res[height] = 0;
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
	return(x >= 0 && y >= 0 && map[y] && map[y][x] != '#');
}

static void free_lst(t_lst *lst)
{
	t_lst *tmp;

	while(lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

static uint32_t dijkstra(char **map, t_pos pos, uint32_t **dists)
{
	int dir[2];
	int tmp[2];
	char **visited;
	t_lst *lst;
	uint32_t score;

	visited = create_map(map, 0, 1);
	lst = 0;
	add_lst(&lst, 0, pos, (int [2]){0, 1});
	while(get_new_pos(&lst, visited, &pos, &score, dir))
	{
		if(dists[pos.y][pos.x] > score)
			dists[pos.y][pos.x] = score;
		visited[pos.y][pos.x] = 1;
		if(map[pos.y][pos.x] == '#')
			continue;
		if(is_valid_move(map, pos.y + dir[0], pos.x + dir[1]))
			add_lst(&lst, score + 1, (t_pos){pos.x + dir[1], pos.y + dir[0]}, dir);
		rotate_dir(dir, 0, tmp);
		if(is_valid_move(map, pos.y + tmp[0], pos.x + tmp[1]))
			add_lst(&lst, score + 1, (t_pos){pos.x + tmp[1], pos.y + tmp[0]}, tmp);
		rotate_dir(dir, 1, tmp);
		if(is_valid_move(map, pos.y + tmp[0], pos.x + tmp[1]))
			add_lst(&lst, score + 1, (t_pos){pos.x + tmp[1], pos.y + tmp[0]}, tmp);
	}
	ft_free_str_arr(visited);
	return(0);
}

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

static long int check_around(uint32_t **dists, t_pos pos, int len, int height, int cheat_dist, int cur_dist)
{
	long int res;
	int x;
	int y;

	res = 0;
	y = -cheat_dist - 1;
	while(y <= cheat_dist)
	{
		x = -cheat_dist - 1;
		while(x <= cheat_dist)
		{
			if((x || y) && pos.x + x >= 0 && pos.y + y >= 0 && pos.x + x < len && pos.y + y < height && abs(x) + abs(y) <= cheat_dist)
				if(dists[pos.y + y][pos.x + x] != (uint32_t)-1)
					if((dists[pos.y + y][pos.x + x] - cur_dist) - (abs(x) + abs(y)) >= 100)
						res++;	
			x++;
		}
		y++;
	}
	return(res);
}

static void get_next_pos(char **map, uint32_t **dists, t_pos *pos)
{
	uint32_t min;
	t_pos new;

	min = -1;
	new.x = 0;
	new.y = 0;
	if(pos->x > 0 && dists[pos->y - 1][pos->x] < min)
	{
		min = dists[pos->y - 1][pos->x];
		new.x = pos->x;
		new.y = pos->y - 1;
	}
	if(pos->y > 0 && dists[pos->y][pos->x - 1] < min)
	{
		min = dists[pos->y][pos->x - 1];
		new.x = pos->x - 1;
		new.y = pos->y;
	}
	if(map[pos->y + 1] && dists[pos->y + 1][pos->x] < min)
	{
		min = dists[pos->x][pos->y + 1];
		new.x = pos->x;
		new.y = pos->y + 1;
	}
	if(map[pos->y][pos->x + 1] && dists[pos->y][pos->x + 1] < min)
	{
		min = dists[pos->x + 1][pos->y];
		new.x = pos->x + 1;
		new.y = pos->y;
	}
	pos->x = new.x;
	pos->y = new.y;

}

static long int count_cheats(char **map, t_pos pos, uint32_t **dists)
{
	long int res;
	uint32_t cur_dist;
	int len;
	int height;

	res = 0;
	height = 0;
	len = 0;
	while(map[height])
		height++;
	while(map[0][len])
		len++;
	while(map[pos.y][pos.x] != 'E')
	{
		cur_dist = dists[pos.y][pos.x];
		dists[pos.y][pos.x] = (uint32_t) -1;
		if(cur_dist != (uint32_t)-1)
			res += check_around(dists, pos, len, height, 20, cur_dist);
		get_next_pos(map, dists, &pos);
	}
	return(res);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	t_pos strt;
	uint32_t **dists;
	long int res;

	get_char(split, &strt, 'S');
	dists = create_map(split, 255, sizeof(uint32_t));
	dijkstra(split,strt, dists);
	res = count_cheats(split, strt, dists);
	ft_free_str_arr((void *)dists);
	(void)free_lst;
	return(res);
}
