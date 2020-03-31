#ifndef _SEMAFOROS_H
#define _SEMAFOROS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define NUM_SEM 10
#define SEM_WRITE1 0
#define SEM_READ1 1
#define SEM_WRITE2 2
#define SEM_READ2 3
#define SEM_WRITE3 4
#define SEM_READ3 5
#define SEM_WRITE4 6
#define SEM_READ4 7
#define SEM_WRITE5 8
#define SEM_READ5 9


void esperar(int numsem,int semid);
void avisar(int numsem,int semid);
int crear_ligar_sem(key_t llave);

#endif
