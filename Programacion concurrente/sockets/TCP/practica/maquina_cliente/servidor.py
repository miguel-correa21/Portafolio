import socket
import os
from archivos_x_socket import archivo
import threading

HOST = '192.168.43.88' #localhost
PORT = 8003 #puerto desde el que se escucha
            #puertos no privilegiados > 1023
BUFFER = 1024

def listar_archivos():
    print("\t Archivo en este directorio")
    directorio = os.listdir("./")
    for archivo in directorio:
        print(f"\t>>{archivo}")

def realizar_accion(accion,conexion):
    os.system("clear")
    listar_archivos()
    if accion == 'nuevo':
        conexion.send(bytes('ok','utf-8'))
        print("Recibiendo nuevo archivo...")
        nombre_arch = archivo.recibir_archivo(conexion,BUFFER)
        if(nombre_arch != ' '):
            print("se recibio el archivo exitosamente")
            print("contenido del archivo: ")
            os.system(f"cat {nombre_arch}")
            input("Presione Enter para continuar..")
        else:
            print("No se recibio el archivo")
        
    elif accion == 'eliminar':
        print("Eliminando archivo...")
        conexion.send(bytes('ok','utf-8'))
        nombre_archivo = str(conexion.recv(BUFFER).decode('utf-8'))
        if archivo.eliminar_archivo(nombre_archivo):
            listar_archivos()
            print(f"Archivo:{nombre_archivo} se elimino correctamente")
        else:
            print("No se pudo eliminar el archivo")

    elif accion == 'actualizar':
        print("Actualizando archivo")
        conexion.send(bytes('ok','utf-8'))
        nombre_arch = archivo.recibir_archivo(conexion,BUFFER,"actualizar")
        if(nombre_arch != ' '):
            print("se actualizo el archivo exitosamente")
            print("nuevo contenido del archivo: ")
            os.system(f"cat {nombre_arch}")
            input("Presione Enter para continuar..")
        else:
            print("No se pudo actualizar el archivo")



def tarea_hilo(*args):
    conexion = args[0]
    semaforo = threading.Semaphore()
    dir = args[1]
    print("Se conecto con ", dir)
    while True:
        print("En espera de otra petición...")
        semaforo.acquire()
        accion = str(conexion.recv(BUFFER).decode('utf-8')) 
        realizar_accion(accion,conexion) 
        print("Se termino de procesar la petición del servidor maestro")
        conexion.send(bytes('listo','utf-8'))
        semaforo.release()



##creamos el socket con la configuración especificada
#utilizamos with para no tener que utilizar close
with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as ser:
    ser.bind((HOST,PORT))
    ser.listen()
    while True:
        conexion,dir = ser.accept()
        threading.Thread(target=tarea_hilo,args=(conexion,dir)).start()
