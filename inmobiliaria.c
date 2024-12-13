#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

struct inmueble {
    char cod_usuario[10];
    char descrip_aviso[300];
    char categoria[10];
    char telefono[15];
};

void carga_avisos(struct inmueble*, int*);
void carga_categorias(char categorias[6][10]);
struct inmueble* valida_avisos(struct inmueble*, int, int*, char categorias[6][10]);
int valida_tel_cat(char*, char*, char[6][10]);
int valida_duplicidad_aviso(char*, struct inmueble*, int);
void imprime(struct inmueble*, int);

int main() {
    struct inmueble todos_los_avisos[1500];
    struct inmueble* avisos_validos;
    int cantidad_avisos_cargados = 0, cantidad_avisos_validos = 0;
    char categorias[6][10];

    carga_avisos(todos_los_avisos, &cantidad_avisos_cargados);
    carga_categorias(categorias);
    avisos_validos = valida_avisos(todos_los_avisos, cantidad_avisos_cargados, &cantidad_avisos_validos, categorias);
    imprime(avisos_validos, cantidad_avisos_validos);

    return 0;
}

void carga_avisos(struct inmueble* todos_los_avisos, int* cantidad_avisos_cargados) {
    int i;
    char codigo[10];

    for (i = 0; i < 1500; i++) {
        system("cls");
        printf("\n - Para finalizar con la carga, simplemente a la hora de ingresar el codigo, escriba '*' - \n");
        printf("\n Aviso nro %i", i + 1);
        printf("\n + Codigo de usuario: ");
        scanf("%s", codigo);

        if (strcmp(codigo, "*") == 0) {
            printf("\n Finalizando carga...");
            Sleep(2000);
            break;
        } else {
            strcpy(todos_los_avisos[i].cod_usuario, codigo);

            printf("\n + Descripcion del aviso: ");
            fflush(stdin);
            fgets(todos_los_avisos[i].descrip_aviso, 300, stdin);
            todos_los_avisos[i].descrip_aviso[strcspn(todos_los_avisos[i].descrip_aviso, "\n")] = '\0';

            printf("\n + Categoria: ");
            scanf("%s", todos_los_avisos[i].categoria);
            printf("\n + Telefono: ");
            scanf("%s", todos_los_avisos[i].telefono);
            printf("\n");

            (*cantidad_avisos_cargados)++;
            system("pause");
        }
    }
}

void carga_categorias(char categorias[6][10]) {
    int i;

    for (i = 0; i < 6; i++) {
        system("cls");
        printf("\n Categoria nro %i", i + 1);
        printf("\n + Escriba el nombre de la categoria: ");
        scanf("%s", categorias[i]);
        printf("\n");
        system("pause");
    }
}

struct inmueble* valida_avisos(struct inmueble* todos_los_avisos, int cantidad_avisos_cargados, int* cantidad_avisos_validos, char categorias[6][10]) {
    static struct inmueble avisos_validos[1500];
    int i, valido_tel_cat, valido_duplicidad;

    for (i = 0; i < cantidad_avisos_cargados; i++) {
        valido_tel_cat = valida_tel_cat(todos_los_avisos[i].telefono, todos_los_avisos[i].categoria, categorias);
        valido_duplicidad = valida_duplicidad_aviso(todos_los_avisos[i].cod_usuario, todos_los_avisos, cantidad_avisos_cargados);

        if (valido_tel_cat && valido_duplicidad) {
            strcpy(avisos_validos[*cantidad_avisos_validos].cod_usuario, todos_los_avisos[i].cod_usuario);
            strcpy(avisos_validos[*cantidad_avisos_validos].descrip_aviso, todos_los_avisos[i].descrip_aviso);
            strcpy(avisos_validos[*cantidad_avisos_validos].categoria, todos_los_avisos[i].categoria);
            strcpy(avisos_validos[*cantidad_avisos_validos].telefono, todos_los_avisos[i].telefono);
            (*cantidad_avisos_validos)++;
        }
    }

    return avisos_validos;
}

int valida_tel_cat(char* telefono, char* categoria, char categorias[6][10]) {
    int long_tel = strlen(telefono);
    int contador_digitos = 0;
    int categoria_encontrada = 0;

    for (int i = 0; i < long_tel; i++) {
        if (isdigit(telefono[i])) {
            contador_digitos++;
        } else {
            break;
        }
    }

    for (int i = 0; i < 6; i++) {
        if (strcmp(categoria, categorias[i]) == 0) {
            categoria_encontrada = 1;
            break;
        }
    }

    return (categoria_encontrada && contador_digitos == long_tel);
}

int valida_duplicidad_aviso(char* cod_usu, struct inmueble* todos_los_avisos, int cantidad_avisos_cargados) {
    int usuario_duplicado = 0;

    for (int i = 0; i < cantidad_avisos_cargados; i++) {
        if (strcmp(cod_usu, todos_los_avisos[i].cod_usuario) == 0) {
            usuario_duplicado++;
        }
    }

    return (usuario_duplicado == 1);
}

void imprime(struct inmueble* avisos_validos, int cantidad_avisos_validos) {
    printf("\n - LISTADO DE TODOS LOS AVISOS VALIDOS -");
    printf("\n =======================================\n");

    for (int i = 0; i < cantidad_avisos_validos; i++) {
        printf("\n - Codigo de usuario: %s", avisos_validos[i].cod_usuario);
        printf("\n - Descripcion del aviso: %s", avisos_validos[i].descrip_aviso);
        printf("\n - Categoria: %s", avisos_validos[i].categoria);
        printf("\n - Telefono: %s", avisos_validos[i].telefono);
        printf("\n ------------------------------------------------------------ \n");
    }
}

