#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

long int resolve(char *input);

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
	return(res);
}

int main(void)
{
	char *input;

	input = get_input("input");
	if(!input)
	{
		printf("file read error\n");
		return(1);
	}
	printf("result: %ld\n", resolve(input));
	free(input);
	return(0);
}
