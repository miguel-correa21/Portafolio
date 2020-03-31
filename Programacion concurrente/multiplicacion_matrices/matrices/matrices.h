#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void LlenarMatriz(int **matriz,int filas, int columnas);
void MultiplicarFila(int fila[],int **matriz, int filas, int columnas,long res[]);
void PedirDatos(int *fila,int *columna,int *filas2);
void ImprimirMatriz(int **matriz,int filas, int columnas);
int ReservarMemoria(int ***matriz,int filas, int columnas);
void ImprimirFila(int fila[],int tam);
