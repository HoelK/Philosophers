CC=cc
FLAGS=-Wall -Wextra -Werror -g -pthread -O3
SRCS=main.c routine.c parse.c init.c exit.c debug.c monitor.c utils.c
OBJS=$(SRCS:.c=.o)
NAME=philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
