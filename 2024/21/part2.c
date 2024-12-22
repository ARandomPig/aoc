/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/22 20:25:16 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft/libft.h"

typedef struct s_cache
{
	char *str;
	int pos[2];
	int depth;
	uint64_t res;
	struct s_cache *next;
}	t_cache;

static void get_char_pos(char **map, char c, int *res)
{
	res[0] = 0;
	while(map[res[0]])
	{
		res[1] = 0;
		while(map[res[0]][res[1]])
		{
			if(map[res[0]][res[1]] == c)
				return ;
			res[1]++;
		}
		res[0]++;
	}
}

static void add_char(int nb, char c, char *res, int *i)
{
	if(nb < 0)
		nb *= -1;
	while(nb > 0)
	{
		res[(*i)++] = c;
		nb--;
	}
	res[*i] = 0;
}

static int move_y(char **map, int diff[2], int from[2])
{
	int diff_spc[2];
	int spc[2];

	get_char_pos(map, ' ', spc);
	diff_spc[0] = spc[0] - from[0];
	diff_spc[1] = spc[1] - from[1];
	return((diff[1] > 0 || (diff_spc[1] == diff[1] && diff_spc[0] == 0)) && (diff_spc[0] != diff[0] || diff_spc[1] != 0));
}

static char *plan_route(char **map, int from[2], int to[2])
{
	int diff[2];
	char chrs[2];
	char *res;
	int i;

	res = malloc(128);
	i = 0;
	chrs[0] = 'v';
	chrs[1] = '>';
	diff[0] = to[0] - from[0];
	diff[1] = to[1] - from[1];
	if(diff[0] < 0)
		chrs[0] = '^';
	if(diff[1] < 0)
		chrs[1] = '<';
	if(move_y(map, diff, from))
	{
		add_char(diff[0], chrs[0], res, &i);
		add_char(diff[1], chrs[1], res, &i);
	}
	else
	{
		add_char(diff[1], chrs[1], res, &i);	
		add_char(diff[0], chrs[0], res, &i);
	}
	res[i] = 'A';
	res[i + 1] = 0;
	return(res);
}

static uint64_t get_cache(t_cache *cache, char *str, int depth, int *pos)
{
	while(cache)
	{
		if(!ft_strcmp(cache->str, str) && cache->depth == depth && cache->pos[0] == pos[0] && cache->pos[1] == pos[1])
			return(cache->res);
		cache = cache->next;
	}
	return(0);
}

static void add_cache(t_cache **cache, char *str, int depth, int *pos, uint64_t res)
{
	t_cache *new;

	new = malloc(sizeof(t_cache));
	new->str = ft_strdup(str);
	new->depth = depth;
	new->pos[0] = pos[0];
	new->pos[1] = pos[1];
	new->res = res;
	new->next = *cache;
	*cache = new;
}

static uint64_t get_path_len(char **keypad, char **robot_pad, int **pos, char *objectives, int depth)
{
	static t_cache *cache;
	int cur_objective[2];
	char *path;
	uint64_t res;
	int i;

	res = get_cache(cache, objectives, depth, pos[depth]);
	i = 0;
	if(res)
		return(res);
	while(objectives[i])
	{
		if(depth != 0)
			keypad = robot_pad;
		get_char_pos(keypad, objectives[i], cur_objective);
		path = plan_route(keypad, pos[depth], cur_objective);
		if(depth < 25)
			res += get_path_len(keypad, robot_pad, pos, path, depth + 1);
		else
			res += ft_strlen(path);
		free(path);
		pos[depth][0] = cur_objective[0];
		pos[depth][1] = cur_objective[1];
		i++;
	}
	add_cache(&cache, objectives, depth, pos[depth], res);
	return(res);
}

static int **init_positions(int nb)
{
	int **res;
	int i;

	res = malloc((nb + 1) * sizeof(int *));
	res[nb] = 0;
	i = 0;
	while(i < nb)
	{
		res[i] = malloc(2 * sizeof(int));
		res[i][0] = 0;
		res[i][1] = 2;
		if(i == 0)
			res[i][0] = 3;
		i++;
	}
	return(res);
}

uint64_t resolve_part2(char *input, char **split)
{
	(void)input;
	(void)split;
	int **pos;
	uint64_t res;
	char **keypad;
	char **robot_pad;

	keypad = ft_split("789\n456\n123\n 0A", '\n');
	robot_pad = ft_split(" ^A\n<v>", '\n');
	pos = init_positions(26);
	res = 0;
	while(*split)
	{
		res += get_path_len(keypad, robot_pad, pos, *split, 0) * ft_atoi(*split);
		split++;
	}
	ft_free_str_arr((void *)pos);
	ft_free_str_arr(keypad);
	ft_free_str_arr(robot_pad);
	return(res);
}
