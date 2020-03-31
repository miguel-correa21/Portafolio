#include "memoria.h"

seccion_crt * crear_ligar_mem(key_t llave_mem,int *memid)
{
    int i= 0;
    seccion_crt *ptr = NULL;

    if((*memid = shmget(llave_mem,sizeof(seccion_crt),IPC_CREAT | IPC_EXCL| 0600)) == -1)
    {

    //ligando a la memoria
        if((*memid = shmget(llave_mem,sizeof(seccion_crt), 0600)) == -1)
        {
            printf("no se puede ligar con la memoria\n");
            exit(-1);
        }
        else
            printf("productor se ligo a memoria\n");
    }
    else
        printf("productor creo memoria\n");

    if((ptr = (seccion_crt *)shmat(*memid,0,0)) == NULL)
    {
        printf("no se pude crear memoria compartida\n");
        exit(-1);
    }
    return ptr;
}

void Inicializar_mem(seccion_crt *ptr)
{
    for(int i = 0; i < NUM_SECC_CRT; ++i)
        ptr[i]->vacio = 1;
}

