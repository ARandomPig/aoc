/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/22 23:07:18 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

long int sim_secret(long int nb)
{
	int i;

	i = 0;
	while(i < 2000)
	{
		nb = ((nb * 64) ^ nb) % 16777216;
		nb = ((nb / 32) ^ nb) % 16777216;
		nb = ((nb * 2048) ^ nb) % 16777216;
		i++;
	}
	return(nb);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	long int res;
	
	res = 0;
	while(*split)
	{
		res += sim_secret(atol(*split));	
		split++;
	}
	return(res);
}
