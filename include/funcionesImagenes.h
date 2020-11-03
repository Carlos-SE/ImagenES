#ifndef FUNC_IMAGEN
#define FUNC_IMAGEN

int AplicarTransformacionLineal(int indice, unsigned char *imagen, int nmin, int omin, double cociente);
void AumentoContraste(char *entrada, char *salida, int min, int max);
void Umbral(char *entrada, char *salida, int min, int max);


#endif