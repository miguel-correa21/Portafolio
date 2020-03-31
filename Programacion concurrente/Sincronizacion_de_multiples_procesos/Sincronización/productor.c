#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "memoria.h"
#include "semaforos.h"

#define NUM_SECC_CRT 5
#define SEM_PRODUCTORES 0
#define SEM_CONSUMIDOR 1
#define NUM_PROC 4
#define PRODUCCION 10000

int escribir(seccion_crt *ptr, char mensaje[], int semid, int np);

int main(int argc, char **argv)
{
    key_t llave_tel, llave_msg, llave;
    seccion_crt *tel_ptr;
    seccion_crt *msg_ptr;
    int tel_semid, tel_memid, msg_semid, msg_memid, p;
    pid_t pid;
    char *telefonos[NUM_PROC] = {"55585558", "77777777", "88888888", "99999999"};
    char *mensajes[NUM_PROC] = {"usuario1", "usuario2", "usuario3", "usuario4"};

    llave_tel = ftok("/bin/ls", 31);
    llave_msg = ftok("/bin/ls", 30);
    llave = ftok("/bin/ls", 33);

    /****************************SECCION DE TELEFONO**************************************/
    tel_semid = crear_ligar_sem(llave_tel);
    tel_ptr = crear_ligar_mem(llave_tel, &tel_memid);
    Inicializar_mem(tel_ptr);
    /**************************FIN SECCION TELEFONO**************************************/

    /**************************SECCION DE MENSAJES**************************************/
    msg_semid = crear_ligar_sem(llave_msg);
    msg_ptr = crear_ligar_mem(llave_msg, &msg_memid);
    Inicializar_mem(msg_ptr);
    /**************************FIN DE MENSAJES*****************************************/

    printf("SECCION TEL: semid:%d\t memid:%d\n", tel_semid, tel_memid);
    printf("SECCION MSG: semid:%d\t memid:%d\n", msg_semid, msg_memid);

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
        semctl(id, SEM_CONSUMIDOR, SETVAL, 3);
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
        while (cont_tel < PRODUCCION || cont_msg < PRODUCCION)
        {
            if ((i = semctl(id, SEM_PRODUCTORES, GETVAL)) <= 1)
                avisar(SEM_PRODUCTORES, id);

            esperar(SEM_PRODUCTORES, id);
            if (cont_tel < PRODUCCION)
                if (escribir(tel_ptr, telefonos[p], tel_semid, cont_tel + 1))
                    cont_tel++;

            if (cont_msg < PRODUCCION)
                if (escribir(msg_ptr, mensajes[p], msg_semid, cont_msg + 1))
                    cont_msg++;
            avisar(SEM_CONSUMIDOR, id);
        }
        j--;
        if (j == 1)
        {
            semctl(id, SEM_PRODUCTORES, SETVAL, 1);
            semctl(id, SEM_CONSUMIDOR, SETVAL, 0);
        }
        exit(0);
    }
    else
    {
        for (int k = 0; k < NUM_PROC; k++)
        {
            int estado;
            wait(&estado);
        }

        printf("finaliza la producción\n");
        semctl(id, 0, IPC_RMID, 0);
        shmdt(tel_ptr);
        shmdt(msg_ptr);
        semctl(tel_semid, 0, IPC_RMID, 0);
        semctl(msg_semid, 0, IPC_RMID, 0);
    }

    return 0;
}

int escribir(seccion_crt *ptr, char mensaje[], int semid, int np)
{
    int sems = 0;
    for (int i = 0; i < NUM_SECC_CRT; i++)
    {
        esperar(sems, semid);
        if (ptr[i]->vacio == 1)
        {
            strcpy(ptr[i]->msg, mensaje);
            printf("Productor[%d]:%s,seccion[%d],no.prod:%d\n", getpid(),
                   ptr[i]->msg, i, np);
            ptr[i]->vacio = 0;
            avisar(sems + 1, semid);
            return 1;
        }
        avisar(sems + 1, semid);
        sems += 2;
    }
    return 0;
}
