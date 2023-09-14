NAME	= philo

SRC		= 	main.c\
			init.c\
			utils.c\
			routine_philo.c\
			test.c\
			errors.c\

OBJ		= ${SRC:.c=.o}

FLAGS	= -Wall -Wextra -Werror -pthread -g -fsanitize=thread

CC		= gcc -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
