CC=cc
#FLAGS=-Wall -Werror -Wextra -lpthread -g
FLAGS=-Wall -Werror -Wextra -g
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

fclean: clean
	rm -f $(NAME)

re: fclean all
