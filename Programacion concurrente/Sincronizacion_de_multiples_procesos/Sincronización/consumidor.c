#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "memoria.h"
#include "semaforos.h"
#include "archivo.h"

#define SEM_PRODUCTORES 0
#define SEM_CONSUMIDORES 1
#define NUM_PROC 2
#define NUM_SECC_CRT 5

#define CONSUMO 13333

int leer(seccion_crt *ptr, int semid, int np);

int main(int argc, char **argv)
{
    key_t llave_tel, llave_msg, llave;
    seccion_crt *tel_ptr;
    seccion_crt *msg_ptr;
    int tel_semid, tel_memid, msg_semid, msg_memid, p;
    pid_t pid;

    llave_tel = ftok("/bin/ls", 31);
    llave_msg = ftok("/bin/ls", 30);
    llave = ftok("/bin/ls", 33);

    /****************************SECCION DE TELEFONO**************************************/
    tel_semid = crear_ligar_sem(llave_tel);
    tel_ptr = crear_ligar_mem(llave_tel, &tel_memid);
    /**************************FIN SECCION TELEFONO**************************************/

    /**************************SECCION DE MENSAJES**************************************/
    msg_semid = crear_ligar_sem(llave_msg);
    msg_ptr = crear_ligar_mem(llave_msg, &msg_memid);
    /**************************FIN DE MENSAJES*****************************************/

    printf("SECCION TEL: semid:%d\t memid:%d\n", tel_semid, tel_memid);
    printf("SECCION MSG: semid:%d\t memid:%d\n", msg_semid, msg_memid);
    crear_archivos();

    /********************INCIALIZACIÓN DE SEMAFORO PARA PRODUCTORES*******************/
    int id = semget(llave, 2, IPC_CREAT | IPC_EXCL | 0600);
    if (id == -1)
    {
        if ((id = semget(llave, 2, 0600)) < -1)
        {
            printf("no se puede crear semaforos para productores\n");
            exit(-1);
        }
    }
    else
    {
        semctl(id, SEM_PRODUCTORES, SETVAL, 4);
        semctl(id, SEM_CONSUMIDORES, SETVAL, 3);
    }
    /********************FINALIZACIÓN DE SEMAFORO PARA PRODUCTORES********************/

    for (p = 0; p < NUM_PROC; ++p)
    {
        if ((pid = fork()) == -1)
        {
            printf("error\n");
            exit(-1);
        }
        else if (pid == 0)
            break;
    }

    if (pid == 0)
    {
        int cont_tel = 0, cont_msg = 0, i, j = NUM_PROC;
        while (cont_tel < CONSUMO || cont_msg < CONSUMO)
        {
            if ((i = semctl(id, SEM_CONSUMIDORES, GETVAL)) < 1)
                avisar(SEM_CONSUMIDORES, id);

            esperar(SEM_CONSUMIDORES, id);
            if (cont_tel < CONSUMO)
                cont_tel += leer(tel_ptr, tel_semid, cont_tel + 1);

            if (cont_msg < CONSUMO)
                cont_msg += leer(msg_ptr, msg_semid, cont_msg + 1);
            avisar(SEM_PRODUCTORES, id);
        }
        exit(0);
    }
    else
    {
        int c_tel = 0, c_msg = 0, j = NUM_PROC, i;
        while (c_tel < CONSUMO + 1 || c_msg < CONSUMO + 1)
        {
            if ((i = semctl(id, SEM_CONSUMIDORES, GETVAL)) < 1)
                avisar(SEM_CONSUMIDORES, id);

            esperar(SEM_CONSUMIDORES, id);
            if (c_tel < CONSUMO + 1)
                c_tel += leer(tel_ptr, tel_semid, c_tel + 1);
            if (c_msg < CONSUMO + 1)
                c_msg += leer(msg_ptr, msg_semid, c_msg + 1);
            avisar(SEM_PRODUCTORES, id);
        }

        for (int k = 0; k < NUM_PROC; k++)
        {
            int estado;
            wait(&estado);
        }
        shmdt(tel_ptr);
        shmdt(msg_ptr);

        printf("finaliza consumidor\n");
        semctl(id, 0, IPC_RMID);
        semctl(tel_semid, 0, IPC_RMID);
        semctl(msg_semid, 0, IPC_RMID);
        shmctl(tel_memid, IPC_RMID, 0);
        shmctl(msg_memid, IPC_RMID, 0);
    }

    //se desliga de la memoria
    return 0;
}

int leer(seccion_crt *ptr, int semid, int nc)
{
    int sems = 1;
    for (int i = 0; i < NUM_SECC_CRT; i++)
    {
        esperar(sems, semid);
        if (ptr[i]->vacio == 0)
        {
            guardar_datos(ptr[i]->msg);
            ptr[i]->vacio = 1;
            printf("Consumidor[%d]:%s,seccion[%d],no_cons:%d\n", getpid(),
                   ptr[i]->msg, i, nc);
            avisar(sems - 1, semid);
            return 1;
        }
        avisar(sems - 1, semid);
        sems += 2;
    }
    return 0;
}
