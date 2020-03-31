#include <iostream>
#include <cmath>
#include <vector>
#define max 2000000000
#define digitos_max 10
using namespace std;


int Calcular_base(long int numero,long int modulo,int &num_digitos);
int Calcular_elemento(const vector<int> &vec,int base);
void Calcular_digitos(int num_digitos, vector<int> &vec,int base,long int digito);
int Resolver_caso(int &num_digitos, vector<int> &vec,int base,long int digito);
int Sumar(const vector<int> &vec);
void Imprimir(const vector<int> &respuestas);

int main()
{
    int num_digitos = digitos_max;
    long int digito{max};
    vector<int> vec{};
    int base{};
    vector<int> respuestas{};

    while(digito != 0)
    {
        cin >> digito;
        if(digito != 0)
          respuestas.push_back(Resolver_caso(num_digitos,vec,base,digito));
    }
    
    Imprimir(respuestas);
    return 0;
}

int Calcular_base(long int numero,long  int modulo, int &num_digitos)
{
    int base = int(numero/modulo);
    if(base  > 0)
        return base;
    else 
    {
        num_digitos -= 1;
        return Calcular_base(numero,(modulo/10),num_digitos);
    }
}

int Calcular_elemento(const vector<int> &vec,int base)
{
    int elemento{base};
    int potenciador{10};
    
    if(!vec.empty())
        for(int i = vec.size() - 1; i >= 0 ; --i)
        {
            elemento -= vec[i]*potenciador;
            potenciador *= 10;
        }
    return elemento;
}

void Calcular_digitos(int num_digitos, vector<int> &vec,int base, long int digito)
{
   int denominador = pow(10,num_digitos-1);
   int potenciador{1};
   for(int i{0}; i < num_digitos; ++i) 
   {
       base  = int((digito*potenciador)/denominador);
       vec.push_back(Calcular_elemento(vec,base));
       potenciador *= 10;
   }
}

int Resolver_caso(int &num_digitos, vector<int> &vec,int base, long int digito)
{
    long int resultado = digito;
    do
    {
        base = Calcular_base(resultado,(max/2),num_digitos);
        Calcular_digitos(num_digitos,vec,base,resultado);
        resultado = Sumar(vec);
        num_digitos = digitos_max;
        vec.clear();
    }while((resultado/10) != 0);

    return resultado;
}

int Sumar(const vector<int> &vec)
{
    int suma{0};
    for(const auto &numero: vec)
        suma += numero;
    
    return suma;
}

void Imprimir(const vector<int> &respuestas)
{
    for(const auto &respuesta :respuestas)
        cout << respuesta << endl;
}
