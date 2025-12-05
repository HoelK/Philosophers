CC=cc
FLAGS=-Wall -Wextra -Werror -g -pthread
SRCS=philo.c stats.c utils.c debug.c
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
