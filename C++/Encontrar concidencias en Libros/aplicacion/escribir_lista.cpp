#include <mihilo.h>

void miHilo::escribir_lista()
{
    QString titulo = "Arhchvio : " + nombre_libro;
    lista->addItem(titulo);
    QString aux;
    foreach (auto par, this->repeticion_palabras)
    {
       if(par.second != 0)
       {
           aux = par.first + QString::number(par.second);
           lista->addItem(aux);
       }
    }
}
