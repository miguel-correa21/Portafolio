import socket
import os
import sys
import time
from archivos_x_socket import utilidades

direccion_servidor = (utilidades.HOST_MAESTRO,utilidades.PORT_MAESTRO)


with socket.socket(socket.AF_INET,socket.SOCK_DGRAM) as socket:
    while True:
        utilidades.menu()
        accion = int(input("Ingrese la acción a realizar: "))
        utilidades.listar()    
        nombre_archivo = input("Ingrese el nombre del archivo: ")
        utilidades.avisar(accion,socket,direccion_servidor,nombre_archivo)

    

    
    
