#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

long int resolve_part1(char *input, char **split);
long int resolve_part2(char *input, char **split);

char *get_input(char *file)
{
	int fd;
	int rd_len;
	char buffer[1000];
	int len;
	char *res;

	fd = open(file, O_RDONLY);
	len = 0;
	if(fd < 0)
		return(0);
	rd_len = -1;
	while(rd_len)
	{
		rd_len = read(fd, buffer, 1000);
		len+= rd_len;
	}
	close(fd);
	res = malloc(len + 1);
	if(!res)
		return(0);
	fd = open(file, O_RDONLY);
	if(fd < 0)
		return(0);
	rd_len = read(fd,res, len);
	res[len] = 0;
	close(fd);
	return(res);
}

int main(void)
{
	char *input;
	char *input_cpy;
	char **split;

	input = get_input("input");
	input_cpy = ft_strdup(input);
	if(!input || !input_cpy)
	{
		fprintf(stderr, "file read error\n");
		return(1);
	}
	split = ft_split(input, '\n');
	if(!split)
		return(1);
	printf("result part 1: %ld\n", resolve_part1(input, split));
	ft_free_str_arr(split);
	split = ft_split(input_cpy, '\n');
	if(!split)
		return(1);
	printf("result part 2: %ld\n", resolve_part2(input, split));
	ft_free_str_arr(split);
	free(input);
	return(0);
}
