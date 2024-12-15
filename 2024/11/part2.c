/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/15 19:02:10 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"

#define MAX_NB_MAP 1000

typedef struct s_pebble
{
	long int value;
	struct s_pebble *next;
}	t_pebble;

static t_pebble *get_input(char *input)
{
	t_pebble *res;
	t_pebble *prev;
	t_pebble *cur;

	prev = 0;
	while(*input && (ft_isdigit(*input) || *input == ' '))
	{
		cur = malloc(sizeof(t_pebble));
		cur->next = 0;
		cur->value = atol(input);
		if(prev)
			prev->next = cur;
		else
			res = cur;
		prev = cur;
		while(ft_isdigit(*input))
			input++;
		while(*input == ' ')
			input++;
	}
	return(res);
}

static int count_digits(long int nb)
{
	int res;

	res = 1;
	while(nb > 9)
	{
		nb /= 10;
		res++;
	}
	return(res);
}

static void split_pebble(long int *l, long int *r)
{
	int len;
	long exp;
	int i;

	len = count_digits(*l) / 2;
	*r = 0;
	i = 0;
	exp = 1;
	while(i < len)
	{
		*r += (*l % 10) * exp;
		*l /= 10;
		exp *= 10;
		i++;
	}
}

static long int get_nb(long int nb, long int depth, long int *map)
{
	long int res;
	long int tmp;
	long int fuck;

	fuck = nb;
	if(depth == 75)
		return(1);
	if(map && nb >= 0 && nb < MAX_NB_MAP && map[(depth * MAX_NB_MAP) + nb])
		return(map[(depth * MAX_NB_MAP) + nb]);
	res = 0;
	if(nb == 0)
		res = get_nb(1, depth + 1, map);
	else if(count_digits(nb) % 2 == 0)
	{
		split_pebble(&nb, &tmp);
		res = get_nb(nb, depth + 1, map);
		res += get_nb(tmp, depth + 1, map);
	}
	else
		res = get_nb(nb * 2024, depth + 1, map);
	if(map && fuck >= 0 && fuck < MAX_NB_MAP)
		map[(depth * MAX_NB_MAP) + fuck] = res;
	return(res);
}

long int resolve_part2(char *input, char **split)
{
	(void)split;
	(void)input;
	t_pebble *pebble;
	t_pebble *tmp;
	long int res;
	long int *map;		
	size_t		map_len;
	(void)get_input;

	res = 0;
	pebble = get_input(input);
	map_len = MAX_NB_MAP * 75 * sizeof(long int);
	map = malloc(map_len);
	bzero(map, map_len);
	while(pebble)
	{
		tmp = pebble->next;
		res += get_nb(pebble->value, 0, map);
		free(pebble);
		pebble = tmp;
	}
	free(map);
	return(res);
}
