#include <mihilo.h>

void miHilo::buscar_en_linea(QStringList linea)
{
    foreach (QString palabra, linea)
    {
       this->buscar_palabra(palabra) ;
    }
}
