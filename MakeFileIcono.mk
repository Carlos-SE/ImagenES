HOME = .
BIN = $(HOME)/bin
INCLUDE = $(HOME)/include
OBJ = $(HOME)/obj
SRC = $(HOME)/src



all : presentacion $(BIN)/icono clean

presentacion :
	@echo
	@echo "    ______________  _   ______" 
	@echo "   /  _/ ____/ __ \\/ | / / __ \\"
	@echo "   / // /   / / / /  |/ / / / /"
	@echo " _/ // /___/ /_/ / /|  / /_/ /"
	@echo "/___/\____/\____/_/ |_/\____/"
	@echo

$(BIN)/icono : $(OBJ)/icono.o $(OBJ)/imagen.o
	g++ -o $(BIN)/icono $(OBJ)/icono.o $(OBJ)/imagen.o

$(OBJ)/icono.o : $(SRC)/icono.cpp
	g++ -c -o $(OBJ)/icono.o $(SRC)/icono.cpp -I$(INCLUDE)


$(OBJ)/imagen.o : $(SRC)/imagenES.cpp
	g++ -o $(OBJ)/imagen.o -c $(SRC)/imagenES.cpp -I$(INCLUDE)

clean :
	rm $(OBJ)/*.o