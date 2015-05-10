NAME =	test
SRC =	$(shell ls -1 src | grep "cpp")
OBJ =	$(addprefix src/, $(subst .cpp,.o,$(SRC)))

CC		=	g++
FLAGS	=	-Wall -Werror -Wextra

INC		=	-Iinc

LIB		=	-llua5.2

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LIB)

src/%.o: src/%.cpp
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

re: fclean all

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)
