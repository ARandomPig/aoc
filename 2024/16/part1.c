/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/18 23:21:58 by tomoron          ###   ########.fr       */
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

typedef struct s_vis
{
	t_pos pos;
	int dir[2];
	struct s_vis *next;
}	t_vis;

typedef struct s_lst
{
	t_pos			pos;
	uint32_t		score;
	int				dir[2];
	struct s_lst	*next;
}	t_lst;

void *create_map(char **map, uint8_t fill, int bloc_size)
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

void get_char(char **map, t_pos *pos, char c)
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

int is_visited(t_vis *vis, t_pos pos, int dir[2])
{
	while(vis)
	{
		if(vis->pos.x == pos.x && vis->pos.y == pos.y && vis->dir[0] == dir[0] && vis->dir[1] == dir[1])
			return(1);
		vis = vis->next;
	}
	return(0);
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

int get_new_pos(t_lst **lst, char **vis, t_pos *pos, uint32_t *score, int *dir)
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
	if(vis[pos->y][pos->x] & (dir_to_bit(dir)))
		return(get_new_pos(lst, vis, pos, score, dir));
	return(1);
}

void visited_add(t_vis **visited, t_pos *pos, int dir[2])
{
	t_vis *new;
	
	new = malloc(sizeof(t_vis));
	new->dir[0] = dir[0];
	new->dir[1] = dir[1];
	new->pos.x = pos->x;
	new->pos.y = pos->y;
	new->next = *visited;
	*visited = new;
}

void add_lst(t_lst **lst, uint32_t score, t_pos pos, int dir[2])
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

int	*rotate_dir(int dir[2], int inv, int *res)
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

uint32_t dijkstra(char **map, t_pos *pos)
{
	int dir[2];
	int tmp[2];
	char **visited;
	t_lst *lst;
	uint32_t score;

	visited = create_map(map, 0, 1);
	lst = 0;
	add_lst(&lst, 0, *pos, (int [2]){0, 1});
	while(get_new_pos(&lst, visited, pos, &score, dir))
	{
		visited[pos->y][pos->x] |= dir_to_bit(dir);
		if(map[pos->y][pos->x] == '#')
			continue;
		if(map[pos->y][pos->x] == 'E')
		{
			free_lst(lst);
			ft_free_str_arr(visited);
			return(score);
		}
		if(map[pos->y + dir[0]][pos->x + dir[1]] != '#')
			add_lst(&lst, score + 1, (t_pos){pos->x + dir[1], pos->y + dir[0]}, dir);
		rotate_dir(dir, 0, tmp);
		if(map[pos->y + tmp[0]][pos->x + tmp[1]] != '#')
			add_lst(&lst, score + 1000, *pos, tmp);
		rotate_dir(dir, 1, tmp);
		if(map[pos->y + tmp[0]][pos->x + tmp[1]] != '#')
			add_lst(&lst, score + 1000, *pos, tmp);
	}
	ft_free_str_arr(visited);
	return(0);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	t_pos pos;

	get_char(split, &pos, 'S');

	return(dijkstra(split, &pos));
}
