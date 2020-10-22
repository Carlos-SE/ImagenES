#include <iostream>
#include <cstring>
#include <cstdlib>
#include <imagenES.h>

using namespace std;

int main (int argc, char *argv[]){
    /*
    EL RESULTADO SERÁ DE N*N
    */
 
    char *origen, *destino; // nombres de los ficheros

    unsigned char *datos;

    TipoImagen tipo;
    unsigned char *image;
    int fils, nfils, cols, ncols, npixeles; // Num. de filas y columnas de las imagenes

    // Comprobar validez de la llamada
    if (argc != 4){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: negativo <FichImagenOriginal> <FichImagenDestino>\n";
        exit (1);
    }

    origen  = argv[1];
    destino = argv[2];
    nfils = argv[3];

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

    //Calcular Icono
    int p_conversion_f = fils/nfils;    //pixeles para hacer la transformación de las filas
    int p_conversion_c = cols/nfils;    //pixeles para hacer la transformación de las columnas
    int ntam = nfils*nfils;
    int tam = fils*cols;

    int valor;
    int iteracion = 0;
    int aumento = 0;

    for(int i = 0; i < ntam; i++){
        valor = 0;

        for(int f = 0; j < p_conversion_f; f++){
            for(int c = 0; k < p_conversion_c; c++){

                if ((iteracion+1)%(ncols) == 0 && iteracion > 0){
                    aumento += p_conversion_c*p_conversion_c;
                }
                else{
                    aumento += p_conversion_c;

                    if (iteracion == 0){
                        aumento = 0;
                    }
                }
                valor += image[f*fils + c + aumento /*+ (iteracion%(fils/nfils))**/];
            }
        }

        iteracion++;

        datos[i = valor/(p_conversion_f*p_conversion_c)];
    }


    //ESCRIBIR IMAGEN CON  datos[]

}