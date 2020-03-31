#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h>  // Para los Sockets
#include <stdlib.h> 
#include <netinet/in.h>  // Para la AF_INET (Address Family)
#include <arpa/inet.h> 
#include <string.h> 
#include <pthread.h>
#define PORT 8080 

void * tarea_hilo(void *);

int main () 
{

    // Definiendo variables necesarias para hacer posible la conexión 
    int socket_fd, new_socket, peticion_data;
    struct sockaddr_in server_address, client_address;
    int addr_len = sizeof(server_address);
    int opt = 1 ;
    char buffer[1024] = {0};
    char ok[100];

    // Creando descriptor de socket
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { // socket(domain, type, protocol)
        printf("\nEl socket no se ha podido crear");
        exit(EXIT_FAILURE);
    }

    // Forzando al socket a que escuche en el puerto 8080
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    // Publicando el servicio
    memset((void *) &server_address, 0, sizeof(server_address)); // Reset a la estructura address
    server_address.sin_family = AF_INET; 
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    server_address.sin_port = htons( PORT ); 
    
    if (bind(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        printf("\nNo se pudo publicar la IP");
        exit(EXIT_FAILURE);
    }

    // Servidor escuchando peticiones
    printf("Estoy escuchando...");
    if (listen(socket_fd, 5) < 0) 
    { 
        printf("\nError al escuchar");
        exit(EXIT_FAILURE);
    }

    // Servidor aceptando cpnexión
    int addrlen = sizeof(client_address);
	for(;;)
	{
			int socket;
			pthread_t hilo;
			if ((socket = accept(socket_fd,
			(struct sockaddr *) &client_address,
			(socklen_t*) &addrlen)) < 0) 
			{ 
				perror("\nError al establecer la conexión"); 
				exit(EXIT_FAILURE); 
			}
			printf("Conexión aceptada...");
			pthread_create(&hilo,NULL,tarea_hilo,(void *)&socket);
    }
    return 0;
}

void * tarea_hilo(void *conexion)
{
	int new_socket = *(int *)conexion;
	char arroba;
	char ok[500];
	char buffer[1024];
	while(1)
	{
        read(new_socket, buffer, 1024);
        printf("\n# Cadena recibida del cliente: %s\n", buffer);
		memcpy(&arroba,buffer,sizeof(char));
		
        if(arroba  == '@') 
		{
            printf("\nMe desconecto\n\n");
            break;
            exit(0);   
        }
        printf("Cadena a enviar desde servidor: ");
        fgets(ok, sizeof(ok), stdin);
        send(new_socket, ok, strlen(ok), 0); 
        printf(">> Mensaje del servidor enviado\n");
		memcpy(&arroba,ok,sizeof(char));
		if(arroba == '@')
		{
            printf("\nMe desconecto\n\n");
            break;
            exit(0);   
		}
        memset(buffer, 0, strlen(buffer));
	}
	close(*(int *)conexion);
}
