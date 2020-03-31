/*
 * =====================================================================================
 *
 *       Filename:  servidor.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/28/2019 12:14:37 AM
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
	char *mensaje = "Hola desde servidor";
	struct sockaddr_in servidor_dir, cliente_dir;
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
	memset(&cliente_dir,0,sizeof(cliente_dir));
	
	//configuración del servidor
	servidor_dir.sin_family = AF_INET;
	servidor_dir.sin_addr.s_addr = inet_addr("127.0.0.1");
	servidor_dir.sin_port = htons(PORT);
	
	//publicamos el servidor
	if( bind(desc_socket,
		(const struct sockaddr *)&servidor_dir,
		sizeof(servidor_dir)) < 0)
	{
		printf("Error al publicar socket\n");
		exit(EXIT_FAILURE);
	}
	
	int tam,bytes_res;

	for(;;)
	{
			bytes_res = recvfrom(desc_socket,(char *)buffer,
					MAX,0,(struct sockaddr *)&cliente_dir,&tam);
			buffer[bytes_res] = '\0';

			printf("Cliente: %s\n",buffer);
			memset(buffer,0,sizeof(buffer));

			sendto(desc_socket,(const char *)mensaje,
					strlen(mensaje),0,(const struct sockaddr *)&cliente_dir,
					tam);
			sleep(1);
			printf("Se mando el mensaje\n");
	}
	close(desc_socket);	
	return 0;
}

