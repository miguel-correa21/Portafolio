//Snail.cpp
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Resultados
{
    int dias;
    bool estado;//salio no salio;
};


void Iniciar(vector<Resultados> &res);
float Calcular(float alturaI, float U,float D,float H);
void Imprimir(const vector<Resultados> &res);
void InicializarDatos(float *total, int *dias,float *alturaI ,bool *bandera);

int main()
{
    cout << std::setprecision(2);
    cout << fixed;
    vector<Resultados> res{};
    Iniciar(res);
    Imprimir(res);
    return 0;
}

void Iniciar(vector<Resultados> &res)
{
    float total,H,U,D,F;
    int dias{1};
    bool estado{};
    float alturaI{};
    bool bandera{};
    int i{0};

    do
    {
        cin  >> H >>U >>D >>F;
        F = F/100 * (U); // se saca el procentaje de fatiga por pies que sube.

        if(H != 0.00)
        {
            InicializarDatos(&total,&dias,&alturaI,&bandera);

            while(bandera)
            {
                total = Calcular(alturaI,U,D,H);
                if(total >= 0.00 && total <= H )
                {
                    alturaI = total;
                    U = U - F;
                    dias++;
                }
                else
                {
                    bandera = false;
                }
            }

            estado = (total <= H)?false:true;
            res.push_back({dias,estado});
        }

    }while(H != 0);
}

float Calcular(float alturaI, float U,float D,float H)
{
    float despues_subido;

    if(U >= 0.0)
        despues_subido = alturaI + U;
    else
        despues_subido = alturaI;

    if(despues_subido > H)
        return despues_subido;
    else
        return (despues_subido - D);
}

void Imprimir(const vector<Resultados> &res)
{
    for(auto const  &resultado: res)
    {
        if(resultado.estado)
            cout << "success on day " << resultado.dias << endl;
         else
            cout << "failure on day " << resultado.dias << endl;
    }
}

void InicializarDatos(float *total, int *dias,float *alturaI ,bool *bandera)
{
    *dias = 1;
    *alturaI = 0.00;
    *total = 0.00;
    *bandera = true;
}
