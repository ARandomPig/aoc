/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/13 23:41:42 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libft/libft.h"

static void get_pos(char *line, long int *res)
{
	while(*line && *line != 'X')
		line++;
	if(*line)
	{
		line += 2;
		res[0] = atoi(line);
	}
	while(*line && *line != 'Y')
		line++;
	if(*line)
	{
		line += 2;
		res[1] = atoi(line);	
	}
}

static long int get_score(long int btn_a[2],long int btn_b[2],long int prize[2])
{
	double a;
	double b;
	long int res[2];

	a = ((prize[1] * btn_b[0]) - (prize[0] * btn_b[1])) / ((btn_a[1] * btn_b[0]) - (btn_a[0] * btn_b[1]));
	b = (((-btn_a[0] * a) + prize[0]) / btn_b[0]);
	res[0] = a;
	res[1] = b;
	if((btn_a[0] * res[0]) + (btn_b[0] * res[1]) != prize[0] || (btn_a[1] * res[0]) + (btn_b[1] * res[1]) != prize[1])
		return(0);
	return((a * 3) + b);
}

long int resolve_part1(char *input, char **split)
{
	(void)input;
	long int btn_a[2];
	long int btn_b[2];
	long int prize[2];
	long int res;

	res = 0;
	while(*split)
	{
		get_pos(*split, btn_a);
		split++;
		get_pos(*split, btn_b);
		split++;
		get_pos(*split, prize);
		split++;
		res += get_score(btn_a, btn_b, prize);
	}
	return(res);
}
