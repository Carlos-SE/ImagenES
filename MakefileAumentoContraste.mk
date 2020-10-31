HOME = .
BIN = $(HOME)/bin
INCLUDE = $(HOME)/include
OBJ = $(HOME)/obj
SRC = $(HOME)/src


all : $(BIN)/Aumento clean

$(BIN)/Aumento : $(OBJ)/aumentocontraste.o $(OBJ)/imagen.o
	g++ -o $(BIN)/Aumento $(OBJ)/aumentocontraste.o $(OBJ)/imagen.o

$(OBJ)/aumentocontraste.o : $(SRC)/aumentocontraste.cpp
	g++ -c -o $(OBJ)/aumentocontraste.o $(SRC)/aumentocontraste.cpp -I$(INCLUDE)

$(OBJ)/imagen.o : $(SRC)/imagenES.cpp
	g++ -o $(OBJ)/imagen.o -c $(SRC)/imagenES.cpp -I$(INCLUDE)

clean :
	rm $(OBJ)/*.o