/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/18 23:32:19 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "libft/libft.h"

static long int get_register(char *str)
{
	while(*str && *str != ':')
		str++;
	return(atol(str + 1));
}

static void parse_input(char **split, long int *reg, uint8_t **ops, size_t *len)
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

static long int combo(uint8_t val, long int *reg)
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

static size_t exec_instructions(uint8_t *ops, long int *reg, size_t len, uint8_t *out)
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
				reg[0] = reg[0] >> combo(ops[instr_ptr + 1], reg);
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
				reg[1] = reg[0] >> combo(ops[instr_ptr + 1], reg);
				instr_ptr += 2;
				break;
			case 7:
				reg[2] = reg[0] >> combo(ops[instr_ptr + 1], reg);
				instr_ptr += 2;
				break;
		}
	}
	return(out_ptr);
}

int is_good(long int tmp, uint8_t *ops, size_t op_len, size_t cur_len)
{
	long int reg[3];	
	uint8_t *out;
	size_t out_len;
	size_t i;

	reg[0] = tmp;
	reg[1] = 0;
	reg[2] = 0;
	out = malloc(128);
	out_len = exec_instructions(ops, reg, op_len, out);
	if(out_len != cur_len)
	{
		free(out);
		return(0);
	}
	i = 0;
	while(i < out_len && i < op_len)
	{
		if(out[out_len - i - 1] != ops[op_len - i - 1])
		{
			free(out);
			return(0);
		}
		i++;
	}
	free(out);
	return(1);
}

long int get_res(long int cur, uint8_t *ops, size_t len, size_t depth)
{
	long int nb;
	long int tmp;
	long int res;

	nb = 0;
	tmp = 0;
	while(nb < 8)
	{
		tmp = (cur << 3 ) | nb;
		if(is_good(tmp, ops, len, depth + 1))
		{
			if(depth < len)
			{
				res = get_res(tmp, ops, len, depth + 1);
				if(res)
					return(res);
			}
			else	
				break;
		}
		nb++;
	}
	if(nb == 8)
		return(0);
	return(cur);
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	long int reg[3];
	uint8_t *ops;
	size_t len;
	long int res;
	
	parse_input(split, reg, &ops, &len);
	res = get_res(0, ops, len, 0);
	free(ops);
	return(res);
}
