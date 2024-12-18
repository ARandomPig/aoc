# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 15:48:36 by tomoron           #+#    #+#              #
#    Updated: 2024/10/29 20:43:12 by tomoron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c\
		part1.c\
		part2.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wextra -Werror -Wall -g

LIB = libft/libft.a

all: $(LIB) a.out test
	cp test cur_input
	./a.out

f: $(LIB) a.out input
	cp input cur_input
	./a.out

test: 
	touch test

input:
	touch input

cp:
	cp part1.c part2.c
	sed -i 's/resolve_part1/resolve_part2/g' part2.c

$(LIB): libft
	make -C libft

libft:
	cp -r ~/Desktop/aoc/libft .

main.c:
	cp ~/Desktop/aoc/main.c .

part1.c:
	cp ~/Desktop/aoc/part1.c .

part2.c:
	cp ~/Desktop/aoc/part2.c .

a.out: main.c $(OBJS) $(LIB)
	clang $(FLAGS) $(OBJS) $(LIB)

clean:
	rm -rf $(OBJS)
	rm -rf libft

fclean: clean
	rm -rf a.out

.c.o:
	clang $(FLAGS) -c $< -o $@

.PHONY: t all clean fclean cp
