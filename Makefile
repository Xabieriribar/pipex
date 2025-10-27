NAME		:= pipex.a 
CC			:= cc 
FLAGS		:= -Wall -Wextra -Werror -g -I.  
RM			:= rm -f 
AR			:= ar
RCS			:= rcs
SRCS		:= pipex.c pipex_utils.c

OBJS		:= $(SRCS:.c=.o)

all:	$(NAME) 

$(NAME): $(OBJS) pipex.h
	@cd libft ; make ; make clean
	@mv libft/libft.a .
	$(AR) $(RCS) libft.a $(OBJS)
	@mv libft.a $(NAME)
	@cc $(NAME) -o pipex

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
		$(RM) $(NAME)

re: fclean all


.PHONY = all clean fclean re

