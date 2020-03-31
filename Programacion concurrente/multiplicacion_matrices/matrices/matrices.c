#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "matrices.h"

void PedirDatos(int *fila,int *columna, int *fila2)
{
    printf("Filas :");
    scanf("%d",&(*fila));
    printf("Columnas :");
    scanf("%d",&(*columna));
    printf("Filas mat2: ");
    scanf("%d",&(*fila2));
}

void LlenarMatriz(int **matriz,int filas, int columnas)
{
    srand(time(NULL));

    for(int i = 0; i < filas; ++i)
        for(int j = 0; j < columnas; ++j)
            matriz[i][j] = rand() % 5 + 1;
}

void ImprimirMatriz(int **matriz,int filas, int columnas)
{
    printf("\n");
    for(int i = 0; i < filas; ++i)
    {
        printf("\n\t");
        for(int j = 0; j < columnas; ++j)
            printf("[%*d] ",2,matriz[i][j]);
    }
    printf("\n");
}

int ReservarMemoria(int ***matriz,int filas, int columnas)
{
    *matriz = (int**)malloc(filas*sizeof(int*));
    for(int i = 0; i < filas; ++i)
        (*matriz)[i] = (int*)malloc(columnas*sizeof(int));
}

void MultiplicarFila(int fila[],int **matriz, int filas, int columnas,long res[])
{
    int temp;
    for(int i = 0; i < columnas; ++i)
    {
        temp = 0;
        for(int j = 0 ; j < filas; ++j) 
        {
            temp += (fila[j] * matriz[j][i]);
            res[i] = temp; 
        }
    }
}

void ImprimirFila(int fila[],int tam)
{
    printf("\n");
    for(int i = 0; i < tam; ++i)
        printf("[%*d]",2,fila[i]);
    printf("\n");
}
