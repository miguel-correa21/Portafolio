#include <cstdlib>
#include <iostream>

using namespace std;

int Cerrar_brecha(int norte, int sur);
void Imprimir(const bool respuestas[],int tam);

int main()
{
    bool *respuestas{nullptr};
    int casos{};
    int norte{};
    int sur{};
    int num_columnas{};
    bool bandera{};
    int brecha{};

    cin >> casos;
    respuestas = new bool[casos];

    for(int i{0}; i < casos; ++i)
    {
        cin.ignore();
        cin >> num_columnas;
        bandera = true;
        cin >> norte >> sur;
        brecha = Cerrar_brecha(norte,sur);

        for(int j{0}; j < num_columnas-1; ++j)
        {
            cin >> norte >> sur;
            if(brecha != Cerrar_brecha(norte,sur))
                bandera = false;
        }
        respuestas[i] = bandera;
    }
    
    Imprimir(respuestas,casos);
    delete [] respuestas;
    return 0;
}

int Cerrar_brecha(int norte, int sur)
{
    return abs(norte - sur);
}

void Imprimir(const bool respuestas[],int tam)
{
    for(int i{0}; i < tam; ++i)
    {

        if(respuestas[i])
            cout << "yes" << endl;
        else
            cout << "no" << endl;

        if(i != tam-1)
            cout << "\n";
    }
}
