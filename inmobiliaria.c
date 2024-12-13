#include <stdio.h>

struct inmueble{
    char cod_usuario[10];
    char descrip_aviso[300];
    char categoria[10];
    char telefono[15];
};

void carga_avisos(struct inmueble*,int*);
void carga_categorias(char categorias[6][10]);
struct inmueble * valida_avisos(struct inmueble*,int,int*,char categoria[6][10]);
int valida_tel_cat(char*,char*,char[6][10]);
int valida_duplicidad_aviso(char*,struct inmueble*);
void imprime(struct inmueble*,int);

int main(){
    struct inmueble todos_los_avisos[1500];
    struct inmueble *avisos_validos;
    int cantidad_avisos_cargados = 0,cantidad_avisos_validos = 0;
    char categorias[6][10];

    carga_avisos(todos_los_inmuebles,&cantidad_avisos_cargados);
    carga_categorias(categorias);
    avisos_validos = valida_avisos(todos_los_avisos,cantidad_avisos_cargados,&cantidad_avisos_validos,categorias);
    imprime(avisos_validos,cantidad_avisos_validos);

    return 0;
}





