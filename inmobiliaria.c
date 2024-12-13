#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

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

struct inmueble * valida_avisos(struct inmueble *todos_los_avisos, int cantidad_avisos_cargados, int *cantidad_avisos_validos, char categorias[6][10]){
    static struct inmueble avisos_validos[1500];
    int i,valido_tel_cat,valido_duplicidad;
    static char telefono[15] = {0};
    static char categoria[10] = {0};
    static char cod_usu[10] = {0};

    for(i = 0; i < cantidad_avisos_cargados; i++){
        strcpy(telefono,todos_los_avisos[i].telefono);
        strcpy(categoria,todos_los_avisos[i].categoria);
        strcpy(cod_usu, todos_los_avisos[i].cod_usuario);
        valido_tel_cat = valida_tel_cat(telefono,categoria,categorias);
        valido_duplicidad = valida_duplicidad_aviso(cod_usu,todos_los_avisos);
        if(valido_tel_cat == 1 && valido_duplicidad == 1){
            strcpy(avisos_validos[*cantidad_avisos_validos].cod_usuario,cod_usu);
            strcpy(avisos_validos[*cantidad_avisos_validos].descrip_aviso,todos_los_avisos[i].descrip_aviso);
            strcpy(avisos_validos[*cantidad_avisos_validos].categoria, categoria);
            strcpy(avisos_validos[*cantidad_avisos_validos].telefono, telefono);
            (*cantidad_avisos_validos)++;
            Sleep(2000);
            printf("\n");
            printf("\n *** Aviso valido *** \n");
        } else{
            sleep(2000);
            printf("\n");
            printf("\n x Aviso no valido x \n");
        }
    }

    return avisos_validos;
}

int valido_tel_cat(char *telefono, char *categoria, char categorias[6][10]){
  int long_tel,i,contador_digitos = 0,pos = 0, categoria_encontrada = 0;

    long_tel = strlen(telefono);

    for(i = 0; i < long_tel; i++){
        if(isdigit(telefono[i]) != 0){
            contador_digitos++;
        } else{
            break;
        }
    }

    do{
        if(strcmp(categoria,categorias[pos]) == 0){
            categoria_encontrada = 1;
            break;
        } else{
            pos++;
        }
    } while(pos < 6 && categoria_encontrada == 0);

    categoria_encontrada == 1 && contador_digitos == long_tel ? return 1 : return 0;
}

int valido_duplicidad(char *cod_usu, struct inmueble *todos_los_avisos){
    int usuario_duplicado = 0,i;

    for(i = 0; usuario_duplicado >= 0 && usuario_duplicado < 2; i++){
        if(strcmp(cod_usu,todos_los_avisos[i].cod_usuario) == 0){
            usuario_duplicado++;
        }
    }

    usuario_duplicado === 1 ? return 1 : return 0;
}
