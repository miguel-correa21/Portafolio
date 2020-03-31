#include "mihilo.h"
#include <QtCore>
#include <iostream>
#include <mutex>

 miHilo::miHilo(QString nombre_libro):
     libro(nombre_libro),nombre_libro(nombre_libro)
 {
     foreach (auto &palabra, palabras)
     {
         conjunto_datos datos;
         datos.palabra = palabra;
         datos.contador = 0;
         palabras_con_contadores.push_back(datos);
     }
 }


void miHilo::run()
{
    this->id_hilo = static_cast<unsigned int>(pthread_self());
    if(!libro.open(QFile::ReadOnly | QIODevice::Text))
    {
        std::cout << "no se puede Abrir el archivo" << std::endl;
    }
    QTextStream in(&libro);
    QString linea;
    QStringList lista;
    while(!in.atEnd())
    {
        //emit enviar_trabajo(this->id_hilo);
        {
            std::lock_guard<std::mutex> lock(this->mtx);
            printf("hilo trabajando : %u\n",this->id_hilo);
        }
        linea  = in.readLine();
        lista = linea.split(' ');
        this->buscar_en_linea(lista);
    }
    emit enviar_datos(this);
    libro.close();
}

