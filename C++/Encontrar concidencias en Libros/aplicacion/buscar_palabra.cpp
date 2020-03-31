#include <mihilo.h>
#include <iostream>

void miHilo::buscar_palabra(QString palabra)
{
    for(size_t i = 0 ; i < palabras_con_contadores.size(); i++)
    {
        QString aux = palabras_con_contadores[i].palabra;
        if((QString::compare(palabra,aux,Qt::CaseInsensitive) == 0))
            palabras_con_contadores[i].contador++;
        else if(QString::compare(palabra,aux + ",",Qt::CaseInsensitive) == 0)
            palabras_con_contadores[i].contador++;
        else if(QString::compare(palabra,aux + "?",Qt::CaseInsensitive) == 0)
            palabras_con_contadores[i].contador++;
        else if(QString::compare(palabra,aux + ";",Qt::CaseInsensitive) == 0)
            palabras_con_contadores[i].contador++;
        else if(QString::compare(palabra,aux + ":",Qt::CaseInsensitive) == 0)
            palabras_con_contadores[i].contador++;
        else if(QString::compare(palabra,aux + "-",Qt::CaseInsensitive) == 0)
            palabras_con_contadores[i].contador++;
        else if(QString::compare(palabra,aux + "_",Qt::CaseInsensitive) == 0)
            palabras_con_contadores[i].contador++;
        else if(QString::compare(palabra,aux + ".",Qt::CaseInsensitive) == 0)
            palabras_con_contadores[i].contador++;
        else if(QString::compare(palabra,aux + "...",Qt::CaseInsensitive) == 0)
            palabras_con_contadores[i].contador++;
    }

}
