#include <iostream>
#include <cstring>
#include <cstdlib>

#include <imagenES.h>
#include <Imagen.h>

using namespace std;

//typedef unsigned char unsigned char;

int main (int argc, char *argv[]){

	char *origen, *destino; // nombres de los ficheros

	unsigned char *image;

	int nf, nc; // Num. de filas y columnas de las imagenes
	
  	// Comprobar validez de la llamada
 	if (argc != 7){
    	cerr << "Error: Numero incorrecto de parametros.\n";
    	cerr << "Uso: zoom <FichImagenOriginal> <FichImagenDestino> <x1> <y1> <x2> <y2>\n";
    	exit (1);
  	}

  	int x1 = atoi(argv[3]);
	int y1 = atoi(argv[4]);
	int x2 = atoi(argv[5]);
	int y2 = atoi(argv[6]);

  	if (x1 > x2 || y1 > y2){
  		cerr << "Error: coordenadas erroneas.\n";
  		cerr << "x1 < x2 y y1 < y2 \n";
  		exit(1);  		
  	}

  	int n_dif_x = x2 - x1; //El numero de columnas de diferencia entre las coordenadas.
  	int n_dif_y = y2 - y1; //El numero de filas de diferencia entre las coordenadas.
 
  	if(n_dif_y != n_dif_x){
  		cerr << "Error: argumentos no validos. \n";
  		cerr << "Las coordenadas obtenidas deben de dar una imagen cuadrada.";
  		exit(1);
  	}

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

  	int nf_dest = (2*n_dif_x)-1;
  	int nc_dest = (2*n_dif_y)-1;

  	Imagen image_dest(nf_dest, nc_dest);

  	int inicio = x1 * y1;
  	int contador= 0;;

  	//Crear la imagen con los valores originales y los huecos necesarios

  	for(int i = 0; i < nf_dest; i++ ){		
  		if (i%2 == 1){						//Si es impar
  			i++;
  		}

  		for (int j = 0; j < nc_dest; j++){
  			if (j%2 == 0 ){				//Si es par	
  				image_dest.asigna_pixel(i,j, image[inicio+contador]);
  				contador++;
  			}
  		}
  	}

  	double media;

  	//Rellenar los valores de la ampliacion en las filas pares

  	for (int i = 0; i < nf_dest; i+=2){
  		for(int j = 0; j < nc_dest; j++){
  			if(j%2 == 1){	//Si es impar
  				media = (image_dest.valor_pixel(i, j-1) + image_dest.valor_pixel(i, j+1))/2;
  				image_dest.asigna_pixel(i, j, media);
  			}
  		}
  	}
  	//Rellenar los valores restantes de la imagen

  	for(int i = 0; i < nf_dest; i++ ){	
  		
  		if (i % 2 == 1){ 	//Si es par, saltamos esta fila, ya está completa
  			for (int j = 0; j < nc_dest; j++){ 
				media = (image_dest.valor_pixel(i+1, j)+ image_dest.valor_pixel(i-1,j))/2;

  				image_dest.asigna_pixel(i, j, media);  			
  			}
  		}
  	}
  	
  	unsigned char *image_final = new unsigned char [nc_dest*nf_dest];

  	for(int i = 0; i < nf_dest; i++ ){
  		for(int j = 0; j < nc_dest; j++){
  			
  			image_final[i*nc_dest + j] = image_dest.valor_pixel(i,j); 
  		}
  	}

  	// Mostrar los parametros calculados por LeerImagenPGM()
  	cout << endl;
  	cout << "Dimensiones de " << origen << ":" << endl;
  
  	cout << "   Origen   = " << nf << " filas x " << nc << " columnas " << endl;

  	if (EscribirImagenPGM (destino, image_final, nf_dest, nc_dest))
    	cout  << "La imagen se guardo en " << destino << endl;
  	else{
    	cerr << "Error: No pudo guardarse la imagen." << endl;
   		cerr << "Terminando la ejecucion del programa." << endl;
    	exit (2);
  	}

  	delete [] image_final;
  	delete [] image;

  	return(0);
}