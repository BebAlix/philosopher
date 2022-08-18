GREEN = /bin/echo -e "\x1b[1;3;32m$1\x1b[0m"
SRC =   srcs/main.c \
		srcs/utils.c \
		srcs/dinner.c \
		srcs/init_vars.c \
		srcs/free_vars.c \
		srcs/check_errors.c \
		srcs/launch_thread.c \

OBJ = $(SRC:.c=.o)
CC = gcc -g
CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread
LIBS = -lpthread
NAME = philo

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@
		$(call GREEN,"Compilation success 😁")

clean:
		rm -f $(OBJ)
		$(call GREEN,"The .o cleaned up !")


fclean:		clean
		rm -f $(NAME)
		$(call GREEN,"The rest too !")

re:		fclean all

.SILENT:
.PHONY:		all clean fclean re 
