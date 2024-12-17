/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/17 17:50:43 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include "libft/libft.h"

static long int get_register(char *str)
{
	while(*str && *str != ':')
		str++;
	return(ft_atoi(str + 1));
}

static void parse_input(char **split, int *reg, uint8_t **ops, size_t *len)
{
	char *tmp;
	int i;

	reg[0] = get_register(*split);
	split++;
	reg[1] = get_register(*split);
	split++;
	reg[2] = get_register(*split);
	split++;
	*len = 0;
	tmp = *split;
	while(*tmp)
	{
		if(ft_isdigit(*tmp))
			(*len)++;
		tmp++;	
	}
	i = 0;
	*ops = malloc(*len);
	tmp = *split;
	while(*tmp)
	{
		while(*tmp && !ft_isdigit(*tmp))
			tmp++;
		if(*tmp)
			(*ops)[i] = (uint8_t)atoi(tmp);
		i++;
		while(ft_isdigit(*tmp))
			tmp++;
	}
}

static int combo(uint8_t val, int *reg)
{
	if(val <= 3)
		return(val);
	if(val == 7)
	{
		printf("err\n");
		exit(1);
	}
	return(*(reg + (val - 4)));
}

static size_t exec_instructions(uint8_t *ops, int *reg, size_t len, uint8_t *out)
{
	size_t instr_ptr;
	size_t out_ptr;

	instr_ptr = 0;
	out_ptr = 0;
	while(instr_ptr < len)
	{
//		printf("op : %d, %d\n", ops[instr_ptr], ops[instr_ptr + 1]);
		switch (ops[instr_ptr])
		{
			case 0:
				reg[0] = reg[0] / pow(2, combo(ops[instr_ptr + 1], reg));
				instr_ptr += 2;
				break;
			case 1:
				reg[1] = reg[1] ^ ops[instr_ptr + 1];
				instr_ptr += 2;
				break;
			case 2:
				reg[1] = combo(ops[instr_ptr + 1], reg) % 8;
				instr_ptr += 2;
				break;
			case 3:
				if(reg[0])
					instr_ptr = ops[instr_ptr + 1];
				else
					instr_ptr += 2;
				break;
			case 4:
				reg[1] = reg[1] ^ reg[2];
				instr_ptr += 2;
				break;
			case 5:
				out[out_ptr++] = combo(ops[instr_ptr + 1], reg) % 8;
				instr_ptr += 2;
				break;
			case 6:
				reg[1] = reg[0] / pow(2, combo(ops[instr_ptr + 1], reg));
				instr_ptr += 2;
				break;
			case 7:
				reg[2] = reg[0] / pow(2, combo(ops[instr_ptr + 1], reg));
				instr_ptr += 2;
				break;
		}
		if(out_ptr == len)
			break;
	}
	return(out_ptr);
}

void show_progress(struct timeval start, int cur)
{
	struct timeval now;
	double itps;
	double sec_diff;

	gettimeofday(&now, 0);
	sec_diff = (((double)now.tv_usec - (double)start.tv_usec) / 1000000) + (now.tv_sec - start.tv_sec);
	itps = cur / sec_diff;
	printf("currently: %d, itps : %f, time remaining until max int : %fs                 \r", cur, itps, (2147483647 - cur) / itps);
	fflush(stdout);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	int reg[3];
	uint8_t *ops;
	size_t len;
	uint8_t *out;
	size_t out_len;
	int i;
	struct timeval start;
	
	parse_input(split, reg, &ops, &len);
	out = malloc(len);
	gettimeofday(&start, 0);
	i = 1;
	while(1)
	{
		reg[0] = i;
		reg[1] = 0;
		reg[2] = 0;
		out_len = exec_instructions(ops, reg, len, out);
		if(out_len == len && !memcmp(out, ops, len))
			return(i);
		i++;
		if(i % 1000000 == 0)
			show_progress(start, i);
	}
	return(0);
}
