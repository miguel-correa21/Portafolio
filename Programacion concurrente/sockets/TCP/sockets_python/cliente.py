import socket

HOST = '127.0.0.1'
PORT = 8006
BUFFER = 1024

def chatear(conexion):
    respuesta = ''
    datos = ''
    while(str(respuesta) != "adios"):
        respuesta = input("Cliente: ")
        conexion.send(bytes(respuesta,'utf-8'))
        datos = conexion.recv(BUFFER).decode("utf-8")
        print("Servidor: ",datos) 
        if(str(datos) == "adios"):
            break;

with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as ser:
    ser.connect((HOST,PORT))
    chatear(ser)

