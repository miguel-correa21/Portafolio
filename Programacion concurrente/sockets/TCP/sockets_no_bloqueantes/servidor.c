/*
 * =====================================================================================
 *
 *       Filename:  primer_ejemplo.c
 *
 *    Description:  socket no bloqueqnte  modelo cliente
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
#define TAM_BUFFER 100 

#define CLIENTES_MAX 32

/* un arreglo de descripción de archivos que el servidor
 * mantiene en para poder comunicarse con los clientes*/
int descriptores_monitoreados[CLIENTES_MAX];

/*cada respuesta del cliente se guarda en este arreglo*/
int respuesta_cliente[CLIENTES_MAX];

//limpiamos todos los archivos de descripción
//si es que existen en la estructura
static void inicializar_monitor()
{
	for(int i = 0; i < CLIENTES_MAX; i++)
		descriptores_monitoreados[i] = -1;
}

//agregar un nuevo archivo de descripción al arreglo
static void agregar_a_monitor(int archivo_descripcion)
{
	for(int i = 0; i < CLIENTES_MAX; i++)
	{
		if(descriptores_monitoreados[i] == -1)
		{
			descriptores_monitoreados[i] = archivo_descripcion;
			break;
		}
	}
}
//eliminar un archivo de descripción del arreglo
static void eliminar_de_monitor(int archivo_descripcion)
{
	for(int i = 0; i < CLIENTES_MAX; i++)
	{
		if(descriptores_monitoreados[i] == archivo_descripcion)
		{
			descriptores_monitoreados[i] = -1;
			break;
		}
	}
}
//introducimos todos los archivos de descripción que se
//encuentran en el arreglo a la estructura de datos
static void actualizar_estructura(fd_set *archivo_des_ptr)
{
	FD_ZERO(archivo_des_ptr);
	for(int i = 0; i < CLIENTES_MAX; i++)
		if(descriptores_monitoreados[i] != -1)
			FD_SET(descriptores_monitoreados[i],
					archivo_des_ptr);
}
//obtener el valor maximo de todos los archivos de 
//descripción que el servidor esta monitoreando
static int obtener_max_archivo_des()
{
	int max = -1;
	for(int i = 0; i < CLIENTES_MAX; i++)
		if(descriptores_monitoreados[i] > max)
			max = descriptores_monitoreados[i];
	return max;
}

void chatear(int conexion);

int main(int argc, char *argv[])
{
	struct sockaddr_un nombre;
	int conexion_socket;
	int datos_socket;
	char respuesta;
	int resultado;
	char buffer[TAM_BUFFER];
	fd_set archivos_lectura;
	int socket_activo,i;
	inicializar_monitor();

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
	//agregamos el socket maestro al arreglo para
	//monitorearlo.
	agregar_a_monitor(conexion_socket);
	
	//bucle infitino para mantener al servidor
	for(;;)
	{	
		//agregamos todos los archivos de descriptor
		//al arreglo para monitorearlos
		actualizar_estructura(&archivos_lectura);
		printf("Esperando a select()\n");
		
		//cuando se realiza la llamada a select()
		//el servidor queda bloqueado
		//y este se desbloquea cuando un cliente le manda
		//una petición
		select(obtener_max_archivo_des()+1,&archivos_lectura,
				NULL,NULL,NULL);
		
		//checamos si esta activo el descriptor de archivo
		//del socket esta activo.
		//si FD_ISSET retorna TRUE signigica que un nuevo
		//cliente ha mandado una solicitud de conexión
		if(FD_ISSET(conexion_socket,&archivos_lectura))
		{
			printf("Se ha recibido una nueva conexión\n");

			datos_socket = accept(conexion_socket,NULL,NULL);
			if(datos_socket == -1)
			{
				printf("No se pued aceptar conexión");
				exit(EXIT_FAILURE);
			}
			printf("Conexión aceptada desde el cliente\n");
			//agregamos esta conexión al arreglo para que sea
			//vigilada.
			agregar_a_monitor(datos_socket);
		}
		else // Llegan datos de algun otro cliente
		{
			socket_activo = -1;
			//buscamos que archivo de descripción es el
			//que esta activo
			for(i = 0; i < CLIENTES_MAX; i++)
			{
				if(FD_ISSET(descriptores_monitoreados[i],
							&archivos_lectura))
				{
					socket_activo = 
						descriptores_monitoreados[i];
					chatear(socket_activo);
					//mandamos mensaje de terminado
					memset(buffer,0,TAM_BUFFER);
					sprintf(buffer,"Adios\n");
					printf("Terminando de atender a cliente\n");
					if((write(datos_socket,
									buffer,strlen(buffer)))< 0)
					{
						printf("no se puede responder al cliente\n");
						exit(EXIT_FAILURE);
					}
						//cerramos el la conexión 
						//con el cliente
						close(socket_activo);
						respuesta_cliente[i] = 0;
						eliminar_de_monitor(socket_activo);
						continue;
				}
			}
		}

	}

	//cerramos el socket maestro
	close(conexion_socket);
	eliminar_de_monitor(conexion_socket);
	printf("Conexión cerrada...\n");
	//eliminados el socket
	unlink(NOMBRE_SOCKET);
	exit(EXIT_SUCCESS); 
}

void chatear(int conexion)
{
	char buffer[TAM_BUFFER];
	char adios_mand, adios_rec;
	char respuesta[TAM_BUFFER];
	for(;;)
	{
		//preparamos el buffer para recibir
		//los datos
		memset(buffer,0,TAM_BUFFER);
		memset(respuesta,0,TAM_BUFFER);
		printf("Esperamos respuesta del cliente\n");
		if((read(conexion,buffer,
						TAM_BUFFER))< 0)
		{
			printf("los datos del cliente no se pueden leer\n");
			exit(EXIT_FAILURE);
		}
		printf("Cliente: %s\n",buffer);
		memcpy(&adios_rec,buffer,sizeof(char));
		if(adios_rec == '@' || adios_mand == '@' ) break;

		printf("Mensaje: ");
		fgets(respuesta,TAM_BUFFER,stdin);
		write(conexion,respuesta,strlen(respuesta));
		memcpy(&adios_mand,respuesta,sizeof(char));
		if(adios_rec == '@' || adios_mand == '@' ) break;
	}
}

