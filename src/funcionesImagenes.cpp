#include "funcionesImagenes.h"
#include "imagenES.h"
#include <iostream>
#include <cmath>

using namespace std;

int AplicarTransformacionLineal(int indice, unsigned char *imagen, int nmin, int omin, double cociente){

    int color = imagen[indice];
    int colorSalida;

    colorSalida = round(nmin + (cociente*(color-omin)));

    return colorSalida;

}

void AumentoContraste(char *entrada, char *salida, int min, int max){
	char *origen = entrada, *destino = salida;

    unsigned char *datos;

    int minOrigen = 256, maxOrigen = -1;
    int minSalida = min, maxSalida = max;

    TipoImagen tipo;
    unsigned char *image;
    int fils, cols;// Num. de filas y columnas de las imagenes

    cout << endl << "Fichero de entrada: " << origen << endl;
    cout << endl << "Fichero de salida: " << destino << endl;

    tipo = LeerTipoImagen(origen);

    switch(tipo){
        case IMG_PGM:
            image = LeerImagenPGM(origen, fils, cols);
            break;
        case IMG_PPM:
            image = LeerImagenPPM(origen, fils, cols);
            break;
        default:
            cerr << "Error: No pudo leerse la imagen." << endl;
            cerr << "Terminando la ejecucion del programa." << endl;
            exit (1);
    }

    if(!image){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        exit (1);
    }

    cout << "Dimensiones de " << origen << ":" << endl;
    cout << "   Imagen   = " << fils  << " filas x " << cols << " columnas " << endl;

    //Hallar los valores mínimo y máximo de la imagen

    for (int i = 0; i < fils*cols; i++){
        if (image[i] < minOrigen){
            minOrigen = image[i];
        }
        if (image[i] > maxOrigen){
            maxOrigen = image[i];
        }
    }

    double numerador = (maxSalida-minSalida)/1.0;
    double denominador = (maxOrigen-minOrigen)/1.0;
    double cociente = numerador/denominador;   //variable para evitar operaciones innecesarias
    
    for (int i = 0; i < fils*cols; i++){
        image[i] = AplicarTransformacionLineal(i,image,minSalida, minOrigen, cociente);
    }

    bool escribir;

    escribir = EscribirImagenPGM(destino, image, fils, cols);
}

void Umbral(char *entrada, char *salida, int min, int max){
	char *origen = entrada, *destino = salida; // nombres de los ficheros

  	unsigned char *image;
	  int nf, nc, npixeles; // Num. de filas y columnas de las imagenes

  	int T_1 = min;
  	int T_2 = max;

  	cout << endl;
  	cout << "Fichero origen: " << origen << endl;
  	cout << "Fichero resultado: " << destino << endl;
    cout << "Umbral inferior: " << T_1 << endl;
    cout << "Umbral superior: " << T_2 << endl;


  	image = LeerImagenPGM (origen, nf, nc);
  	
  	if (!image){
   		cerr << "Error: No pudo leerse la imagen." << endl;
    	cerr << "Terminando la ejecucion del programa." << endl;
    	exit (1);
  	}

  	// Mostrar los parametros calculados por LeerImagenPGM()
  	cout << endl;
  	cout << "Dimensiones de " << origen << ":" << endl;
  
  	cout << "   Imagen   = " << nf  << " filas x " << nc << " columnas " << endl;

 	//Calcular la imagen ubral
 	
 	npixeles = nf*nc;

 	for ( int i = 0; i < npixeles; i++){
 		if (image[i] <= T_1 || image[i] >= T_2){
 			image [i] = 255;
 		} 
 	}

 	//Guardar la imagen resultante en el fichero destino:
 	if (EscribirImagenPGM (destino, image, nf, nc))
    	cout  << "La imagen se guardo en " << destino << endl;
  	else{
    	cerr << "Error: No pudo guardarse la imagen." << endl;
   		cerr << "Terminando la ejecucion del programa." << endl;
    	exit (2);
  	}

  	// Liberar la imagen
  	delete [] image;
}