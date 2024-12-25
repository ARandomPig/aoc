/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/25 12:08:33 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct s_elem
{
	int nbrs[5];
	int lock;
	struct s_elem *next;
} t_elem;

void set_nbrs(t_elem *res, char **split)
{
	int y;
	int x;
	
	if(**split == '#')
		res->lock = 1;
	x = 0;
	y = 0;
	while(split[0][x])
	{
		y = 0;
		while((res->lock && split[y][x] == '#') || (!res->lock && split[y][x] == '.'))
			y++;	
		res->nbrs[x] = y;
		x++;
	}
}

void add_elem(t_elem **res, char **split)
{
	t_elem *new;

	new = malloc(sizeof(t_elem));
	new->lock = 0;
	new->next = *res;
	set_nbrs(new, split);
	*res = new;
}

t_elem *get_all(char **all)
{
	char **split;
	t_elem *res;

	res = 0;
	while(*all)
	{
		split = ft_split(*all, '\n');	
		add_elem(&res, split);	
		ft_free_str_arr(split);
		all++;
	}
	return(res);
}

int try_keys(t_elem *all, t_elem *lock)
{
	int i;
	int res;

	res = 0;
	while(all)
	{
		if(all->lock == 0)
		{
			i = 0;
			while(i < 5)
			{
				if(lock->nbrs[i] > all->nbrs[i])		
					break;
				i++;
			}
			if(i == 5)
				res++;
		}
		all = all->next;
	}
	return(res);
}

int get_res(t_elem *lst)
{
	t_elem *start;
	int res;

	res = 0;
	start = lst;
	while(lst)
	{
		if(lst->lock == 1)
			res += try_keys(start, lst);
		lst = lst->next;
	}
	return(res);
}

long int resolve_part1(char *input, char **split)
{
	int i;
	t_elem *lst;
	int res;

	i = 1;
	while(input[i])
	{
		if(input[i - 1] == '\n' && input[i] == '\n')
		{
			input[i - 1] = 'x';
			input[i] = 'x';
		}
		i++;
	}
	split = ft_split(input, 'x');
	lst = get_all(split);
	ft_free_str_arr(split);
	res = get_res(lst);
	return(res);
}
