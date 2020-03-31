#include "matrices.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct Proceso
{
    pid_t id;
    int inicio_fila;
    int final_fila;

}Proceso;


void Ingresar_num_proc(int *num_proc,int filas);
void Crear_procesos(Proceso p,int **mat1, int **mat2,int filas, int columnas,long **RES);
void AsignarFilas(Proceso p[], int filas, int num_proc);

int main(int argc, char *argv[])
{
    Proceso *procesos;
    int filas,columnas,filas2;
    int num_proc;
    int **mat1,**mat2;
    long **res;

    PedirDatos(&filas,&columnas,&filas2);
    Ingresar_num_proc(&num_proc,filas);
    ReservarMemoria(&mat1,filas,columnas);
    ReservarMemoria(&mat2,columnas,filas2);

    res = (long**)malloc(filas*sizeof(long*));
    for(int i = 0; i < filas; ++i)
        (res)[i] = (long*)malloc(filas2*sizeof(long));

    LlenarMatriz(mat1,filas,columnas);
    LlenarMatriz(mat2,columnas,filas2);
    ImprimirMatriz(mat1,filas,columnas);
    ImprimirMatriz(mat2,columnas,filas2);
    procesos = (Proceso *) malloc(num_proc * sizeof(Proceso));
    AsignarFilas(procesos,filas,num_proc);
    for(int i = 0; i < num_proc; ++i)
        Crear_procesos(procesos[i],mat1,mat2,filas2,columnas,res);
    
    
    printf("\nJuntando... ");
    for(int i = 0; i < filas; ++i)
    {
        printf("\n");
        for(int j = 0; j < filas2; ++j)
        {
            printf("[%d]",res[i][j]);
        }
    }
    free(mat1);
    free(mat2);
    free(res);
    return 0;
}

void Ingresar_num_proc(int *num_proc,int filas)
{
    while(1)
    {
        printf("Número de procesos: ");
        scanf("%d",&(*num_proc));
        if(*num_proc > filas)
        {
            printf("\nEl número de procesos es mayor al número de filas, ");
            printf("Vuelva a ingresar el número de procesos\n");
        }
        else
            break;
    }
}

void Crear_procesos(Proceso p,int **mat1, int **mat2,int filas ,int columnas,long **RES)
{ 
    int fila[p.final_fila][columnas];
    long res[filas];
    int tuberia[2];

    pipe(tuberia);

    for(int i = p.inicio_fila; i <= p.final_fila; ++i)
       for(int j = 0; j < columnas; ++j)
           fila[i][j] = mat1[i][j];
    
    if((p.id = fork()) == 0)
    {
        close(tuberia[0]);
        printf("\n\tProceso %d\n",getpid());
        for(int k = p.inicio_fila; k <= p.final_fila; ++k)
        {
            MultiplicarFila(fila[k],mat2,columnas,filas,res);
            
            //escribir dato por dato de la matriz
            for(int f = 0; f < filas; f++)
                write(tuberia[1],&res[f],sizeof(long));

//            ImprimirFila(res,filas);
        }    
        
        close(tuberia[1]);
        exit(0);
    }
    else
    {
        close(tuberia[1]);
        for(int a = p.inicio_fila; a <= p.final_fila; ++a)
        {   
            //leer todo lo que esta en la tuberia
            for(int z = 0; z < filas; z++)
                read(tuberia[0],&res[z],sizeof(long));

            for(int b = 0; b < filas; ++b)
                RES[a][b] = res[b];
        }

        int estado;
        wait(&estado);

        close(tuberia[0]);
    }
}


void AsignarFilas(Proceso p[], int filas, int num_proc)
{
    int filasAsignadas = filas/num_proc;
    int aux = 0;

    for(int i = 0; i < num_proc; i++)
    {
        p[i].inicio_fila = aux;
        //si la razón no es exacta, el ultimo proceso toma las ultimas filas.
        if(filas % num_proc != 0 && i == (num_proc-1) )
        {
           p[i].final_fila = filas - 1;
        }
        else
        {
            aux += (filasAsignadas - 1);
            p[i].final_fila = aux;
            aux++;
        }
    }
}
