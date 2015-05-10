NAME =	test
SRC =	$(shell ls -1 src | grep "cpp")
OBJ =	$(addprefix src/, $(subst .cpp,.o,$(SRC)))

CC		=	g++
FLAGS	=	-Wall -Werror -Wextra

LUAPATH =	lib/lua/

INC		=	-Iinc -I$(LUAPATH) -I$(LUAPATH)/src
LIB		=	-L$(LUAPATH) -llua

.PHONY: all re clean fclean

_depend:
	sh depend.sh
	make $(NAME)

all: _depend

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
	make -C $(LUAPATH) clean
