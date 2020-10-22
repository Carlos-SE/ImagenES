#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>

#include "imagenES.h"

using namespace std;


int AplicarTransformacionLineal(int indice, unsigned char *imagen, int nmin, int omin, float cociente);

int main(int argc, char *argv[]){

    char *origen, *destino;

    unsigned char *datos;

    int minOrigen = 256, maxOrigen = -1;
    int minSalida, maxSalida;

    TipoImagen tipo;
    unsigned char *image;
    int fils, cols;// Num. de filas y columnas de las imagenes

    // Comprobar validez de la llamada
    if (argc != 5){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: negativo <FichImagenOriginal> <FichImagenDestino>\n";
        exit (1);
    }

    origen  = argv[1];
    destino = argv[2];
    minSalida = atoi(argv[3]);
    maxSalida = atoi(argv[4]);

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

  
    float cociente = (maxSalida-minSalida)/(maxOrigen-minOrigen);   //variable para evitar operaciones innecesarias

    int nuevoColor;
    for (int i = 0; i < fils*cols; i++){
        nuevoColor = AplicarTransformacionLineal(i,image,minSalida, minOrigen, cociente);
        image[i] = nuevoColor;
    }

    bool escribir;

    escribir = EscribirImagenPGM(destino, image, fils, cols);

}
/**
 * @brief Devuelve el valor de gris que tendrá el pixel después de aplicar la transformación lineal
 * 
 * @param indice es el índice por el cual se guiará @a *imagen
 * @param *imagen es el conjunto de datos
 * @param nmin es el valor mínimo que tendrá el archivo de salida
 * @param omin es el valor mínimo que tiene el archivo de entrada
 * @param coeficiente es el valor de (max - min)/(b - a) declarado en el main para evitar repetición de cálculos
 * @return Devuelve un entero que será el valor de la escala de gris del pixel
 */
int AplicarTransformacionLineal(int indice, unsigned char *imagen, int nmin, int omin, float cociente){

    int color = imagen[indice];
    int colorSalida;

    colorSalida = round(nmin + (cociente*(color-omin)));

    return colorSalida;

}