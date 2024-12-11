/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/11 17:17:34 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

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

int count_digits(long int nb)
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

void split_pebble(t_pebble *pebble)
{
	t_pebble *new;
	t_pebble *tmp;
	int len;
	long exp;
	int i;

	new = malloc(sizeof(t_pebble));
	len = count_digits(pebble->value) / 2;
	new->value = 0;
	i = 0;
	exp = 1;
	while(i < len)
	{
		new->value += (pebble->value % 10) * exp;
		pebble->value /= 10;
		exp *= 10;
		i++;
	}
	tmp = pebble->next;
	pebble->next = new;
	new->next = tmp;
}

long int update(t_pebble *pebble)
{
	long int res;

	res = 0;
	while(pebble)
	{
		if(!pebble->value)
			pebble->value = 1;
		else if(count_digits(pebble->value) % 2 == 0)
		{
			split_pebble(pebble);
			pebble = pebble->next;
		}
		else
			pebble->value *= 2024;
		pebble = pebble->next;
		res++;
	}
	return(res);
}

long int resolve_part1(char *input, char **split)
{
	(void)split;
	t_pebble *pebble;
	pebble = get_input(input);
	int i;
	long int res;

	i = 0;
	res = 0;
	while(i < 25)
	{
		printf("step : %d, len :%ld\n",i, update(pebble));
		i++;
	}
	while(pebble)	
	{
		res++;
		pebble = pebble->next;
	}
	return(res);
}
