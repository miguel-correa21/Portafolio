/*
 * =====================================================================================
 *
 *       Filename:  cliente.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/28/2019 12:38:38 AM
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
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX 1024

int main()
{
	int desc_socket;
	int buffer[MAX];
	char *mensaje = "Hola desde cliente";
	struct sockaddr_in servidor_dir;
	//creamos el descriptor del socket
	//socket
	desc_socket = socket(AF_INET,SOCK_DGRAM,0); 
	if(desc_socket < 0)
	{
		printf("Error al crear sokcet\n");
		exit(EXIT_FAILURE);
	}
	//limpiamos las direcciones
	memset(&servidor_dir,0,sizeof(servidor_dir));
	
	//configuración del servidor
	servidor_dir.sin_family = AF_INET;
	servidor_dir.sin_addr.s_addr = inet_addr("127.0.0.1");
	servidor_dir.sin_port = htons(PORT);
	
	int tam,bytes_res;

	sendto(desc_socket,(const char *)mensaje,
			strlen(mensaje),0,
			(const struct sockaddr *)&servidor_dir,
			sizeof(servidor_dir));

	printf("Mensaje enviado\n");

	bytes_res = recvfrom(desc_socket,(char *)buffer,
			MAX,0,(struct sockaddr *)&servidor_dir,&tam);
	buffer[bytes_res] = '\0';

	printf("Servidor: %s\n",buffer);
	
	close(desc_socket);	
	return 0;
}

