#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "imagenES.h"

using namespace std;

unsigned char **GetMatriz(unsigned char * datos, int fils, int cols);
unsigned char GetValorMedioFilas(unsigned char **datos, int factor_filas, int posicion, int pixeles_completos, int cols);
unsigned char GetValorMedioCols(unsigned char **datos, int factor_cols, int posicion, int pixeles_completos, int fila);
void GetVector (unsigned char * & vector, unsigned char **matriz, int fils, int cols);

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
    nfils = atoi(argv[3]);
    ncols = nfils;

    cout << endl << "Fichero de entrada: " << origen << endl;
    cout << endl << "Fichero de salida: " << destino << endl;

    tipo = LeerTipoImagen(origen);

    switch(tipo){
        case IMG_PGM:
            image = LeerImagenPGM(origen, fils, cols);
            break;
        case IMG_PPM:
            cerr << "Error: La imagen es formato PPM." << endl;
            cerr << "Terminando la ejecucion del programa." << endl;
            exit (2);
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

    unsigned char **ImagenMatriz = GetMatriz(image, fils, cols);

    //MATRIZ DE PASO. ES UNA MATRIZ DINÁMICA QUE SE UTILIZA PARA FACILITAR LOS CÁSCULOS
    // filasSalida X colsEntrada
    unsigned char **MatrizPaso = new unsigned char*[nfils];
    for (int i = 0; i < nfils; i++){
        MatrizPaso[i] = new unsigned char[cols];
    }

    unsigned char **MatrizFinal = new unsigned char*[nfils];
    for (int i = 0; i < nfils; i++){
        MatrizFinal[i] = new unsigned char[ncols];
    }

    int filas_completas = nfils*p_conversion_f;
    int cols_completas = ncols*p_conversion_c;
    int filas_sobra = fils - (filas_completas);
    int cols_sobra = cols - (cols_completas);

    for (int j = 0; j < cols; j++){
        for (int i = 0; i < nfils; i++){
            if (i < nfils-filas_sobra){
                MatrizPaso[i][j] = GetValorMedioFilas(ImagenMatriz, p_conversion_f, i, filas_completas, j);
                cout << "LLega aqui ln 101" << endl;
            }
            else{
                MatrizPaso[i][j] = GetValorMedioFilas(ImagenMatriz, p_conversion_f+1, i, filas_completas, j);
            }
        }
    }

    for (int i = 0; i < nfils; i++){
        for (int j = 0; j < ncols; j++){
            if (j < ncols-cols_sobra){
                MatrizFinal[i][j] = GetValorMedioCols(MatrizPaso, p_conversion_c, j, cols_completas, i);
            }
            else{
                MatrizFinal[i][j] = GetValorMedioCols(MatrizPaso, p_conversion_c+1, j, cols_completas, i);
            }
        }
    }

    unsigned char *resultado;
    cout << "Llega hasta antes de getVector" << endl;
    GetVector(resultado, MatrizFinal, nfils, ncols);
    cout << "Hace el getVector" << endl;
    EscribirImagenPGM (destino, resultado, nfils, ncols);
    cout << "Escribe los datos" << endl;

}

// FUNCIÓN QUE CONVIERTE EL VECTOR DE DATOS DE LA IMAGEN EN UNA MATRIZ
// LO QUE PERMITE TRABAJAR DE FORMA MÁS SENCILLA CON LOS DATOS

unsigned char **GetMatriz(unsigned char * datos, int fils, int cols){
    unsigned char **Matriz = new unsigned char*[fils];
    for (int i = 0; i < fils; i++){
        Matriz[i] = new unsigned char[cols];
    }

    int contador = 0;
    for (int i = 0; i < fils; i++){
        for (int j = 0; j < cols; j++){
            Matriz[i][j] = datos[contador];
            contador++;
        }
    }

    return Matriz;
}

/*

FUNCIÓN QUE DEVUELVE LOS VALORES MEDIOS DE CADA PIXEL, HECHO PARA LLAMARLO DENTRO DE UN BUCLE FOR CON CONDICIONES INCLUIDAS PARA
SABER CUANDO PONER FACTOR O FACTOR+1

DEVUELVE EL VALOR INDIVIDUAL PARA UNA AMTRIZ DE PASO

*/

unsigned char GetValorMedioFilas(unsigned char **datos, int factor_filas, int posicion, int pixeles_completos, int col){
    int origen;

    if (posicion < pixeles_completos){
        origen = factor_filas*posicion;
    }
    else{
        origen = 0;
        for (int i = 0; i < pixeles_completos; i++){
            origen += factor_filas-1;     // -1 porque si es en una posicion mayor a los pixeles completos se llamará con factor = factro + 1
        }
        for (int i = pixeles_completos; i < posicion; i++){
            origen =+ factor_filas;
        }
    }

    unsigned char valor = datos[origen][col];
    for (int i = 1; i < factor_filas; i++){
        valor += datos[origen+i][col];
    }

    valor = valor/factor_filas;

    return valor;
}

unsigned char GetValorMedioCols(unsigned char **datos, int factor_cols, int posicion, int pixeles_completos, int fila){
     int origen = 0;

     if(posicion < pixeles_completos){
         origen = (factor_cols*posicion);
     }
     else{
         for (int i = 0; i < pixeles_completos; i++){
             origen += factor_cols-1;
         }
         for (int i = pixeles_completos; i < posicion; i++){
             origen += factor_cols;
         }
     }

     unsigned char valor = datos[fila][origen];

     for (int i = 1; i < factor_cols; i++){
         valor += datos[fila][origen+i];
     }

     valor = valor/factor_cols;

     return valor;
}

void GetVector (unsigned char * & vector, unsigned char **matriz, int fils, int cols){
    for (int i = 0; i < fils; i++){
        for (int j = 0; j < cols; j++){
            vector[(i*cols)+cols] = matriz[i][j];
        }
    }
}