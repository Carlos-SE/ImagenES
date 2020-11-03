ME = .
BIN = $(HOME)/bin
INCLUDE = $(HOME)/include
OBJ = $(HOME)/obj
SRC = $(HOME)/src

all : $(BIN)/test_imagen clean


$(BIN)/test_imagen : $(OBJ)/test_imagen.o $(OBJ)/funcionesImagenes.o $(OBJ)/Imagen.o $(OBJ)/imagenES.o
	g++ -o $(BIN)/test_imagen $(OBJ)/test_imagen.o $(OBJ)/funcionesImagenes.o $(OBJ)/Imagen.o $(OBJ)/imagenES.o

$(OBJ)/test_imagen.o : $(SRC)/test_imagen.cpp
	g++ -c -o   $(OBJ)/test_imagen.o  $(SRC)/test_imagen.cpp -I$(INCLUDE)

$(OBJ)/funcionesImagenes.o : $(SRC)/funcionesImagenes.cpp
	g++ -c -o $(OBJ)/funcionesImagenes.o $(SRC)/funcionesImagenes.cpp -I$(INCLUDE)

$(OBJ)/Imagen.o : $(SRC)/Imagen.cpp
	g++ -c -o $(OBJ)/Imagen.o $(SRC)/Imagen.cpp -I$(INCLUDE)

$(OBJ)/imagenES.o : $(SRC)/imagenES.cpp
	g++ -c -o $(OBJ)/imagenES.o $(SRC)/imagenES.cpp -I$(INCLUDE)

clean :
	rm $(OBJ)/*.o

mrproper : clean
	rm $(BIN)./*
