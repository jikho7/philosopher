NAME	= philo

SRC		= 	main.c\
			philosopher.c\
			init.c\
			utils.c\
			routine_philo.c\
			errors.c\
			mutex.c\

OBJ		= ${SRC:.c=.o}

CFLAGS	= -Wall -Wextra -Werror -pthread -g -fsanitize=thread

CC		= gcc

all : $(NAME)

%.o: %.c
	${CC} ${CFLAGS} -o $@ -c $<

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
