#include <iostream>
#include <cstring>
#include <cstdlib>

#include <imagenES.h>


//Hecho por Ana Vico
using namespace std;

int main (int argc, char *argv[]){
	char *origen, *destino; // nombres de los ficheros

  	unsigned char *image;
	  int nf, nc, npixeles; // Num. de filas y columnas de las imagenes

  	// Comprobar validez de la llamada
 	if (argc != 5){
    	cerr << "Error: Numero incorrecto de parametros.\n";
    	cerr << "Uso: umbral <FichImagenOriginal> <FichImagenDestino> <umbral_inf> <umbral_sup>\n";
    	exit (1);
  	}

  	if (argv[3] > argv[4]){
  		cerr << "Error: Intervalo erróneo.\n";
  		cerr << "Uso: umbral <FichImagenOriginal> <FichImagenDestino> <umbral_inf> <umbral_sup>\n";
  		exit (1);
  	}

  	origen  = argv[1];
    destino = argv[2];

  	int T_1 = atoi(argv[3]);
  	int T_2 = atoi(argv[4]);

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

  	return (0);
}
