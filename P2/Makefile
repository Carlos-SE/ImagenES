#############################################################################
#
# ESTRUCTURA DE DATPS
# GRADO EN INGENIERIA INFORMATICA
#
# CURSO 2020 - 2021
#
# makefile para práctica 2 
#
#############################################################################


HOME = .

BIN = $(HOME)/bin
SRC = $(HOME)/src
OBJ = $(HOME)/obj
LIB = $(HOME)/lib
INCLUDE = $(HOME)/include

#................................................
all:  preambulo \
      $(BIN)/umbral \
      $(BIN)/zoom \
	  $(BIN)/icono \
      final

#................................................
preambulo:
	@echo
	@echo ------------------------------------------------------------
	@echo Practica 2
	@echo
	@echo ESTRUCTURA DE DATOS
	@echo Grado en Ingeniería Informática
	@echo
	@echo ANA LUCIA VICO MARTINEZ Y CARLOS SALAS EIROA
	@echo ------------------------------------------------------------
	@echo

#................................................
final: 
	@echo

#................................................
# EJECUTABLES

$(BIN)/umbral : $(OBJ)/umbral.o $(OBJ)/imagenES.o 
	@echo 
	@echo Creando ejecutable: umbral
	@echo 
	g++ -o $(BIN)/umbral $(OBJ)/umbral.o $(OBJ)/imagenES.o -I./include

$(BIN)/zoom: $(OBJ)/zoom.o $(OBJ)/imagenES.o 
	@echo 
	@echo Creando ejecutable: zoom
	@echo 
	g++ -o $(BIN)/zoom $(OBJ)/zoom.o $(OBJ)/imagenES.o -I./include 

$(BIN)/icono : $(OBJ)/icono.o $(OBJ)/imagenES.o 
	@echo 
	@echo Creando ejecutable: icono
	@echo 
	g++ -o $(BIN)/icono $(OBJ)/icono.o $(OBJ)/imagenES.o -I./include


#................................................
# OBJETOS 

$(OBJ)/umbral.o : \
              $(SRC)/umbral.cpp \
              $(INCLUDE)/imagenES.h 
	@echo 
	@echo Creando objeto: umbral.o
	@echo
	g++ -c -o $(OBJ)/umbral.o $(SRC)/umbral.cpp -I$(INCLUDE) -std=c++11

$(OBJ)/zoom.o : $(SRC)/zoom.cpp  $(INCLUDE)/imagenES.h 
	@echo 
	@echo Creando objeto: zoom.o
	@echo 
	g++ -c -o $(OBJ)/zoom.o $(SRC)/zoom.cpp -I$(INCLUDE) -std=c++11

$(OBJ)/icono.o : $(SRC)/icono.cpp  $(INCLUDE)/imagenES.h 
	@echo 
	@echo Creando objeto: icono.o
	@echo 
	g++ -c -o $(OBJ)/icono.o $(SRC)/icono.cpp -I$(INCLUDE) -std=c++11

$(OBJ)/imagenES.o : $(SRC)/imagenES.cpp
	@echo
	@echo Generando archivo objeto: imagenES.OBJ
	@echo 
	g++ -c -o $(OBJ)/imagenES.o $(SRC)/imagenES.cpp -I$(INCLUDE) -std=c++11


#................................................
# LIMPEZA

clean: clean-objs

clean-objs: clean-objetos
	@echo Borrando objetos...

	-rm $(OBJ)/umbral.o
	-rm $(OBJ)/zoom.o	
	-rm $(OBJ)/icono.o
	-rm $(OBJ)/imagenES.o

	@echo ...Borrados objetos
	@echo 

clean-bins : 
	@echo Borrando ejecutables...

	-rm $(BIN)/umbral
	-rm $(BIN)/zoom	
	-rm $(BIN)/icono


	@echo ...Borrados ejecutables

mr.proper:  clean

