# Compiler
CC = mpicc

# Executable name
NAME = busca_paralela

# Directory of Libraries
LIB = ./lib

# Directory of headers
INCLUDE = ./include

# Directory of source codes
SRC = ./src

# Directory of compileds
OBJ = ./obj

# Flag of librarie
LIBFLAGS = -l$(NAME)

# Other flags
FLAGS = -Wall -Wextra -pedantic -g

clean: main
	@rm lib/*.a
	@rm obj/*.o

#Cria um biblioteca dinamica com as bibliotecas
main: libraries
	@$(CC) $(SRC)/main.c $(FLAGS) -I$(INCLUDE) -L$(LIB) $(LIBFLAGS) -o $(NAME)

# Compile the libraries
libraries:
	@$(CC) -c $(SRC)/*.c $(FLAGS) -I$(INCLUDE)
	@mv *.o $(OBJ)
	@ar -cr $(LIB)/lib$(NAME).a $(OBJ)/*.o
