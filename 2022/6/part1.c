/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/10/29 14:10:49 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

static int check_repeat(char *str)
{
	int i;
	int j;

	i = 0;
	while(str[i])
	{
		j = 0;
		while(str[j])
		{
			if(i != j && str[i] == str[j])
				return(1);
			j++;
		}
		i++;
	}
	return(0);
}

long int resolve_part1(char *input, char **split)
{
	(void)split;
	char hist[5];
	int i;

	i = 0;
	hist[4] = 0;
	while(input[i])
	{
		ft_memcpy(hist, input + i, 4);
		if(!check_repeat(hist))
			return(i + 4);
		i++;
	}
	return(0);
}
