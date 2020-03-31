#include <iostream>

using namespace std;

int combinatoria(int n,int k);

int main()
{
    int n,k;
    cout << "ingrese la combinatoria a calcular (n, k): ";
    cin >> n >> k;
    cout << "resultado :" << combinatoria(n,k) << endl;
    return 0;
}

int combinatoria(int n,int k)
{
    int **tabla{nullptr};
    int resultado{0};
    int i,j;
    if(k == 0 || k == n)
        return 1;
    else
    {
        //inicialización de tabla
        tabla = new int *[n+1];
        for(i = 0; i <= n; i++)
            tabla[i] = new int [k+1];

        for(i = 0; i <= n; i++) tabla[i][0] = 1;
        for(i = 1; i <= n; i++) tabla[i][1] = i;
        for(i = 2; i <= k; i++) tabla[i][i] = 1;

        for(i = 3; i <= n; i++)
        {
            for(j = 2; j <= n-1; j++)
            {
                if(j <= k)
                    tabla[i][j] = tabla[i-1][j-1] + tabla[i-1][j];
            }
        }
        resultado = tabla[n][k];
        
        for(i = 0; i < n; i++)
            delete [] tabla[i];
        delete [] tabla;
    }

    return resultado;
}
