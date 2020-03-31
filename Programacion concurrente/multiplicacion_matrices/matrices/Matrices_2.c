#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<time.h>
 
int main()
{
	int procesos,n,m,status,auxMatriz=0;
	int aux,aux2=0;
	int i,j,k,l,ii;
	srand(time(NULL));
	//RECIBE DATOS
	printf("Numero de Procesos\n");
	scanf("%d",&procesos);
	printf("Numero de Filas\n");
	scanf("%d",&n);
	printf("Numero de Columnas\n");
	scanf("%d",&m);
	//NUMERO DE FILAS/PROCESOS
	aux=n/procesos;
	//RESERVACION DE MEMORIA
	int **matriz1,**matriz2;
	matriz1= (int **)malloc (n*sizeof(int *));
	for (i=0;i<n;i++)
		matriz1[i] = (int *)malloc(m*sizeof(int));
	matriz2= (int **)malloc (n*sizeof(int *));
	for (i=0;i<n;i++)
		matriz2[i] = (int *)malloc(m*sizeof(int));
	//LLENADO DE MATRICES
	for(i=0; i<n; i++)
	{
		for (j=0; j<m; j++)
		{
			matriz1[i][j]=rand()%5;
			matriz2[i][j]=rand()%5;		
		}
	}

	printf("\nMATRIZ 1\n");
	for (i=0;i<n;i++)
	{
	    for (j=0;j<m;j++)
	    { 
	    	printf("[%d][%d]=\t%d\n",i,j,matriz1[i][j]);
	    }
    }

	printf("\nMATRIZ 2\n");
	for (i=0;i<n;i++){
	    for (j=0;j<m;j++)
	    { 
	    	printf("[%d][%d]=\t%d\n",i,j,matriz2[i][j]);
	    }
	}


	printf("MATRIZ RESULTANTE\n");
	if(procesos>=n){
		pid_t pid;
		for(i=0; i<procesos; i++)
		{
			pid=fork();
			if(pid){
				if(i==n-1){
					for(l=0; l<procesos; l++)
						wait(&status);
				}
			}
			else if(pid==0)
			{
				//printf("\nSoy el hijo %d, mi padre es %d\n ",getpid(),getppid());
		   		for(j=0; j<m; j++)
		   		{
		   			for(k=0; k<n; k++)
		   			{
		   				auxMatriz=auxMatriz+matriz1[i][k]*matriz2[k][j];
		   			}	
		   			printf("[%d][%d]=%d\n", i,j,auxMatriz);
		   			auxMatriz=0;
		   		}
		   		break;
			}
			else if(pid==-1)
			{
				exit(0);
			}
		}	
	}
	else if(procesos<n)
	{
		pid_t pid;
		for(i=0; i<procesos; i++)
		{
			pid=fork();
			if(pid){
				if(i==n-1){
					for(l=0; l<procesos; l++)
						wait(&status);
				}
				aux2=aux;
				aux++;
			}
			else if(pid==0)
			{
				//printf("\nSoy el hijo %d, mi padre es %d\n ",getpid(),getppid());
				if(i==procesos-1){
					for(j=aux2; j<n; j++)
					{
						for(k=0; k<m; k++)
						{
							for(ii=0; ii<n; ii++)
							{
								auxMatriz=auxMatriz+matriz1[j][ii]*matriz2[ii][k];
			   				}	
			   			printf("[%d][%d]=%d\n", j,k,auxMatriz);
			   			auxMatriz=0;
						}
					}
				}
				else
				{
					for(j=aux2; j<aux; j++)
					{
						for(k=0; k<m; k++)
						{
							for(ii=0; ii<n; ii++)
							{
								auxMatriz=auxMatriz+matriz1[j][ii]*matriz2[ii][k];
			   				}	
			   			printf("[%d][%d]=%d\n", j,k,auxMatriz);
			   			auxMatriz=0;
						}
					}
				}
				break;
			}
			else if(pid==-1)
			{
				exit(0);
			}
		}
	}

	return 0;
}