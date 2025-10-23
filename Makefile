NAME		:= pipex.a 
CC			:= cc 
FLAGS		:= -Wall -Wextra -Werror -g -I.  
RM			:= rm -f 
AR			:= ar
RCS			:= rcs
SRCS		:= ft_pipex.c 

OBJS		:= $(SRCS:.c=.o)

all:	$(NAME) 

$(NAME): $(OBJS) 
	@cd /home/xiribar/Desktop/projects/libft ; make ; make clean
	@mv /home/xiribar/Desktop/projects/libft/libft.a ../pipex
	$(AR) $(RCS) libft.a $(OBJS)
	@mv libft.a $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
		$(RM) $(NAME)

re: fclean all


.PHONY = all clean fclean re 

