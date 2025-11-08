NAME    := pipex
CC      := cc
FLAGS   := -Wall -Wextra -Werror -g
RM      := rm -f

SRCS    := pipex.c pipex_utils.c parser.c main.c
OBJS    := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cd libft ; make
	$(CC) $(FLAGS) $(OBJS) libft/libft.a -o $(NAME)

%.o: %.c pipex.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@cd libft && make clean

fclean: clean
	$(RM) $(NAME)
	@cd libft && make fclean

re: fclean all

.PHONY: all clean fclean re