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
#include <time.h>


#define PORT 8080
#define MAX 1024
#define GRUPO "239.0.0.1"

int main()
{
	int desc_socket;
	char buffer[MAX];
	char *mensaje = "Hola desde servidor";
	struct ip_mreq mreq;
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
	bzero((char* )&servidor_dir,sizeof(servidor_dir));
	servidor_dir.sin_family = AF_INET;
	servidor_dir.sin_addr.s_addr = htonl(INADDR_ANY);
	servidor_dir.sin_port = htons(PORT);
	
	//publicamos el servidor
	if( bind(desc_socket,
		(const struct sockaddr *)&servidor_dir,
		sizeof(servidor_dir)) < 0)
	{
		printf("Error al publicar socket\n");
		exit(EXIT_FAILURE);
	}
	//configuramos multicast
	mreq.imr_multiaddr.s_addr = inet_addr(GRUPO);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	//agregamos 
	if(setsockopt(desc_socket,IPPROTO_IP,IP_ADD_MEMBERSHIP,
				&mreq,sizeof(mreq)) < 0)
	{
		printf("Error al agregar miembros a multicast\n");
		exit(-1);
	}
	int tam,bytes_res;

	for(;;)
	{
			bytes_res = recvfrom(desc_socket,buffer,
					MAX,0,(struct sockaddr *)&servidor_dir,&tam);
			if(bytes_res < 0)
			{
				printf("Error al recibir datos\n");
				exit(-1);
			}
			else if (bytes_res == 0)
				break;

			buffer[bytes_res] = '\0';

			printf("%s : %s\n",inet_ntoa(servidor_dir.sin_addr),buffer);
			memset(buffer,0,sizeof(buffer));

			/*sendto(desc_socket,(const char *)mensaje,
	strlen(mensaje),0,(const struct sockaddr *)&servidor_dir,
					tam);
			printf("Se mando el mensaje\n");*/
	}
	close(desc_socket);	
	return 0;
}

