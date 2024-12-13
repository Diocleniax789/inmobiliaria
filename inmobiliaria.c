#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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

    carga_avisos(todos_los_avisos,&cantidad_avisos_cargados);
    carga_categorias(categorias);
    avisos_validos = valida_avisos(todos_los_avisos,cantidad_avisos_cargados,&cantidad_avisos_validos,categorias);
    imprime(avisos_validos,cantidad_avisos_validos);

    return 0;
}

void carga_avisos(struct inmueble *todos_los_avisos, int *cantidad_avisos_cargados){
    int i,j;
    char caracter,aviso[300] = {0}, codigo[10] = {0};

    for(i = 0; i < 1500; i++){
        system("cls");
        printf("\n - Para finalizar con la carga, simplemente a la hora de ingresar el codigo, escriba '*' - \n");
        printf("\n Aviso nro %i",i + 1);
        fflush(stdin);
        printf("\n + Codigo de usuario: ");
        scanf("%s",codigo);
        if(strcmp(codigo,"*") == 0){
            printf("\n Finalizando carga...");
            Sleep(2000);
            break;
        } else{
            strcpy(todos_los_avisos[i].cod_usuario,codigo);
            printf("\n + Descripcion del aviso <presione ctrl + c para finalizar>: \n");
            j = 0;
            while((caracter = getchar()) != EOF && j < 300){
                aviso[j] = caracter;
                j++;
            }
            aviso[j] = '\0';
            strcpy(todos_los_avisos[i].descrip_aviso,aviso);
            printf("\n + Categoria: ");
            scanf("%s",todos_los_avisos[i].categoria);
            printf("\n + Telefono: ");
            scanf("%s",todos_los_avisos[i].telefono);
            printf("\n");
            (*cantidad_avisos_cargados)++;
            system("pause");
        }
    }
}

void carga_categorias(char categorias[6][10]){
    int i;

    for(i = 0; i < 6; i++){
        system("cls");
        fflush(stdin);
        printf("\n Categoria nro %i",i + 1);
        printf("\n");
        printf("\n + Escriba el nombre de la categoria: ");
        scanf("%s",categorias[i]);
        printf("\n");
        system("pause");
    }
}

