import time
import os
import sys
import select

buffer_cadena = 1024
buffer_datos = 4096
tiempo = 3


def mandar_archivo(socket,direccion,nombre_archivo):
    #mandamos el nombre del archivo
    socket.sendto(bytes(nombre_archivo,'utf-8'), direccion)
    tam = os.stat(nombre_archivo).st_size
    restante = 0
    #mandamos el archivo
    with open(nombre_archivo,'rb') as  archivo:
        datos = archivo.read(buffer_datos)
        while(datos):
            if(socket.sendto(datos,direccion)):
                restante += buffer_datos
                porcentaje = (restante * 100)/ tam
                print("Enviando archivo .....{0:.2f}".format(porcentaje))
                datos = archivo.read(buffer_datos)
                time.sleep(0.02)


def recibir_archivo(socket,direccion):
    #recibimos el nombre y nos conectamos con cliente
    datos,dir = socket.recvfrom(buffer_cadena)
    print(f"Se conecto con : {dir}")
    if datos:
        nombre_archivo = datos.strip()
    else:
        return False

    
    with open(nombre_archivo,'wb') as archivo:
        while True:
            listo = select.select([socket],[],[],tiempo)
            if listo[0]:
                datos,dir = socket.recvfrom(buffer_datos)
                archivo.write(datos)
            else:
                break
        
    return True

def eliminar_archivo(nombre_archivo):
    #if not '.txt' in nombre_archivo:
    #    nombre_archivo = nombre_archivo + '.txt'
    if not os.path.isfile(nombre_archivo):
        return False
    os.remove(nombre_archivo)
    return True
