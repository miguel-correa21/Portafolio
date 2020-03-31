import socket
import os
import sys
import time
from archivos_x_socket import utilidades

direccion1 = (utilidades.HOST_SERVIDOR2,utilidades.PORT_SERVIDOR2)
direccion2 = (utilidades.HOST_SERVIDOR3,utilidades.PORT_SERVIDOR3)


with socket.socket(socket.AF_INET,socket.SOCK_DGRAM) as socket:
    socket.sendto(bytes("soycliente",'utf-8'),direccion1)
    time.sleep(0.02)
    socket.sendto(bytes("soycliente",'utf-8'),direccion2)
    time.sleep(0.02)
    while True:
        utilidades.menu()
        accion = int(input("Ingrese la acción a realizar: "))
        utilidades.listar()    
        nombre_archivo = input("Ingrese el nombre del archivo: ")
        utilidades.avisar(accion,socket,direccion1,nombre_archivo)
        time.sleep(0.02)
        utilidades.avisar(accion,socket,direccion2,nombre_archivo)
        time.sleep(0.02)

    

    
    
