typedef struct Pixel
{
	int r;
	int g;
	int b;
}Pixel;

typedef struct Imagen
{
	int altura;
	int base;
	Pixel **matriz;
}Imagen;

void Leer(char nombre_imagen[],Imagen *m);
void ReservarMemoria(Imagen *m);
void Escribir(char nombre_imagen[],Imagen *m);
void Filtro_RGB(char filtro,Imagen *m,Imagen *filtrada);
void Inicializar(Imagen *m,int base,int altura);
void AsignarPixel(Pixel *p, int r, int g, int b);
void copiarImagen(Imagen *original, Imagen *copia);
