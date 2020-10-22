all : Aumento clean

Aumento : aumentocontraste.o imagen.o
	g++ -o Aumento aumentocontraste.o imagen.o

aumentocontraste.o : aumentocontraste.cpp
	g++ -c -o aumentocontraste.o aumentocontraste.cpp -I./

imagen.o : imagenES.cpp
	g++ -o imagen.o -c imagenES.cpp

clean :
	rm ./*.o
