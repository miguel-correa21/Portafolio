import socket
import os
import threading
from archivos_x_socket import utilidades

 #localhost
HOST = '192.168.43.89'
PORT = 8001 #puerto desde el que se escucha

buffer_cliente = 100
buffer_accion = 1024 


def tarea_servidor(*args):
    socket = args[0]
    direccion = args[1]
    print("Se conecto con ", dir)
    while True:
        accion = socket.recvfrom(buffer_accion)
        nombre_archivo = utilidades.realizar_accion(accion,socket,direccion) 
        if nombre_archivo != ' ':
            print("Se atendio al cliente de forma correcta")
        else:
            print("No se puede atender a los clientes")
        print("Se termino de procesar la petición\nEn espera de otra...")

##creamos el socket con la configuración especificada
#utilizamos with para no tener que utilizar close

with socket.socket(socket.AF_INET,socket.SOCK_DGRAM) as socket:
    utilidades.actualizar_lista_archivos()
    hilo = threading.Thread(target=utilidades.monitorear_servidor_cliente)
    socket.bind((HOST,PORT))
    while True:
        hilo.start()
        respuesta,dir = socket.recvfrom(buffer_cliente)
        if respuesta:
            cliente = respuesta.strip()
            if cliente == "soycliente":
                threading.Thread(target=tarea_servidor,args=(socket,dir)).start()



