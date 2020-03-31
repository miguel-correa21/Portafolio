import socket
HOST = '127.0.0.1' #localhost
PORT = 8006 #puerto desde el que se escucha
            #puertos no privilegiados > 1023
BUFFER = 1024

#función encargada de establecer y mantener una 
#conversación entre este servidor y el cliente
#mediante el canal de comunicación 'conexion'
def chatear(conexion):
    respuesta = ''
    datos = ''
    while(str(respuesta) != "adios"):
        datos = conexion.recv(BUFFER).decode("utf-8")
        print("Cliente: ",datos) 
        if(str(datos) == "adios"):
            break;
        respuesta = input("Servidor: ")
        conexion.send(bytes(respuesta,'utf-8'))


##creamos el socket con la configuración especificada
#utilizamos with para no tener que utilizar close
with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as ser:
    ser.bind((HOST,PORT))
    ser.listen()
    conexion,dir = ser.accept()
    with conexion:
        print("Se conecto con ", dir)
        chatear(conexion)
