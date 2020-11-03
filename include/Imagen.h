/**
  * @file imagenES.h
  * @brief Fichero cabecera para la E/S de imágenes
  *
  * Permite la E/S de archivos de tipo PGM,PPM
  *
  */

#ifndef _IMAGEN_ES_H_
#define _IMAGEN_ES_H_

using namespace std;

typedef unsigned char byte;

class Imagen{
private:
  byte ** img;
  int fils;
  int cols;  

public:


    //@brief Constructor por defecto
  Imagen();

  /**@brief Constructor de copia.
  *@param J puntero a Imagen.
  */
  Imagen (const Imagen &J);

  /* *@brief Crea una imagen con el tamanio.
  *@param filas numero de filas en la imagen a crear.
  *@param columnas numero de columnas a en la imagen a crear
  *@pre filas > 0 y columnas > 0
  *@post La imagen creada contiene filas filas y cols columnas
  *@post La imagen creada contiene valores "basura " (no esta inicializada)
  */
  Imagen (int filas, int columnas);
    
  /**@brief Operador de tipo destructor.

    El proposito es liberar los recursos ocupados por la imagen
  *@post Devuelve: nada.
  *@post La imagen destruida no puede volver a usarse, salvo que se vuelva a realizar sobre ella
otra operación Imagen().
  */
  ~Imagen();



  /**@brief Calcula el numero de filas de la imagen
  * @post Devuelve: Número de filas de la imagen
  * @post La imagen no se modifica 

  */
  int num_filas () const;

  /**@brief Calcula el numero de columnas de la imagen
  * @post Devuelve: Número de columnaas de la imagen
  * @post La imagen no se modifica 

  */
  int num_columnas () const ;

  /** @brief Asignar el valor de luminosidad valor a la casilla (fila, col) de la imagen.
  *
  * @param fila y col son las coordenadas de la casilla
  * @param valor = valor de la luminosidad a asignar en el pixel.
  *
  * @pre 0 <= fila < num_filas ()
  * @pre 0 <= col < num_columnas ().
  * @pre 0 <= col < num_columnas ().
  *
  * @post Devuelve: nada.
  * @post La imagen se modifica. Concretamente, se cambia el valor de la casilla (fila, col) de
    la imagen por el especificado con valor. Los restantes puntos no se modifican.
 
  */
  void asigna_pixel (int fila, int col, byte valor);

  /** @brief Consultar el valor de luminosidad de la casilla (fila, col) de la imagen
  * @param fila y col son las coordenadas de la casilla que se está consultando
  *
  * @pre 0 <= fila < num_filas ()
  * @pre 0 <= col < num_columnas ()
  *
  * @post Devuelve: El valor de luminosidad de la casilla (fila, col) de la imagen, que está en
      el conjunto {0,1, ...., 255}.
  * @post La imagen no se modifica

  */
  byte valor_pixel (int fila, int col) const;

  

//Métodos extra privados
private:

/**
  * @brief Reserva memoria para una imagen de tamaño fils y cols
  * 
  * @param fils son la cantidad de filas que hay que reservar
  * @param cols son la cantidad de columnas que hay que reservar
  */
void Reservar (int filas, int columnas);

/* *
  * @brief Copia los datos de la imagen obtenida como parámetro
  * 
  * @param otra es una referencia a la imagen que queremos copiar
*/


void Copiar (const Imagen & otra);


/* *
  *@brief Libera la memoria de la imagen, borra los datos y 
    deja todos los parametros a 0

*/
void Liberar ();

};
