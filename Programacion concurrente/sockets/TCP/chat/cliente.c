#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h>
#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0}; 

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\nError al crear el socket\n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nDirección inválida o no es soportada\n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nError al establecer la conexión\n"); 
        return -1; 
    }
    
    char arroba;
	char cad[100];
    while(1)
	{
        printf("\nCadena a enviar: ");
        fgets(cad, sizeof(cad), stdin);
		memcpy(&arroba,cad,sizeof(char));
		if(arroba == '@')
			break;
        send(sock, cad, strlen(cad), 0); 
        printf("# Cadena enviada\n"); 
        valread = read(sock, buffer, 1024); 
        printf(">> Respuesta recibida del servidor: %s\n", buffer);
		
		memcpy(&arroba,buffer,sizeof(char));
		if(arroba == '@')
			break;
        memset(buffer, 0, strlen(buffer));
    }

    printf("\n\nConexión al servidor terminada\n\n");
    return 0; 
}
