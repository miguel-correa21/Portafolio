import socket
import os
from archivos_x_socket import archivo

HOST = '127.0.0.1'
PORT = 8001
BUFFER = 1024

def menu():
    os.system("clear")
    print("""
            1) Crear un Nuevo archivo
            2) Eliminar  archivo
            3) Actualizar archivo
            4) Mostrar Contenido de un archivo
            """)

def listar_archivos():
    print("\t Archivo en este directorio")
    directorio = os.listdir("./")
    for archivo in directorio:
        print(f"\t>>{archivo}")
    

def avisar(accion,conexion,nombre_archivo):
    listar_archivos()
    '''
    acciones:
        1:agregar archivo
        2:eliminar archivo
        3:actualizar archivo
        4:mostrar contenido de un archivo 
    '''
    if accion == 1:
        conexion.send(bytes('nuevo','utf-8'))
        respuesta = conexion.recv(BUFFER).decode('utf-8')
        if str(respuesta) == 'ok':
            if  archivo.nuevo_archivo(nombre_archivo):
                print(f"Archivo:{nombre_archivo} creado exitosamente")
                print("enviando archivo...")
                archivo.mandar_archivo(conexion,nombre_archivo)

    elif accion == 2:
        conexion.send(bytes('eliminar','utf-8'))
        respuesta = conexion.recv(BUFFER).decode('utf-8')
        if str(respuesta) =='ok':
            conexion.send(bytes(nombre_archivo,'utf-8'))
            if archivo.eliminar_archivo(nombre_archivo):
                print(f"Archivo:{nombre_archivo} ha sido eliminado")
            else:
                print(f"no se puede eliminar el archivo:{nombre_archivo}")

    elif accion == 3:
        conexion.send(bytes('actualizar','utf-8'))
        respuesta = conexion.recv(BUFFER).decode('utf-8')
        if str(respuesta) == 'ok':
            if archivo.actualizar_archivo(nombre_archivo):
                print(f"Archivo:{nombre_archivo} ha sido eliminado")
                archivo.mandar_archivo(conexion,nombre_archivo,"actualizar")
            else:
                print(f"no se puede actualizar el archivo:{nombre_archivo}")

    elif accion == 4:
        ruta = './' + nombre_archivo
        if not ".txt" in nombre_archivo:
            ruta += '.txt'
        if os.path.isfile(ruta):
           os.system(f"cat {nombre_archivo}") 
           input("Oprima Enter para continuar...")
        else:
            print(f"el archivo{nombre_archivo} no existe")
            input("Oprima Enter para continuar...")


with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as servidor:
    servidor.connect((HOST,PORT))
    while True:
        menu()
        accion = int(input("Ingresa la acción que se quiere Realizar:"))
        listar_archivos()
        nombre_archivo = input("Ingrese el nombre del archivo a crar/eliminar/actualizar: ")
        avisar(accion,servidor,nombre_archivo)
    

