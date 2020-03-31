#!/usr/bin/python3.7
from tkinter import *
import matplotlib.pyplot as plt
import operator
from scipy import signal

#keys son el eje_x y values son eje_y
s1 = {} 
s2 = {} 
conjunto_x = {}
resul = {}
resultado_x = []
resultado_y = []
ampli = False
atenue = False
se_ocupa_signal2 = False

def reiniciar():
    global ampli
    global atenue
    ampli = False
    atenue = False
    signal_text1_x.set('')
    signal_text1_y.set('')
    signal_text2_x.set('')
    signal_text2_y.set('')
    result_x.set('')
    result_y.set('')
    return

def get_valores():
    global s1
    global s2
    global conjunto_x
    bandera = False
    if(signal_text1_x.get() != '' and signal_text1_y.get() != ''):
        s1_x = [int(n) for n in signal_text1_x.get().split(',')]
        s1_y = [float(n) for n in signal_text1_y.get().split(',')]
        s2_x = [int(n) for n in signal_text2_x.get().split(',')]
        s2_y = [float(n) for n in signal_text2_y.get().split(',')]
        tam_s1 = len(s1_x)
        tam_s2 = len(s2_x)
        for i in range(tam_s1):
            s1[s1_x[i]] = s1_y[i]

        for n in range(tam_s2):
            s2[s2_x[n]] = s2_y[n]
        aux = set(s1_x)
        aux2 = set(s2_x)
        conjunto_x = aux | aux2
        bandera = True

    return bandera


def rellenar():
    global conjunto_x
    global s2
    global s1
    for eje_x in list(conjunto_x):
        if(not eje_x in list(s1.keys())):
            s1[eje_x] = 0.0
        if(not eje_x in list(s2.keys())):
            s2[eje_x] = 0.0


def sumar():
    global conjunto_x
    global s1
    global s2
    global resul
    global resultado_x
    global resultado_y
    if(get_valores()):
        rellenar()
        for eje_x in list(conjunto_x):
            resul[eje_x] = s1[eje_x] + s2[eje_x]

        ordenado = dict(sorted(resul.items(),key=operator.itemgetter(0)))
        resultado_x = list(ordenado.keys())
        resultado_y = list(ordenado.values())
        result_x.set(str(resultado_x))
        result_y.set(str(resultado_y))
    return

def restar():
    global conjunto_x
    global s1
    global s2
    global resul
    global resultado_x
    global resultado_y
    if(get_valores()):
        rellenar()
        for eje_x in list(conjunto_x):
            resul[eje_x] = s1[eje_x] - s2[eje_x]

        ordenado = dict(sorted(resul.items(),key=operator.itemgetter(0)))
        resultado_x = list(ordenado.keys())
        resultado_y = list(ordenado.values())
        result_x.set(str(resultado_x))
        result_y.set(str(resultado_y))
    return

def amplificacion():
    global resultado_x
    global resultado_y
    global ampli
    s1_x = [int(n) for n in signal_text1_x.get().split(',')]
    s1_y = [float(n) for n in signal_text1_y.get().split(',')]
    constante = int(signal_text2_x.get())
    for i in range(len(s1_y)):
        s1_y[i] = s1_y[i] * constante

    resultado_x = s1_x 
    resultado_y = s1_y
    result_x.set(str(resultado_x))
    result_y.set(str(resultado_y))
    ampli = True
    return

def atenuacion():
    global resultado_x
    global resultado_y
    global atenue
    s1_x = [int(n) for n in signal_text1_x.get().split(',')]
    s1_y = [float(n) for n in signal_text1_y.get().split(',')]
    constante = int(signal_text2_x.get())
    for i in range(len(s1_y)):
        s1_y[i] = s1_y[i] / constante

    resultado_x = s1_x 
    resultado_y = s1_y
    result_x.set(str(resultado_x))
    result_y.set(str(resultado_y))
    atenue = True
    return

def reflexion():
    global s1
    global resul
    global resultado_x
    global resultado_y
    if(signal_text1_x != '' and signal_text1_y != ''):
        s1_x = [int(n) for n in signal_text1_x.get().split(',')]
        s1_y = [float(n) for n in signal_text1_y.get().split(',')]
        
        for i in range(len(s1_x)):
            s1_x[i] = (-1) * s1_x[i]

        resultado_x = s1_x
        resultado_y = s1_y 
        result_x.set(str(resultado_x))
        result_y.set(str(resultado_y))
    return


def desplazando():
    global result_x
    global result_y
    global desplazar_n
    global resultado_x
    global resultado_y
    s1_x = [int(n) for n in signal_text1_x.get().split(',')]
    s1_y = [float(n) for n in signal_text1_y.get().split(',')]
    n = int(desplazar_n.get())
    print(n)
    if n > 0:
        for i in range(n):
            aux = s1_x[0]
            aux = aux - 1
            s1_x.insert(0,aux)
            s1_y.append(0)
    else:
        #for i in range(n):
        j = 0
        while j > n:
            aux = s1_x[len(s1_x) - 1]
            aux = aux + 1
            s1_x.append(aux)
            s1_y.insert(0,0.0)
            print(s1_y)
            j = j - 1


    resultado_x = s1_x
    resultado_y = s1_y 
    result_x.set(str(resultado_x))
    result_y.set(str(resultado_y))
    return

def desplazamiento():
    global root
    if(signal_text1_x != '' and signal_text1_y != ''):
        desplazar = Toplevel(root)
        desplazar.resizable(0,0)
        desplazar.title("Desplazamiento")
        desplazar.config(bd=15)
        
        entrada = Frame(desplazar,width=50,height=30,bg="white")
        boton = Frame(desplazar,width=30,height=10)

        entrada.pack(fill='x')
        entrada.config(bd=5)
        boton.pack(fill='x',side='bottom')

        ld1 = Label(entrada,text="Ingrece el n-desplazamiento")
        ld1.grid(row=0, column=1, sticky="e", padx=5, pady=5)
        ed1 = Entry(entrada, justify="center", textvariable=desplazar_n)
        ed1.grid(row=0, column=2, padx=5, pady=5)

        bt1 = Button(boton, text="Aceptar", command=desplazando)
        bt1.pack(side="left")
        bt1.config(font="Arial 15")
    return


def interpolar():
    global interpolar_n
    global result_x
    global result_y
    global resultado_x
    global resultado_y
    k = int(interpolar_n.get()) - 1
    s1_x = [int(n) for n in signal_text1_x.get().split(',')]
    s1_y = [float(n) for n in signal_text1_y.get().split(',')]

    nueva_y = []
    for i in range(len(s1_y)):
        if s1_x[i] == 0:
            centro = s1_y[i]
        nueva_y.append(s1_y[i])
        for j in range(k):
            nueva_y.append(0.0)


    contador_neg = 0
    condicion = True
    while (condicion):
        if(nueva_y[contador_neg] == centro):
            condicion = False
        else:
            contador_neg += 1

    total_neg = contador_neg
    nueva_x = []
    while(contador_neg > 0):
        aux = -contador_neg
        nueva_x.append(aux)
        contador_neg -= 1

    nueva_x.append(0)

    aumento = len(nueva_y) - total_neg
    contador = 1
    while(contador < aumento):
        nueva_x.append(contador)
        contador += 1
    resultado_x = nueva_x
    resultado_y = nueva_y
    result_x.set(str(resultado_x))
    result_y.set(str(resultado_y))
    return


def interpolacion():
    global root
    if(signal_text1_x != '' and signal_text1_y != ''):
        inter = Toplevel(root)
        inter.resizable(0,0)
        inter.title("Interpolacion")
        inter.config(bd=15)
        
        entrada = Frame(inter,width=50,height=30,bg="white")
        boton = Frame(inter,width=30,height=10)

        entrada.pack(fill='x')
        entrada.config(bd=5)
        boton.pack(fill='x',side='bottom')

        ld1 = Label(entrada,text="Ingrece el k-interpolacion")
        ld1.grid(row=0, column=1, sticky="e", padx=5, pady=5)
        ed1 = Entry(entrada, justify="center", textvariable=interpolar_n)
        ed1.grid(row=0, column=2, padx=5, pady=5)

        bt1 = Button(boton, text="Aceptar", command=interpolar)
        bt1.pack(side="left")
        bt1.config(font="Arial 15")
    return

def diezmar():
    global diez_n
    global result_x
    global result_y
    global resultado_x
    global resultado_y
    k = int(diez_n.get()) - 1
    s1_x = [int(n) for n in signal_text1_x.get().split(',')]
    s1_y = [float(n) for n in signal_text1_y.get().split(',')]

    centro = s1_x.index(0)
    nueva_y = [s1_y[centro]]
    nueva_x = [s1_x[centro]]
    i = centro
    while( i >= 0):
        if s1_x[i] % k == 0:
            nueva_x.insert(0,s1_x[i])
            nueva_y.insert(0,s1_y[i])
        i -= 1
        
    i = centro
    while(i < len(s1_y)):
        if s1_x[i] % k == 0:
            nueva_x.append(s1_x[i])
            nueva_y.append(s1_y[i])
        i += 1

        
    resultado_x = nueva_x
    resultado_y = nueva_y
    result_x.set(str(resultado_x))
    result_y.set(str(resultado_y))
    return 


def diezmacion():
    global root
    if(signal_text1_x != '' and signal_text1_y != ''):
        diez = Toplevel(root)
        diez.resizable(0,0)
        diez.title("Diezmar")
        diez.config(bd=15)
        
        entrada = Frame(diez,width=50,height=30,bg="white")
        boton = Frame(diez,width=30,height=10)

        entrada.pack(fill='x')
        entrada.config(bd=5)
        boton.pack(fill='x',side='bottom')

        ld1 = Label(entrada,text="Ingrece el k-diezmaciones")
        ld1.grid(row=0, column=1, sticky="e", padx=5, pady=5)
        ed1 = Entry(entrada, justify="center", textvariable=diez_n)
        ed1.grid(row=0, column=2, padx=5, pady=5)

        bt1 = Button(boton, text="Aceptar", command=diezmar)
        bt1.pack(side="left")
        bt1.config(font="Arial 15")
    return

def convolucion():
    global conjunto_x
    global s1
    global s2
    global resultado_x
    global resultado_y
    if(signal_text1_x != '' and signal_text1_y != ''):
        s1_x = [int(n) for n in signal_text1_x.get().split(',')]
        s1_y = [float(n) for n in signal_text1_y.get().split(',')]
        s2_x = [int(n) for n in signal_text2_x.get().split(',')]
        s2_y = [float(n) for n in signal_text2_y.get().split(',')]

    listas = []
    if(len(s1_y) > len(s2_y)):
        mayor = s1_y
        menor = s2_y
    else:
        mayor = s1_y
        menor = s2_y
    
    for i in menor:
        nueva = []
        for j in mayor:
            nueva.append(i * j)
        listas.append(nueva)
    

    nueva_y = []
    total_elem = len(s1_y) + len(s2_y) - 1
    #inicio=0
    final=len(menor) - 1
    #rellenamos todas las listas para que tengan el mismo número de elementos
    for i in range(len(menor)):
        for k in range(i):
            listas[i].insert(k,0.0)
    index = 0
    while (final >= 0):
        for j in range(final):
            listas[index].append(0.0)
        index  += 1
        final -= 1

    print(listas)
    
    for index in range(total_elem):
        suma = 0
        for lis in listas:
            suma += lis[index]
        nueva_y.append(suma)

    centro_is1 = s1_x.index(0)
    centro_is2 = s2_x.index(0)

    nueva_x = [0]
    final = centro_is1 + centro_is2
    c = -1
    for negativos in range(final):
        nueva_x.insert(0,c)
        c -= 1

    c = 1
    for positivos in range(final,total_elem-1):
        nueva_x.append(c)
        c += 1

    resultado_x = nueva_x
    resultado_y = nueva_y
    result_x.set(str(resultado_x))
    result_y.set(str(resultado_y))
    return

def graficar():
    global resultado_x
    global resultado_y
    global atenue
    global ampli
    bandera = False
    if(signal_text1_x.get() != '' and signal_text1_y.get() != ''):
        s1_x = [float(n) for n in signal_text1_x.get().split(',')]
        s1_y = [float(n) for n in signal_text1_y.get().split(',')]
    if(not atenue and not ampli and signal_text2_x.get() != '' and signal_text2_y.get() != 0):
        s2_x = [float(n) for n in signal_text2_x.get().split(',')]
        s2_y = [float(n) for n in signal_text2_y.get().split(',')]
        bandera = True

    
    ax = plt.subplot(221) 
    ax.stem(s1_x,s1_y)
    ax.set_title("Señal 1")
    if (bandera and not ampli and not atenue):
        ax1 = plt.subplot(222)
        ax1.stem(s2_x,s2_y)
        ax1.set_title("Señal 2")
    
    ax3 = plt.subplot(212)
    ax3.stem(resultado_x,resultado_y)
    ax3.set_title("Resultado")


    plt.show()
    return


root = Tk()
root.title("proyecto de señales")
root.config(bd=15)
root.config(width=600, height=1200)
root.config(bg="white")

#variables 
signal_text1_x = StringVar()
signal_text1_y = StringVar()
signal_text2_x = StringVar()
signal_text2_y = StringVar()
result_x = StringVar()
result_y = StringVar()
desplazar_n = StringVar()
interpolar_n = StringVar()
diez_n = StringVar()

numero1 = Frame(root, width=600, height=100, bg="white")
numero2 = Frame(root, width=600, height=100, bg="white")
resultado = Frame(root, width=600, height=200, bg="white")
botones = Frame(root, width=500, height=500)
botones2 = Frame(root, width=500, height=500)
botones3 = Frame(root, width=500, height=500)
botones4 = Frame(root, width=500, height=500)

botones.pack(fill="y", side="bottom")
botones2.pack(fill="y",side="bottom")
botones3.pack(fill="y",side="bottom")
botones4.pack(fill="y",side="bottom")
numero1.pack(fill="x")
numero1.config(bd=5)
numero2.pack(fill="x")
numero2.config(bd=5)
resultado.pack(fill="x")
resultado.config(bd=5)

# etiquetas de texto
Label(numero1, text="Señal 1:",font=('Arial',20)).grid()
l1 = Label(numero1, text="eje x:",font=('Arial',20))
l1.grid(row=0, column=1, sticky="e", padx=5, pady=5)
e1 = Entry(numero1, justify="center", textvariable=signal_text1_x,width=50)
e1.grid(row=0, column=2, padx=5, pady=5)
l2 = Label(numero1, text="eje y:",font=("Arial",20))
l2.grid(row=0, column=3, sticky="e", padx=5, pady=5)
e2 = Entry(numero1, justify="center", textvariable=signal_text1_y,width=50)
e2.grid(row=0, column=4, padx=5, pady=5)

# numero 2
Label(numero2, text="Señal 2:",font=("Arial",20)).grid()
l3 = Label(numero2, text="eje x:",font=("Arial",20))
l3.grid(row=0, column=1, sticky="e", padx=5, pady=5)
e3 = Entry(numero2, justify="center", textvariable=signal_text2_x,width=50)
e3.grid(row=0, column=2, padx=5, pady=5)
l4 = Label(numero2, text="eje y:",font=("Arial",20))
l4.grid(row=0, column=3, sticky="e", padx=5, pady=5)
e4 = Entry(numero2, justify="center", textvariable=signal_text2_y,width=50)
e4.grid(row=0, column=4, padx=5, pady=5)

Label(resultado, text="Resultado:",font=("Arial",20)).grid()
l1 = Label(resultado, text="x:",font=("Arial",20))
l1.grid(row=0, column=1, sticky="e", padx=5, pady=5)
e4 = Entry( resultado, justify="center", textvariable=result_x, state="disabled",width=50)
e4.grid(row=0,column=2,padx=25,pady=25)
l2 = Label(resultado, text="y:",font=("Arial",20))
l2.grid(row=0, column=3, sticky="e", padx=5, pady=5)
e5 = Entry( resultado, justify="center", textvariable=result_y,  state="disabled",width=50)
e5.grid(row=0,column=4,padx=25,pady=25)

#botones
b1 = Button(botones4,text="Sumar",command=sumar)
b1.pack(side="left")
b1.config(font="Arial 30")


b2 = Button(botones4,text="Restar",command=restar)
b2.pack(side="left")
b2.config(font="Arial 30")


b3 = Button(botones3,text="Amplificacion",command=amplificacion)
b3.pack(side="left")
b3.config(font="Arial 30")

b3_1 = Button(botones3,text="Atenuación",command=atenuacion)
b3_1.pack(side="left")
b3_1.config(font="Arial 30")

b4 = Button(botones3,text="Reflexion",command=reflexion)
b4.pack(side="left")
b4.config(font="Arial 30")

b10 = Button(botones3, text="Limpiar", command=reiniciar)
b10.config(font="Arial 30", bg="grey")
b10.pack(side="left")

b5 = Button(botones,text="Desplazamiento",command=desplazamiento)
b5.pack(side="left")
b5.config(font="Arial 26")

b6 = Button(botones,text="Interpolacion",command=interpolacion)
b6.pack(side="left")
b6.config(font="Arial 26")

b7 = Button(botones2,text="Diezmacion",command=diezmacion)
b7.pack(side="left")
b7.config(font="Arial 26")

b8 = Button(botones2,text="Convolucion",command=convolucion)
b8.pack(side="left")
b8.config(font="Arial 26")

b9 = Button(botones2,text="Graficar",command=graficar)
b9.pack(side="left")
b9.config(font="Arial 26")



root.mainloop()
