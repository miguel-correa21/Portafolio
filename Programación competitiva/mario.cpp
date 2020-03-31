#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

void tratarCaso(vector<int> &muros,int &altos,int &bajos);
void limpiar_var(int &alto,int &bajo,int &num_muros,vector<int> &v);


int main()
{
    vector<tuple<int,int>> caso;
    int altos{0};
    int bajos{0};
    int num_casos{};
    int num_muros,muro,j;
    vector<int> muros{};

    cin >> num_casos;
    for(int i{0}; i < num_casos; ++i)
    {
        cin >> num_muros;
        for(j = 0; j < num_muros; ++j)
        {
            cin >> muro;
            muros.push_back(muro);
            cin.ignore();
        }

        tratarCaso(muros,altos,bajos);
        caso.push_back(make_tuple(altos,bajos));
        limpiar_var(altos,bajos,num_muros,muros);
    }
    
    for(int k{0}; k < caso.size(); k++)
        cout << "Case " << k+1 <<": "<< get<0>(caso[k]) << " " << get<1>(caso[k]) << endl;
    return 0;
}

void tratarCaso(vector<int> &muros,int &altos,int &bajos)
{
    int primero{muros[0]};
    for(int i{1}; i < muros.size(); ++i)
    {
        if(primero < muros[i])
            altos++;
        else if(primero > muros[i])
            bajos++;
        primero = muros[i];
    }
}

void limpiar_var(int &alto,int &bajo,int &num_muros,vector<int> &v)
{
    alto = 0;
    bajo = 0;
    num_muros = 0;
    v.clear();
}
