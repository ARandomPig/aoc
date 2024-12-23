/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:03:36 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/23 00:38:13 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "libft/libft.h"

typedef struct s_seq
{
	int seq[4];
	int score;
	int checked;
	struct s_seq *next;
}	t_seq;

static void add_seq(t_seq **list, int *seq, int val, int cur)
{
	t_seq *tmp;
	t_seq *new;

	tmp = *list;
	while(tmp)
	{
		if(!memcmp(tmp->seq, seq, 4 * sizeof(int)))
		{
			if(tmp->checked < cur)
				tmp->score += val;
			tmp->checked = cur;
			return;
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_seq));
	new->seq[0] = seq[0];
	new->seq[1] = seq[1];
	new->seq[2] = seq[2];
	new->seq[3] = seq[3];
	new->checked = cur;
	new->score = val;
	new->next = *list;
	*list = new;
}

static long int sim_secret(long int nb, t_seq **seq_list, int cur)
{
	int i;
	int prev;
	int seq[4];

	i = 0;
	while(i < 4)
	{
		prev = nb % 10;
		nb = ((nb * 64) ^ nb) % 16777216;
		nb = ((nb / 32) ^ nb) % 16777216;
		nb = ((nb * 2048) ^ nb) % 16777216;
		seq[i] = (nb % 10) - prev;
		i++;
	}
	add_seq(seq_list, seq, nb % 10, cur);
	while(i < 2000)
	{
		prev = nb % 10;
		nb = ((nb * 64) ^ nb) % 16777216;
		nb = ((nb / 32) ^ nb) % 16777216;
		nb = ((nb * 2048) ^ nb) % 16777216;
		seq[0] = seq[1];
		seq[1] = seq[2];
		seq[2] = seq[3];
		seq[3] = (nb % 10) - prev;
		add_seq(seq_list, seq, nb % 10, cur);
		prev = nb % 10;
		i++;
	}
	return(nb);
}

int get_eta(struct timeval start, int cur, int len)
{
	struct timeval end;
	double sec_time;
	double secpit;

	gettimeofday(&end, 0);
	sec_time = ((double)(end.tv_usec - start.tv_usec) / 1000000) + (end.tv_sec - start.tv_sec);
	secpit = sec_time / cur;
	return((int)((len - cur) * secpit));
}

long int resolve_part2(char *input, char **split)
{
	(void)input;
	t_seq *sequences;
	t_seq *tmp;
	int best;
	int i;
	int len;
	struct timeval start;
	
	sequences = 0;
	best = 0;
	i = 0;
	len = 0;
	gettimeofday(&start, 0);
	while(split[len])
		len++;
	while(split[i])
	{
		if(i < 300)
			printf("%d/%d        \r", i + 1, len);
		else
			printf("%d/%d, ETA : %ds        \r", i + 1, len, get_eta(start, i + 1, len));
		fflush(stdout);
		sim_secret(atol(split[i]), &sequences, i);
		i++;
	}
	printf("\n");
	while(sequences)
	{
		if(sequences->score > best)
			best = sequences->score;
		tmp = sequences->next;
		free(sequences);
		sequences = tmp;
	}
	return(best);
}
