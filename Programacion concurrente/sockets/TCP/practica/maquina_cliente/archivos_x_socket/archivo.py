import os
from subprocess import Popen
#Las funciones implementadas se importan
#import from archivos_x_socket.archivos import *

'''
Conexion es el descriptor de archivo que retorna la función
accept() y connect() del modulo socket
nombre_archivo archivo es una cadena
y buffer es el tamaño en bytes que se mandan
el valor normalmente es de 1024.
Esta Función recibe desde el canal de conexción del 
socket la información necesaria para agregar un 
archivo en la maquina en la que se ejecuta, esta puede ser
servidor o cliente de forma indiferente, primero recibe  
el nombre del archivo para crearlo después va recibiendo
una linea de texto del archivo original hasta que se 
reciba la cadena "Fin" la cual avisa que
se copio todo del archivo original
'''
def recibir_archivo(conexion,tam_buffer,accion = ''):
    nombre_archivo = str(conexion.recv(tam_buffer).decode("utf-8"))

    if accion == "actualizar":
        ruta = './' + nombre_archivo
        if not os.path.isfile(ruta):
            return ' ' 

    archivo =  open(nombre_archivo,'w')
    while True: 
        datos = conexion.recv(tam_buffer).decode("utf-8")
        if str(datos) == 'Fin':
            archivo.close()
            break
        else:
            archivo.write(str(datos))
    return nombre_archivo

'''
Conexion es el descriptor de archivo que retorna la función
accept() y connect() del modulo socket
nombre_archivo archivo es una cadena.
La función manda desde el canal de conexión del socket
la información del archivo que se tiene que mandar, se puede
ejecutar desde un proceso servidor o un proceso cliente,
primero se manda el nombre del archivo después se manda
el contenido del archivo linea por linea, cuando termina
manda la cadena "Fin" para avisar a la maquina receptora que
se termino de mandar el  contenido del archivo'''
def mandar_archivo(conexion,nombre_archivo,accion = ''):
    if not '.txt' in nombre_archivo:
        nombre_archivo  = nombre_archivo + '.txt'
    conexion.send(bytes(nombre_archivo,'utf-8'))

    if accion == "actualizar":
        ruta = './' + nombre_archivo
        if not os.path.isfile(ruta):
            return False

    with open(nombre_archivo,'r') as archivo:
        for linea in archivo.readlines():
            conexion.send(bytes(linea,'utf-8'))
        
        #mandamos señal de fin de archivo
    conexion.send(bytes("Fin",'utf8'))
    

'''
nombre_archivo es una cadena. La función retorna 
True si se pudo crear el archivo sin problema
en caso contrario retorna False
El archivo se crea mediante el programa vim
el cual se corre como un subprocesso.
'''
def nuevo_archivo(nombre_archivo):
    if not '.txt' in nombre_archivo:
        nombre_archivo = nombre_archivo + '.txt'
    if os.path.isfile(nombre_archivo):
        return True
    return proceso_vim(nombre_archivo)
    
'''
nombre_archivo es una cadena. La función retorna 
True si se pudo eliminar el archivo sin problema
en caso contrario retorna False.
La función primero checa que nombre_archivo
tenga la extención correcta si no es así se agrega
la extencion '.txt'
'''
def eliminar_archivo(nombre_archivo):
    if not '.txt' in nombre_archivo:
        nombre_archivo = nombre_archivo + '.txt'
    if not os.path.isfile(nombre_archivo):
        return False
    os.remove(nombre_archivo)
    return True

'''
nombre_archivo es una cadena. 
Al igual que la función eliminar esta primero checa la extención
si no la tiene se la agrega y también busca si el archivo 
existe si no la tiene  retorna false en caso contrario 
se retorna True
'''
def actualizar_archivo(nombre_archivo):
    if not '.txt' in nombre_archivo:
        nombre_archivo += '.txt'
    if not os.path.isfile(nombre_archivo):
        return False
    return proceso_vim(nombre_archivo)
    
'''
Función que se encarga de correr el programa vim
como un subproceso. el programa se detiene 
hasta que se termina de editar el archivo
retorna True si se termino de ocupar vim 
sin problemas y en caso contrario retorna False
'''
def proceso_vim(nombre_archivo):
    proceso = Popen(['vim',nombre_archivo])
    fin_exitoso = proceso.wait()
    if fin_exitoso == 0:
        return True
    else:
        return False
