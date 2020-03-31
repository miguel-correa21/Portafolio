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
#include <pthread>

#define NOMBRE_SOCKET "/tmp/SocketArchivo"
#define TAM_BUFER 100

void enviar_archivo(int conexion);

int main(int argc, char *argv[])
{
	struct sockaddr_un dir;
	int datos_socket;
	char buffer[TAM_BUFER];
	char respuesta;
	
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
	for(;;)
	{
		memset(&respuesta,0,1);
		printf("Quieres mandar el archivo a servidor? [n/no][s/si]\n");
		fflush(NULL);
		scanf("%c",&respuesta);
		printf("Se ingreso :%c \n",respuesta);
		if(write(datos_socket,&respuesta,
					sizeof(int)) < 0)
		{
			printf("Error al enviar datos\n");
			exit(EXIT_FAILURE);
		}
		if(respuesta == 'n') break;
		enviar_archivo(datos_socket);
	}
	//recibimos los datos de respuesta final
	memset(buffer,0,TAM_BUFER);
	printf("se termino de pasar los datos\n");
	if((read(datos_socket,buffer,TAM_BUFER))< 0)
	{
		printf("Error al intentar leer\n");
		exit(EXIT_FAILURE);
	}
	printf("%s\n",buffer);
	close(datos_socket);
	exit(EXIT_SUCCESS);
}

void enviar_archivo(int conexion)
{
	FILE *archivo;
	char respuesta[20];
	int bytes_mandados;
	char buffer[TAM_BUFER];
	archivo = fopen("./texto_cliente.txt","r");
	int final = 0;
	for(;;)
	{
		memset(buffer,0,TAM_BUFER);
		memset(respuesta,0,20);
		fgets(buffer,TAM_BUFER,archivo);
		//mandamos datos al servidor
		if(feof(archivo))
		{
			bytes_mandados = write(conexion
					,&final,sizeof(int));
			break;
		}
		else
			bytes_mandados = write(conexion,
					buffer,strlen(buffer));
		printf("Se envia:%s con  %d bytes\n",
				buffer,bytes_mandados);
		read(conexion,respuesta,20);
	}
	fflush(NULL);
	fclose(archivo);
}
