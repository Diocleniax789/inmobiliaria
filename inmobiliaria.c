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
void imprime(struct inmueble*);

int main(){




    return 0;
}
