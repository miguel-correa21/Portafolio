#include "semaforos.h"

void esperar(int numsem,int semid)
{  
    struct sembuf operacion;
    /*cerramos el semáforo del proceso padre*/
    operacion.sem_num = numsem;
    /*restamos una unidad al semáforo*/
    operacion.sem_op = -1;
    operacion.sem_flg = SEM_UNDO;
    /*aplicamos las operaciones, el 1 indica el numero de structuras que
    * tiene el arreglo*/
    semop(semid,&operacion,1);
}

void avisar(int numsem,int semid)
{
    struct sembuf operacion;
    /*cerramos el semáforo del proceso padre*/
    operacion.sem_num = numsem;
/*restamos una unidad al semáforo*/
    operacion.sem_op = 1;
    operacion.sem_flg = SEM_UNDO;
    /*aplicamos las operaciones, el 1 indica el numero de structuras que
 * tiene el arreglo*/
    semop(semid,&operacion,1);
}

int crear_ligar_sem(key_t llave)
{
    int semid;
    if((semid = semget(llave,NUM_SEM,IPC_CREAT| IPC_EXCL | 0600)) == -1)
    {
        
        if((semid = semget(llave,NUM_SEM, 0600)) == -1)
        {
            printf("error al enlazar\n");
            exit(-1);
        }
        else
            printf("productor ligo semaforos\n");
    }
    else
    {
        printf("productor creo semaforos\n");
        /*inicializamos los semáforos*/
        /*cerramos los semaforos que van a leer*/
        semctl(semid,SEM_READ1,SETVAL,0);
        semctl(semid,SEM_READ2,SETVAL,0);
        semctl(semid,SEM_READ3,SETVAL,0);
        semctl(semid,SEM_READ4,SETVAL,0);
        semctl(semid,SEM_READ5,SETVAL,0);
        /*Abrimos el semáforo para escribir*/
        semctl(semid,SEM_WRITE1,SETVAL,1);
        semctl(semid,SEM_WRITE2,SETVAL,1);
        semctl(semid,SEM_WRITE3,SETVAL,1);
        semctl(semid,SEM_WRITE4,SETVAL,1);
        semctl(semid,SEM_WRITE5,SETVAL,1);
    }
    return semid;
}

