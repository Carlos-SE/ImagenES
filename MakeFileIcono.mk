all : icono clean

icono : icono.o imagen.o
	g++ -o icono icono.o imagen.o

icono.o : icono.cpp
	g++ -c -o icono.o icono.cpp -I./


imagen.o : imagenES.cpp
	g++ -o imagen.o -c imagenES.cpp -I./

clean :
	rm ./*.o