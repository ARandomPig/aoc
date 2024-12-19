/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/19 17:38:49 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

long int resolve_part1(char *input, char **split)
{
	(void)split;
	long int res;
	int cur;

	res = 0;
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
		if(res < cur)
			res = cur;
	}
	return(res);
}
