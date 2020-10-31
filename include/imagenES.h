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

/**
  * @brief Tipo de imagen
  *
  * Declara una serie de constantes para representar los distintos tipos
  * de imágenes que se pueden manejar.
  *
  * @see LeerTipoImagen
  */
enum TipoImagen {IMG_DESCONOCIDO, IMG_PGM, IMG_PPM};

typedef unsigned char byte;

class Imagen{
private:
  byte ** img;
  int fils;
  int cols;
  int num_pixels;
  

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

//Funciones
/**
  * @brief Devuelve el tipo de imagen del archivo
  *
  * @param nombre indica el archivo de disco que consultar
  * @return Devuelve el tipo de la imagen en el archivo
  *
  * @see TipoImagen
  */
  TipoImagen LeerTipoImagen (const char *nombre);

/**
  * @brief Lee una imagen de tipo PPM
  *
  * @param nombre archivo a leer
  * @param filas Parámetro de salida con las filas de la imagen.
  * @param columnas Parámetro de salida con las columnas de la imagen.
  * @return puntero a una nueva zona de memoria que contiene @a filas x @a columnas x 3
  * bytes que corresponden a los colores de todos los píxeles en formato
  * RGB (desde la esquina superior izqda a la inferior drcha). En caso de que no
  * no se pueda leer, se devuelve cero. (0).
  * @post En caso de éxito, el puntero apunta a una zona de memoria reservada en
  * memoria dinámica. Será el usuario el responsable de liberarla.
  */
  unsigned char *LeerImagenPPM (const char *nombre, int& fils, int& cols);

/**
  * @brief Escribe una imagen de tipo PPM
  *
  * @param nombre archivo a escribir
  * @param datos punteros a los @a f x @a c x 3 bytes que corresponden a los valores
  *    de los píxeles de la imagen en formato RGB.
  * @param f filas de la imagen
  * @param c columnas de la imagen
  * @return si ha tenido éxito en la escritura.
  */
  bool EscribirImagenPPM (const char *nombre, const unsigned char *datos, 
                        const int fils, const int cols);

/**
  * @brief Lee una imagen de tipo PGM
  *
  * @param nombre archivo a leer
  * @param filas Parámetro de salida con las filas de la imagen.
  * @param columnas Parámetro de salida con las columnas de la imagen.
  * @return puntero a una nueva zona de memoria que contiene @a filas x @a columnas
  * bytes que corresponden a los grises de todos los píxeles
  * (desde la esquina superior izqda a la inferior drcha). En caso de que no
  * no se pueda leer, se devuelve cero. (0).
  * @post En caso de éxito, el puntero apunta a una zona de memoria reservada en
  * memoria dinámica. Será el usuario el responsable de liberarla.
  */
  unsigned char *LeerImagenPGM (const char *nombre, int& fils, int& cols);

/**
  * @brief Escribe una imagen de tipo PGM
  *
  * @param nombre archivo a escribir
  * @param datos punteros a los @a f x @a c bytes que corresponden a los valores
  *    de los píxeles de la imagen de grises.
  * @param f filas de la imagen
  * @param c columnas de la imagen
  * @return si ha tenido éxito en la escritura.
  */
  bool EscribirImagenPGM (const char *nombre, const unsigned char *datos, 
                        const int fils, const int cols);

#endif

/* Fin Fichero: imagenES.h */
