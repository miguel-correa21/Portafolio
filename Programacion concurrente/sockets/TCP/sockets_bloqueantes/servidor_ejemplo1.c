/*
 * =====================================================================================
 *
 *       Filename:  primer_ejemplo.c
 *
 *    Description: primer socket  modelo cliente
 *    -servidor 
 *
 *        Version:  1.0
 *        Created:  09/26/2019 03:21:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NOMBRE_SOCKET "/tmp/SocketArchivo"
#define TAM_BUFER 100 
#define ARCHIVO "servidor_texto.txt"

void procesar_datos(int conexion);
short existe(char *fname);


int main(int argc, char *argv[])
{
	struct sockaddr_un nombre;
	int conexion_socket;
	int datos_socket;
	char respuesta;
	int resultado;
	char bufer[TAM_BUFER];

	//en caso de que ya exista el socket este se 
	//borra
	unlink(NOMBRE_SOCKET);
	//creamos el socket maestro
	conexion_socket = socket(AF_UNIX,SOCK_STREAM,0);
	
	if(conexion_socket == -1)
	{
		printf("Error al crear socket\n");
		exit(EXIT_FAILURE);
	}

	printf("Se ha creado el socket maestro\n");

	//limpliamos 
	memset(&nombre,0,sizeof(struct sockaddr_un));

	//configuración de socket
	nombre.sun_family = AF_UNIX;
	strncpy(nombre.sun_path, NOMBRE_SOCKET, 
			sizeof(nombre.sun_path) - 1);
	//publicamos el socket
	if((bind(conexion_socket,
					(const struct sockaddr *)&nombre,
					sizeof(struct sockaddr_un))) < 0)
	{
		printf ("Error al publicar el socket\n");
		exit(EXIT_FAILURE);
	}

	printf("bind() se ejecuto con exito\n");
	//conexión con backlog de tamaño 20	
	if((listen(conexion_socket,20)) < 0)
	{
		printf("fallo en función listen()\n");
		exit(EXIT_FAILURE);
	}
	
	//bucle infitino para mantener al servidor
	for(;;)
	{	
		printf("Esperando a accept()\n");
		datos_socket = accept(conexion_socket,
				NULL,NULL);
		
		if(datos_socket == -1)
		{
			printf("Error en funcion accept()\n");
			exit(EXIT_FAILURE);
		}
		
		resultado = 0;
		for(;;)
		{
			//preparamos el bufer para recibir
			//los datos
			memset(bufer,0,TAM_BUFER);
			printf("Esperamos respuesta del cliente\n");
			if((read(datos_socket,bufer,
							TAM_BUFER))< 0)
			{
				printf("los datos del cliente no se pueden leer\n");
				exit(EXIT_FAILURE);
			}

			memcpy(&respuesta,bufer,sizeof(char));
			if(respuesta == 'n') break;
			procesar_datos(datos_socket);
		}
		//mandamos mensaje de terminado
		memset(bufer,0,TAM_BUFER);
		sprintf(bufer,"Archivo recibido\n");
		printf("Terminando de atender a cliente\n");

		if((write(datos_socket,bufer,TAM_BUFER))< 0)
		{
			printf("no se puede responder al cliente\n");
			exit(EXIT_FAILURE);
		}
		//cerramos el la conexión con el cliente
		close(datos_socket);
	}

	//cerramos el socket maestro
	close(conexion_socket);
	printf("Conexión cerrada...\n");
	//eliminados el socket
	unlink(NOMBRE_SOCKET);
	exit(EXIT_SUCCESS); 
}

void procesar_datos(int conexion)
{
	FILE *archivo;
	char buffer_archivo[TAM_BUFER];
	char buffer_aux[TAM_BUFER];
	int bytes_recibidos;
	char *texto_servidor = "\ntexto_servidor\n";
	int final;
	if(!existe(ARCHIVO))
		archivo = fopen(ARCHIVO, "w");
	else
		archivo = fopen(ARCHIVO, "a");

	for(;;)
	{
		//limpiamos la memoria
		memset(buffer_archivo,0,TAM_BUFER);
		memset(buffer_aux,0,TAM_BUFER);
		printf("esperando texto para archivo\n");	
		fflush(stdin);
		bytes_recibidos = read(conexion,buffer_archivo,
				TAM_BUFER);
		printf("Se recibio %s con  %d bytes\n",
				buffer_archivo,bytes_recibidos);
		if(bytes_recibidos < 0)
		{
			printf("error al recibir de cliente\n");
			exit(EXIT_FAILURE);
		}
		memcpy(buffer_aux,buffer_archivo,bytes_recibidos);
		memcpy(&final,buffer_archivo,sizeof(int));
		if(final == 0) break;
		else
		{
			fprintf(archivo,buffer_aux);
			fprintf(archivo,texto_servidor);
		}
		write(conexion,"siguiente",strlen("siguiente"));
	}
	fclose(archivo);
	printf("Se termino de elaborar archivo\n");
}

short existe(char *fname)
{
  int fd=open(fname, O_RDONLY);
  if (fd<0)         /* error */
    return 0;
  /* Si no hemos salido ya, cerramos */
  close(fd);
  return 1;
}
