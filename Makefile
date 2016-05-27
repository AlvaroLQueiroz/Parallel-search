#Compilador
CC = mpicc
NAME = busca_paralela

#Variaveis de diretorios
LIB = ./lib
INCLUDE = ./include
SRC = ./src
OBJ = ./obj

#Opcões de compilação
LIBFLAGS = -l$(NAME)
FLAGS = -Wall -Wextra -pedantic -g

limpeza: principal
	@rm lib/*.a
	@rm obj/*.o

#Cria um biblioteca dinamica com as bibliotecas
principal: biblioteca
	@$(CC) $(SRC)/main.c $(FLAGS) -I$(INCLUDE) -L$(LIB) $(LIBFLAGS) -o $(NAME)

#Compila as bibliotecas
biblioteca:
	@$(CC) -c $(SRC)/*.c $(FLAGS) -I$(INCLUDE)
	@mv *.o obj/
	@ar -cr $(LIB)/lib$(NAME).a $(OBJ)/*.o
