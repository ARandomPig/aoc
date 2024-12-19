/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/19 17:43:45 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

long int resolve_part2(char *input, char **split)
{
	(void)split;
	int top[3];
	int cur;

	ft_bzero(top, sizeof(int) * 3);
	while(*input)
	{
		cur = 0;
		while(*input && (input[0] != '\n' || input[1] != '\n'))
		{
			while(*input && !ft_isdigit(*input))
				input++;
			cur += ft_atoi(input);
			while(ft_isdigit(*input))
				input++;
		}
		while(*input == '\n')
			input++;
		if(cur > top[0])
		{
			ft_swap(top + 1, top + 2);
			ft_swap(top, top + 1);
			top[0] = cur;
		}
		else if(cur > top[1])
		{
			ft_swap(top + 1, top + 2);
			top[1] = cur;
		}
		else if(cur > top[2])
			top[2] = cur;
	}
	return(top[0] + top[1] + top[2]);
}
