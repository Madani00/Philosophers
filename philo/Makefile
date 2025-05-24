NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread
RM = rm -f
MK = make
SRCS = main.c check_args.c check_inputs.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
		${RM} ${OBJS}

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re