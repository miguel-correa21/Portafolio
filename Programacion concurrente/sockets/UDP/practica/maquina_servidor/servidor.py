import socket
import os
import threading
from archivos_x_socket import utilidades

 #localhost
HOST = '192.168.43.89'
PORT = 8001 #puerto desde el que se escucha

buffer_cliente = 100
buffer_accion = 1024 
accion = ' '
acciones = ['nuevo','eliminar']


def tarea_servidor(*args):
    global accion
    socket = args[0]
    direccion = args[1]
    print("Se conecto con ", dir)
    while True:
        try:
            if accion == ' ':
                accion = str(socket.recvfrom(buffer_accion).decode('utf-8'))
        except:
            continue
        nombre_archivo = utilidades.realizar_accion(accion,socket,direccion) 
        if nombre_archivo != ' ':
            utilidades.distribuir_accion(accion,nombre_archivo)
        else:
            print("No se puede atender a los clientes")
        print("Se termino de procesar la petición\nEn espera de otra...")

##creamos el socket con la configuración especificada
#utilizamos with para no tener que utilizar close

with socket.socket(socket.AF_INET,socket.SOCK_DGRAM) as socket:
    utilidades.actualizar_lista_archivos()
    hilo = threading.Thread(target=utilidades.monitorear_servidor_maestro)
    socket.bind((HOST,PORT))
    hilo.start()
    while True:
        respuesta,dir = socket.recvfrom(buffer_cliente)
        print(respuesta)
        if respuesta:
            try:
                cliente = str(respuesta.decode("utf-8"))
            except:
                continue
            if cliente == "soycliente":
                threading.Thread(target=tarea_servidor,args=(socket,dir)).start()
            elif cliente in acciones:
                accion = cliente
    hilo.join()


