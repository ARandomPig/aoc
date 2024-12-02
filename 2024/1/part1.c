/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/01 12:36:03 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static void ft_sort(int *list, int len)
{
	int i;
	int j;
	int tmp;
	
	i = 0;
	while(i < len - 1)
	{
		j = 0;
		while(j < len - 1)
		{
			if(list[j] > list[j + 1])
			{
				tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void get_numbers(int *left, int *right, char **split)
{
	int i;
	int j;

	i = 0;
	while(*split)
	{
		j = 0;
		*(left + i) = ft_atoi(*split);
		while((*split)[j] >= '0' && (*split)[j] <= '9')
			j++;
		while((*split)[j] == ' ')
			j++;
		*(right + i) = ft_atoi(*split + j);
		i++;
		split++;
	}
}

long int resolve_part1(char *input, char **split)
{
	int len;
	int *left;
	int *right;
	long int res;
	int i;
	int tmp;

	len = 0;
	i = 0;
	while(split[len])
		len++;
	left = malloc(sizeof(int) * len);	
	right = malloc(sizeof(int) * len);	
	if(!left || !right)
	{
		free(left);
		free(right);
		return(-1);
	}
	get_numbers(left, right, split);
	ft_sort(left, len);
	ft_sort(right, len);
	res = 0;
	while(i < len)
	{
		tmp = left[i] - right[i];
		if(tmp < 0)
			tmp *= -1;
		res += tmp;
		i++;
	}
	free(left);
	free(right);
	(void)input;
	return(res);
}
