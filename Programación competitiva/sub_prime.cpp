#include <iostream>

using namespace std;

bool ingresarBancos(int Bancos[],int Deudas[]);
void ingresarDeudas(int num_deudas);
int CalcularBalance(int Bancos[],int Deudas[],size_t i_Acredor,size_t i_Deudor);

int main()
{
    int *deudas{nullptr};
    int *bancos{nullptr};
    size_t num_bancos{};
    size_t num_deudas{};

    cin >> num_bancos >> num_deudas;

    bancos = new int[num_bancos];
    deudas = new int[num_deudas];
    

    delete [] bancos;
    delete [] deudas;

    return 0;
}

bool ingresarBancos(int Bancos[],int Deudas[])
{
    
}

void ingresarDeudas(int num_deudas)
{

}

int CalcularBalance(int Bancos[],int Deudas[],size_t i_Acredor,size_t i_Deudor)
{

}
