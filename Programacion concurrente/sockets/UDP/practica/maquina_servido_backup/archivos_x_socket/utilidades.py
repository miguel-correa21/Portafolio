from archivos_x_socket import archivo 
import os
import socket
import threading
import time

HOST_MAESTRO   = '192.168.43.89'
HOST_SERVIDOR2 = '192.168.43.235'
HOST_SERVIDOR3 = '192.168.43.247'

PORT_MAESTRO   = 8001
PORT_SERVIDOR2 = 8002
PORT_SERVIDOR3 = 8003

buffer_cliente = 100
buffer_accion = 1024 

buffer_nombre_archivo = 200
lista_archivos = []
tam_archivos = []

def actualizar_lista_archivos():
    global lista_archivos
    archivos = os.listdir("./")
    for archivo in archivos:
        if os.path.isfile(archivo):
            lista_archivos.append(archivo)
            tam = os.stat(archivo).st_size
            tam_archivos.append(tam)

def menu():
    separador()
    print("""
            1) Crear un Nuevo archivo
            2) Eliminar  archivo
            3) Mostrar Contenido de un archivo
            """)

def listar():
    separador()
    print("\t Archivo en este directorio")
    directorio = os.listdir("./")
    for archivo in directorio:
        if os.path.isfile(archivo):
            print(f"\t>>{archivo}")

def separador():
    print("=====================================")
    

def avisar(accion,socket,direccion,nombre_archivo):
    separador()
    '''
    acciones:
        1:agregar archivo
        2:eliminar archivo
        3:mostrar contenido de un archivo 
    '''
    if accion == 1:
        print("Mandando archivo...")
        socket.sendto(bytes("nuevo",'utf-8'),direccion)
        time.sleep(0.02)
        archivo.mandar_archivo(socket,direccion,nombre_archivo)

    elif accion == 2:
        print("Eliminando archivo...")
        socket.sendto(bytes('eliminar','utf-8'),direccion)
        time.sleep(0.02)
        if archivo.eliminar_archivo(nombre_archivo):
            print(f"Archivo:{nombre_archivo} ha sido eliminado")
            listar()
        else:
            print(f"no se puede eliminar el archivo:{nombre_archivo}")

    elif accion == 3:
        ruta = './' + nombre_archivo
        if os.path.isfile(ruta):
           os.system(f"cat {nombre_archivo}") 
           input("Oprima Enter para continuar...")
        else:
            print(f"el archivo{nombre_archivo} no existe")
            input("Oprima Enter para continuar...")


def realizar_accion(accion,socket,direccion):
    listar()
    separador()
    nombre_archivo = ' '
    if accion == 'nuevo':
        print("Recibiendo nuevo archivo...")
        nombre_archivo = archivo.recibir_archivo(socket,direccion)
        if(nombre_archivo != ' '):
            print("se recibio el archivo exitosamente")
            print("contenido del archivo: ")
            os.system(f"cat {nombre_archivo}")
        else:
            print("No se recibio el archivo correctamente")
        
    elif accion == 'eliminar':
        print("Eliminando archivo...")
        respuesta = socket.recvfrom(buffer_nombre_archivo)
        nombre_archivo = respuesta.strip()
        if archivo.eliminar_archivo(nombre_archivo):
            print(f"Archivo:{nombre_archivo} se elimino correctamente")
            listar()
        else:
            print("No se pudo eliminar el archivo")

    return nombre_archivo


def checar_cambios(archivo):
    try:
        indice = lista_archivos.index(archivo)
        tam_archivo_viejo = tam_archivos[indice] 
        tam_archivo_actual = os.stat(archivo).st_size
        if tam_archivo_viejo != tam_archivo_actual:
            return True
        else:
            return False
    except:
        return False

def distribuir_accion(accion,nombre_archivo):
    if accion == 'nuevo':
        accion_cliente = 1
    elif accion == 'eliminar':
        accion_cliente = 2
    #semaforo = threading.Semaphore()
    #semaforo.acquire()
    hilo1 = threading.Thread(target=cliente,
        args=(PORT_SERVIDOR2,HOST_SERVIDOR2,accion_cliente,nombre_archivo))
    hilo1.start()
    hilo1.join()
    #semaforo.release()
    #semaforo.acquire()
    hilo2 = threading.Thread(target=cliente,
        args=(PORT_SERVIDOR3,HOST_SERVIDOR3,accion_cliente,nombre_archivo))
    hilo2.start()
    hilo2.join()
    #semaforo.release()
    
def cliente(*args):
    puerto = args[0]
    host = args[1]
    accion = args[2]
    direccion = (host,puerto)
    nombre_archivo = args[3]
    print(f"Mandando a petición al servidor con puerto {puerto}")
    with socket.socket(socket.AF_INET,socket.SOCK_DGRAM) as sock:
        sock.sendto(bytes("soycliente",'utf-8'),direccion) 
        time.sleep(0.02)
        print(f"se manda el archivo {nombre_archivo} accion:{accion} \
            servidor:{socket}")
        avisar(accion,socket,direccion,nombre_archivo)

def monitorear_servidor_maestro(*args):
    while True:
        archivos = os.listdir("./")
        for archivo in archivos:
            if os.path.isfile(archivo):
                if checar_cambios(archivo):
                    separador()
                    print("Se encontro una actualización") 
                    print("Procediendo a realizar actualización")
                    actualizar_lista_archivos()
                    distribuir_accion('nuevo',archivo)

def monitorear_servidor_cliente(*args):
    while True:
        archivos = os.listdir("./")
        for archivo in archivos:
            if os.path.isfile(archivo):
                if checar_cambios(archivo):
                    separador()
                    print("Se encontro una actualización") 
                    print("Procediendo a realizar actualización")
                    actualizar_lista_archivos()
                    hilo1 = threading.Thread(target=cliente,
                    args=(PORT_MAESTRO,HOST_MAESTRO,1,archivo))
                    hilo1.start()
                    hilo1.join()


                