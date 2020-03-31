#include<iostream>

using namespace std;

long long fibo_din(int num);

int main()
{
    int num;
    cout << "ingrese num: ";
    cin >> num;
    cout << "fibo: " << fibo_din(num) << endl;
    return 0;
}

long long fibo_din(int num)
{
    long long *tabla;
    if(num == 1 || num == 0)
        return 1;
    else
    {
        tabla = new long long[num];
        tabla[0] = 0;
        tabla[1] = 1;
        for(int i{2}; i <= num; ++i)
            tabla[i] = tabla[i - 1] + tabla[i - 2];
    }
    return tabla[num];
}
