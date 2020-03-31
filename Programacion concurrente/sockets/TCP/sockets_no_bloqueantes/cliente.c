/*
 * =====================================================================================
 *
 *       Filename:  cliente_ejemplo1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/26/2019 04:11:27 PM
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


int main(int argc, char *argv[])
{
	struct sockaddr_un dir;
	int datos_socket;
	char buffer[TAM_BUFER];
	char respuesta[TAM_BUFER];
	char adios_rec;
	char adios_mand;
	
	datos_socket = socket(AF_UNIX,SOCK_STREAM,0);
	if(datos_socket == -1)
	{
		printf("Error al crear socket()\n");
		exit(EXIT_FAILURE);
	}

	//limpiamos toda la estructura para portabilidad
	memset(&dir,0,sizeof(struct sockaddr_un));

	//conectamos el socket
	dir.sun_family = AF_UNIX;
	strncpy(dir.sun_path,NOMBRE_SOCKET,
			sizeof(dir.sun_path) - 1);

	if((connect(datos_socket,
				(const struct sockaddr *)&dir,
				sizeof(struct sockaddr_un)) < 0))
	{
		printf("No se encuentra el servidor\n");
		exit(EXIT_FAILURE);
	}
	//mandamos datos
	//chat...
	printf("Conexión establecida con exito.\n");
	for(;;)
	{
		//limpiamos las variables
		memset(buffer,0,TAM_BUFER);
		memset(respuesta,0,TAM_BUFER);

		printf("Mensaje: ");
		fgets(respuesta,TAM_BUFER,stdin);
		if(write(datos_socket,respuesta,
				strlen(respuesta)) < 0)
		{
			printf("Error al enviar datos\n");
			exit(EXIT_FAILURE);
		}
		read(datos_socket,buffer,TAM_BUFER);
		printf("Servidor: %s\n",buffer);
		memcpy(&adios_mand,respuesta,sizeof(char));
		memcpy(&adios_rec,buffer,sizeof(char));
		if(adios_mand == '@' || adios_rec == '@') break;
	}
	//recibimos los datos de respuesta final
	memset(buffer,0,TAM_BUFER);
	printf("se cerro el chat\n");
	if((read(datos_socket,buffer,TAM_BUFER))< 0)
	{
		printf("Error al intentar leer\n");
		exit(EXIT_FAILURE);
	}
	printf("%s\n",buffer);
	close(datos_socket);
	exit(EXIT_SUCCESS);
}

