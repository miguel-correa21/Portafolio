#include <iostream>

using namespace std;

int calcular_prima(int tam, int respeto);
void Imprimir(const int respuestas[], int tam);

int main()
{
    int casos;
    int tam{};
    int num_animales{};
    int Respeto{};
    int *respuestas{nullptr};
    int num_granjeros{};
    int presupuesto{0};

    cin >> casos;
    respuestas = new int[casos];
    for(int i{0}; i< casos; ++i)
    {
        cin >> num_granjeros;
        presupuesto = 0;
        for(int j{0}; j < num_granjeros; ++j)
        {
            cin >> tam >> num_animales >> Respeto;
            presupuesto += calcular_prima(tam,Respeto);
        }
        respuestas[i] = presupuesto;
    }
    
    Imprimir(respuestas,casos);
    delete [] respuestas;
    return 0;
}

int calcular_prima(int tam, int respeto)
{
    return tam*respeto;
}
void Imprimir(const int respuestas[],int tam)
{
    for(int i{0}; i < tam; ++i)
        cout << respuestas[i] << endl;
}

