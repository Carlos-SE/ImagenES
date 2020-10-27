#include <iostream>
#include <cstring>
#include <cstdlib>

#include <imagenES.h>

using namespace std;

int main (int argc, char *argv[]){
	char *origen, *destino; // nombres de los ficheros

  	unsigned char *image;
	  int nf, nc, npixeles; // Num. de filas y columnas de las imagenes
	  
	  int  x1 = atoi(argv[4]);
	  int  y1 = atoi(argv[5]);
	  int  x2 = atoi(argv[6]);
	  int  y2 = atoi(argv[7]);

  	// Comprobar validez de la llamada
 	if (argc != 7){
    	cerr << "Error: Numero incorrecto de parametros.\n";
    	cerr << "Uso: zoom <FichImagenOriginal> <FichImagenDestino> <x1> <y1> <x2> <y2>\n";
    	exit (1);
  	}

  	if (x1 > x2 || y1 > y2){
  		cerr << "Error: coordenadas erroneas.\n";
  		cerr << "x1 < x2 y y1 < y2 \n";
  		exit(1);  		
  	}

  	int n_dif_x = x2 - x1; //El numero de columnas de diferencia entre las coordenadas.
  	int n_dif_y = y2 - y1; //El numero de filas de diferencia entre las coordenadas.
 
 	origen  = argv[1];
    destino = argv[2];

    cout << endl;
  	cout << "Fichero origen: " << origen << endl;
  	cout << "Fichero resultado: " << destino << endl;
    cout << "Coordenadas esquina superior izq: " << x1 << ", " << y1 << endl;
    cout << "Coordenadas esquina inferior dcha: " << x2 << ", " << y2 << endl;

    image = LeerImagenPGM (origen, nf, nc);

    if (!image){
   		cerr << "Error: No pudo leerse la imagen." << endl;
    	cerr << "Terminando la ejecucion del programa." << endl;
    	exit (1);
  	}

  	// Mostrar los parametros calculados por LeerImagenPGM()
  	cout << endl;
  	cout << "Dimensiones de " << origen << ":" << endl;
  
  	cout << "   Origen   = " << nf  << " filas x " << nc << " columnas " << endl;

  	if (EscribirImagenPGM (destino, image, n_dif_y, n_dif_y))
    	cout  << "La imagen se guardo en " << destino << endl;
  	else{
    	cerr << "Error: No pudo guardarse la imagen." << endl;
   		cerr << "Terminando la ejecucion del programa." << endl;
    	exit (2);
  	}
}