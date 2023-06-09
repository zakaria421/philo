NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread -g
RM = rm -f
SRC = philo.c\
	  help1.c\
	  help2.c\
	  help3.c\
	  help4.c\


OBJECT = ${SRC:.c=.o}
all: $(NAME)
$(NAME) : $(OBJECT)
		cc  $(CFLAGS) $(OBJECT) -o $(NAME) 

clean:
	$(RM) $(OBJECT)
	$(RM) $(BOBJECT) 
	
fclean:
	$(RM) $(OBJECT) 
	$(RM) $(NAME)

re: fclean all