#include <iostream>

using namespace std;

void resolver_caso(int dragon[], int caballero[], int n, int m);

void Merger(int mat[], int izq, int  medio, int der)
{
	int indiceA = izq;
	int indiceB = medio + 1;
	int indiceT{0};
	int indiceM{};
	int *matrizTem = new int[der-izq+1];
	
	while(indiceA <= medio && indiceB <= der)	
	{
		if(mat[indiceA] <= mat[indiceB])
			matrizTem[indiceT++] = mat[indiceA++];
		else
			matrizTem[indiceT++] = mat[indiceB++];
	}


	while(indiceB <= der)
		matrizTem[indiceT++] = mat[indiceB++];

	while(indiceA <= medio)
		matrizTem[indiceT++] = mat[indiceA++];

	for(indiceM = izq,indiceT = 0 ; indiceM <= der; ++indiceT , ++indiceM)
		mat[indiceM] = matrizTem[indiceT];
	
	delete []matrizTem;
}

void MergeSortAuxiliar(int mat[], int izq, int der)
{
	if(izq < der)
	{
		int medio = (izq + der)/2;

		MergeSortAuxiliar(mat,izq,medio);
		MergeSortAuxiliar(mat,medio + 1,der);
		Merger(mat,izq,medio,der);
	}

}

void MergeSort(int mat[], int tam)
{
	MergeSortAuxiliar(mat,0,tam-1);
}


int main()
{
    int n{};
    int m{};


    cin >> n >> m;
    while(n != 0 || m != 0)
    {
        int *dragon = new int[n];
        int *caballeros = new int[m];

        for(int i{0}; i < n; ++i)
            cin >> dragon[i];
        for(int j{0}; j < m; ++j)
            cin >> caballeros[j];
        
        MergeSort(dragon,n);
        MergeSort(caballeros,m);
        
        resolver_caso(dragon,caballeros,n,m);
        
        delete [] dragon;
        delete [] caballeros;
        cin >> n >> m;
    }
    
    return 0;
}


void resolver_caso(int dragon[], int caballero[], int n, int m)
{
    int oro,d,k;
    oro = d = k = 0;

    while(d < n && k < m)
    {
        while(dragon[d] > caballero[k] && k < m) k++;
        if(k == m) break;
        oro += caballero[k];
        d++; k++;
    }

    if(d == n)
        cout << oro << endl;
    else
        cout << "Loowater is doomed!" << endl;
}
