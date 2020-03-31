#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int Calcular_mes(int meses,float inicial,float deuda,float dep[],int tam,int mes[]);
void Imprimir(const vector<int> &respuestas);

int main()
{
    cout << fixed;
    vector<int> respuestas{};
    int meses{0};
    float inicial{0};
    float deuda{0};
    int tam{0};

    while(meses >= 0)
    {
        scanf("%d %f %f %d",&meses,&inicial,&deuda,&tam);
        float depresiacion[tam];
        int mes[tam];
        for(int i{0}; i < tam; i++)
            scanf("%d %f",&mes[i],&depresiacion[i]);
            
        if(meses >= 0)
            respuestas.push_back((Calcular_mes(meses,inicial,deuda,depresiacion,tam,mes)));
    }

    Imprimir(respuestas);
    return 0;
}

int Calcular_mes(int meses,float inicial,float deuda,float dep[],int tam,int mes[])
{
    float original{deuda + inicial};
    float valor{original - dep[0]*original};
    int contador{0};
    float porcentaje{dep[0]};
    float mensualidades{deuda/float(meses)};
    int i{1};

    while(deuda >= valor)
    {
        ++contador;
        if(contador == mes[i])
        {
            porcentaje = dep[i];
            i++;
        }
        valor -= porcentaje*valor;
        deuda -= mensualidades;
//        cout << "valor " << valor << " deuda " << deuda << " porcentaje " << porcentaje
  //           << "mes " << contador << endl;
    }

    return contador;
}

void Imprimir(const vector<int> &respuestas)
{
    for(const auto &respueta : respuestas)
    {
        if(respueta > 1 ||  respueta == 0)
            cout << respueta << " months" << endl;
        else
            cout<< respueta  << " month" << endl;
    }
}
