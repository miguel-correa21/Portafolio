#include "Imagen.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int crear_procesos(Imagen *img, Imagen *filtrada,char filtro);

int main(int arc , char *argv[])
{
    Imagen img,roja,verde,azul;
    Leer(argv[1],&img);
    Inicializar(&roja,img.base,img.altura);
    Inicializar(&verde,img.base,img.altura);
    Inicializar(&azul,img.base,img.altura);

    crear_procesos(&img,&roja,'r');
    crear_procesos(&img,&verde,'g');
    crear_procesos(&img,&azul,'b');

    printf("creando el archivo rojo.ppm...\n");
    Escribir("rojo.ppm",&roja);
    printf("Creando el archivo verde.ppm...\n");
    Escribir("verde.ppm",&verde);
    printf("Creando el el archivo Azul.ppm...\n");
    Escribir("Azul.ppm",&azul);
    printf("Listo...\n");
    return 0;
}

int crear_procesos(Imagen *img, Imagen *filtrada,char filtro)
{
    pid_t id;
    int tuberia[2];
    Imagen buf;
    Inicializar(&buf,img->base,img->altura);
    pipe(tuberia);

    id = fork();
    if(id == 0)
    {
        printf("realizando Filtrado %c desde el procesos id:%d\n",filtro,getpid());
        Filtro_RGB(filtro,img,&buf);
        for(int i = 0; i < buf.altura; ++i)
            for(int j = 0; j < buf.base; ++j)
                write(tuberia[1],&(buf.matriz[i][j]),sizeof(Pixel));

        close(tuberia[0]);
        close(tuberia[1]);
        exit(0);
    }
    else if( id == -1)
    {
        printf("Error al crear proceso\n");
        exit(-1);
    }
    else
    {
        for(int i = 0; i < img->altura; ++i)
            for(int j = 0;j < img->base; ++j)
            {
                read(tuberia[0],&(buf.matriz[i][j]),sizeof(Pixel));
                AsignarPixel(&(filtrada->matriz[i][j]),
                        buf.matriz[i][j].r,
                        buf.matriz[i][j].g,
                        buf.matriz[i][j].b
                        );
            }


        int estado;
        wait(&estado);

        close(tuberia[0]);
        close(tuberia[1]);
    }
}
