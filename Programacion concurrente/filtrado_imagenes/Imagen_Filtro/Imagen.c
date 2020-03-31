#include "Imagen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100

void Leer(char nombre_imagen[],Imagen *m)
{
    FILE *archivo;
    char linea[TAM];
    char c,salto;
    int altura,base,r,g,b,maximo;

    if((archivo = fopen(nombre_imagen,"rt")) == NULL)
    {
        printf("ERROR AL ABRIR ARCHIVO: revise que el nombre sea correcto\n");
        exit(-1);
    }
    
    fscanf(archivo,"%s",linea);
    if(strcmp(linea,"P3") != 0)
    {
        printf("ERROR FORMATO INVALIDO: revise que el formato del archivo sea .ppm\n");
        exit(-1);
    }
    
    //leer comentarios
    fscanf(archivo,"%c",&c);
    do
    {
       fscanf(archivo,"%c",&c) ;
    }while(c != '\n');

    fscanf(archivo,"%d %d",&base,&altura);
    Inicializar(m,base,altura);
    //leemos el maximo
    fscanf(archivo,"%d",&maximo);

    for(int i = 0; i < altura; ++i)
        for(int j = 0; j < base; ++j)
        {
            fscanf(archivo,"%d",&r);
            fscanf(archivo,"%d",&g);
            fscanf(archivo,"%d",&b);
            AsignarPixel(&(m->matriz[i][j]),r,g,b);
        }

    fclose(archivo);
}

void ReservarMemoria(Imagen *m)
{
    m->matriz = (Pixel**)malloc(m->altura*sizeof(Pixel*));
    for(int i = 0; i < m->altura; ++i)
        m->matriz[i] = (Pixel*)malloc(m->base*sizeof(Pixel));
}

void Escribir(char nombre_imagen[],Imagen *m)
{
    FILE *archivo;
    if((archivo = fopen(nombre_imagen,"w")) == NULL)
    {
        printf("ERROR AL INTENTAR CREAR ARCHIVO:\n");
        exit(-1);
    }

    fprintf(archivo,"P3\n");
    fprintf(archivo,"# Hecho por Miguel Correa\n");
    fprintf(archivo,"%d %d\n",m->base,m->altura);
    fprintf(archivo,"%d\n",255);
    for(int i = 0; i < m->altura; ++i)
    {
        for(int j = 0; j < m->base; ++j)
        {
            fprintf(archivo," %d ",m->matriz[i][j].r);
            fprintf(archivo," %d ",m->matriz[i][j].g);
            fprintf(archivo," %d ",m->matriz[i][j].b);
        }
        fprintf(archivo,"\n");
    }

    fclose(archivo);
}

void Inicializar(Imagen *m,int _base,int _altura)
{
    m->altura = _altura;
    m->base = _base;
    ReservarMemoria(m);

    for(int i = 0; i < m->altura; i++)
    {    
        for(int j = 0; j < m->base; ++j)
        {
            m->matriz[i][j].r = 0;
            m->matriz[i][j].g = 0;
            m->matriz[i][j].b = 0;
        }
    }
}

void Filtro_RGB(char filtro,Imagen *m,Imagen *filtrada)
{
    
    Inicializar(filtrada,m->base,m->altura);

    if(filtro == 'r')    
    {
        for(int i = 0; i < m->altura; ++i)
            for(int j = 0; j < m->base; ++j)
            {
                AsignarPixel(&(filtrada->matriz[i][j]),255,
                            m->matriz[i][j].g,
                            m->matriz[i][j].b);
            }
    }
    else if(filtro == 'g')
    {
        for(int i = 0; i < m->altura; ++i)
            for(int j = 0; j < m->base; ++j)
            {
                AsignarPixel(&(filtrada->matriz[i][j]),
                            m->matriz[i][j].r,
                            255,
                            m->matriz[i][j].b);
            }
    }
    else
    {
        for(int i = 0; i < m->altura; ++i)
            for(int j = 0; j < m->base; ++j)
            {
                AsignarPixel(&(filtrada->matriz[i][j]),
                            m->matriz[i][j].r,    
                            m->matriz[i][j].g,
                            255);
            }
    }

}

void AsignarPixel(Pixel *p, int r, int g, int b)
{
    p->r = r;
    p->g = g;
    p->b = b;
}
void copiarImagen(Imagen *original, Imagen *copia)
{
    Inicializar(copia,original->base,original->altura);

    for(int i = 0; i < original->altura; i++)
        for(int j = 0; j < original->base; ++j)
        {
            copia->matriz[i][j].r = original->matriz[i][j].r;
            copia->matriz[i][j].g = original->matriz[i][j].g;
            copia->matriz[i][j].b = original->matriz[i][j].b;
        }
}
