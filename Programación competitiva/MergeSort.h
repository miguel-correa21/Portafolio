#ifndef _MERGE_SORT_H
#define _MERGE_SORT_H


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



#endif
