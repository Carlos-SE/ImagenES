#include <fstream>
#include <string>
#include <iostream>

#include "Imagen.h"

using namespace std;


// _____________________________________________________________________________

Imagen::Imagen(){
  fils = cols = 0;
  img = 0;
}

// _____________________________________________________________________________

Imagen::Imagen(const Imagen &J){
  if (this != &J){
    Liberar();
    Reservar (J.fils, J.cols);
    Copiar (J);
  }
}
// _____________________________________________________________________________

Imagen::Imagen(int filas, int columnas){
  fils = filas;
  cols = columnas;
  Reservar(fils, cols);
} 

// _____________________________________________________________________________

Imagen :: ~Imagen(){
  Liberar();
}

// _____________________________________________________________________________

int Imagen :: num_filas() const{
  return fils;
}

// _____________________________________________________________________________

int Imagen :: num_columnas () const {
  return cols;
}

// _____________________________________________________________________________

void Imagen :: asigna_pixel (int fila, int col, byte valor){
  img [fila][col] = valor;
}

// _____________________________________________________________________________

byte Imagen :: valor_pixel (int fila, int col) const {
  return img[fila][col];
}

//Métodos privados:

void Imagen :: Reservar (int filas, int columnas){
  fils = filas;
  cols = columnas;

  if (fils >= 0 && cols >= 0){
    img = new byte *[fils];

    for(int i = 1; i < fils; i ++){
      img [i] = new byte [cols];
    }
  }
  else
    img = 0;

}

void Imagen :: Copiar (const Imagen & otra){
  for (int i = 0; i < fils; i++){
    for (int j =0; j < cols; j++){
      img[i][j] = otra.img[i][j];
    }
    fils = otra.fils;
    cols = otra.cols;

  }
}

void Imagen::Liberar(){
  if (img !=0 ){

    for(int i = 0; i < fils; i++){
      delete[] img[i];
    }

    delete[] img;

    fils = cols = 0;
    img = 0;
  }
}

