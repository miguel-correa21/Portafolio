#include "archivo.h"
#include <stdlib.h>

char *telef[4] = {"55585558","77777777","88888888","99999999"};
char *mens[4] = { "usuario1","usuario2","usuario3","usuario4"};

void crear_archivos()
{
    for(int i = 0; i < 4; i++)
    {
        FILE *tel,*msg;
        if((tel = fopen(telef[i],"w")) == NULL ||
                (msg = fopen(mens[i],"w")) == NULL)
        {
            printf("no se puede crear el archivo :%s\n",telef[i]);
            printf("no se puede crear el archivo :%s\n",mens[i]);
            exit(-1);
        }
        else
        {
            printf("Se creo el archivo: %s con exito\n",telef[i]);
            printf("Se creo el archivo: %s con exito\n",mens[i]);
            fclose(tel);
            fclose(msg);
        }
    }
}
void guardar_datos(char *dato)
{
    FILE *ptr;
    if((ptr = fopen(dato,"a")) == NULL)
    {
        printf("No se puede abrir el archivo:%s\n",dato);
        exit(-1);
    }
    else
    {
        fprintf(ptr,"%s\n",dato);
        fclose(ptr);
    }

}

