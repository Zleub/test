NAME =	test
SRC =	$(shell ls -1 src | grep "cpp")
OBJ =	$(addprefix src/, $(subst .cpp,.o,$(SRC)))

CC		=	g++
FLAGS	=	-Wall -Werror -Wextra

INC		=	-Iinc -Ilua/src

LIB		=	-Llua -llua

.PHONY: all re clean fclean

_depend:
	sh depend.sh

all: _depend $(NAME)

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
	rm -rf lua/liblua.dylib
	rm -rf lua/lua
	rm -rf lua/luac
