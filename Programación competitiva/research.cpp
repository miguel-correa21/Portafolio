#include <iostream>
#include <regex>
#include <string>

using namespace std;

char Comparar(string &entrada);
bool Es_positivo(string &entrada);
bool Es_negativo(string &entrada);
bool Es_Error(string &entrada);

void Imprimir(const char respuestas[], int tam);

int main()
{
    char *respuestas{nullptr};
    int casos{};
    string cadena{};

    cin >> casos;
    respuestas = new char[casos];

    for(int i{0}; i < casos; i++)
    {
        cin >> cadena;
        respuestas[i] = Comparar(cadena);
    }
    Imprimir(respuestas,casos);
    
    delete [] respuestas;
    return 0;
}

char Comparar(string &entrada)
{
    if(Es_positivo(entrada))
        return '+';
    if(Es_negativo(entrada))
        return '-';
    if(Es_Error(entrada))
        return '*';
    else
        return '?';
}

bool Es_positivo(string &entrada)
{
    return (entrada == "1" || entrada == "4" || entrada == "78");
}

void Imprimir(const char respuestas[], int tam)
{
    for(int i{0}; i < tam; i++)
        cout << respuestas[i] << endl;
}
bool Es_negativo(string &entrada)
{
    regex negativo("[0-9]*35");
    return (regex_match(entrada,negativo));
}
bool Es_Error(string &entrada)
{
    regex error("9[0-9]*4");
    return (regex_match(entrada,error));
}
