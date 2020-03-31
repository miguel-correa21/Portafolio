#ifndef _MEMORIA_H
#define _MEMORIA_H

#define NUM_SECC_CRT 5

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct
{
    int vacio;
    char msg[12];

}seccion_crt[NUM_SECC_CRT];

seccion_crt * crear_ligar_mem(key_t llave_mem,int *memid);
int crear_ligar_sem(key_t llave);
void Inicializar_mem(seccion_crt *ptr);

#endif
