#include <iostream>
#include <vector>

using namespace std;

struct hotel
{
    int precio{};
    vector<int> lugaresXsem{};
};

void Iniciar(vector<int> &respuestas);
void recibir_datos(vector<hotel> &hles, int num_h, int num_s);
int Buscar_hotel(vector<hotel> &hles, int ptes, int pto, int num_h, int num_s);
int Sacar_precio(hotel &htel, int num_s, int ptes);
bool verificar_semanas(vector<int> &lugaresXsem, int ptes);
int Buscar_minimo(vector<int> &precios);
void Imprimir(const vector<int> respuestas);

int main()
{
    vector<int> respuestas{};
    Iniciar(respuestas);
    Imprimir(respuestas);
    return 0;
}

void Iniciar(vector<int> &respuestas)
{
    vector<hotel> hles{};
    char caracter{};
    int pto{};
    int ptes{};
    int num_hoteles{};
    int num_semanas{};

    while (cin >> ptes >> pto >> num_hoteles >> num_semanas)
    {

        recibir_datos(hles, num_hoteles, num_semanas);
        respuestas.push_back(Buscar_hotel(hles, ptes, pto, num_hoteles, num_semanas));
        hles.clear();
    }
}

void recibir_datos(vector<hotel> &hles, int num_h, int num_s)
{
    hotel aux{};
    vector<int> semanas{};
    for (int i{0}; i < num_h; i++)
    {
        int precio;
        cin >> precio;
        for (int j{0}; j < num_s; ++j)
        {
            int semana;
            cin >> semana;
            cin.ignore();
            semanas.push_back(semana);
        }
        aux.precio = precio;
        aux.lugaresXsem = semanas;
        hles.push_back(aux);
        semanas.clear();
        aux.lugaresXsem.clear();
    }
}

int Buscar_hotel(vector<hotel> &hles, int ptes, int pto, int num_h, int num_s)
{
    vector<int> precios{};
    int precio{};
    for (auto &htel : hles)
    {
        precio = Sacar_precio(htel, num_s, ptes);
        if (precio > pto)
            precios.push_back(-1);
        else
            precios.push_back(precio);
    }

    return Buscar_minimo(precios);
}

int Sacar_precio(hotel &htel, int num_s, int ptes)
{
    if (!verificar_semanas(htel.lugaresXsem, ptes))
        return -1;

    return htel.precio * ptes;
}

bool verificar_semanas(vector<int> &lugaresXsem, int ptes)
{
    for (auto lugar : lugaresXsem)
        if (lugar == 0)
            return false;

    return true;
}

int Buscar_minimo(vector<int> &precios)
{
    int minimo = 1000001;
    bool bandera{false};
    for (auto &precio : precios)
        if (precio < minimo && precio != -1)
        {
            minimo = precio;
            bandera = true;
        }

    if (bandera)
        return minimo;
    else
        return -1;
}

void Imprimir(const vector<int> respuestas)
{
    for (auto const respuesta : respuestas)
        if (respuesta == -1)
            cout << "stay home" << endl;
        else
            cout << respuesta << endl;
}
