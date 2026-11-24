#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int nivel;
    char sector[50];
    char nombreTanque[50];
} tanque;

void CambiarDato(tanque *p_tanques, int c_tanques) {
    int b, n_tanque, n_nivel;
    char n_nombre[50], n_seccion[50];

    printf("De que tanque (1 a %d)?\n", c_tanques);
    scanf("%d", &n_tanque);
    while (getchar() != '\n');
    n_tanque--;

    if (n_tanque < 0 || n_tanque >= c_tanques) {
        printf("Indice de tanque invalido.\n");
        return;
    }

    printf("¿Que dato quiere cambiar? 1-Nombre\n 2-Seccion\n 3-Nivel\n");
    scanf("%d", &b);
    while (getchar() != '\n');

    switch (b) {
        case 1:
            printf("Ingrese nuevo nombre\n");
            scanf("%49s", n_nombre);
            while (getchar() != '\n');
            strcpy(p_tanques[n_tanque].nombreTanque, n_nombre);
            break;
        case 2:
            printf("Ingrese nueva seccion\n");
            scanf("%49s", n_seccion);
            while (getchar() != '\n');
            strcpy(p_tanques[n_tanque].sector, n_seccion);
            break;
        case 3:
            do {
                printf("Ingrese nuevo nivel [1;100]\n");
                scanf("%d", &n_nivel);
                while (getchar() != '\n');
                if (n_nivel > 100 || n_nivel < 1) {
                    printf("El valor ingresado tiene que estar entre [1;100], vuelva a intentarlo\n");
                }
            } while (n_nivel > 100 || n_nivel < 1);
            p_tanques[n_tanque].nivel = n_nivel;
            break;
        default:
            printf("Opcion invalida.\n");
            break;
    }
}

void Encontrar2Menor(tanque *p_tanques, int c_tanques) {
    if (c_tanques <= 0) {
        printf("No hay tanques cargados.\n");
        return;
    }

    if (c_tanques == 1) {
        printf("Solo hay 1 tanque cargado:\n");
        printf("1) Sector: %s | Nombre: %s | Nivel: %d%%\n",
               p_tanques[0].sector, p_tanques[0].nombreTanque, p_tanques[0].nivel);
        return;
    }

    int idx1 = 0;
    int idx2 = 1;
    if (p_tanques[idx2].nivel < p_tanques[idx1].nivel) {
        int temp = idx1;
        idx1 = idx2;
        idx2 = temp;
    }

    for (int i = 2; i < c_tanques; i++) {
        if (p_tanques[i].nivel < p_tanques[idx1].nivel) {
            idx2 = idx1;
            idx1 = i;
        } else if (p_tanques[i].nivel < p_tanques[idx2].nivel) {
            idx2 = i;
        }
    }

    printf("Los dos tanques con menor nivel de agua son:\n");
    printf("1) Sector: %s | Nombre: %s | Nivel: %d%%\n",
           p_tanques[idx1].sector, p_tanques[idx1].nombreTanque, p_tanques[idx1].nivel);
    printf("2) Sector: %s | Nombre: %s | Nivel: %d%%\n",
           p_tanques[idx2].sector, p_tanques[idx2].nombreTanque, p_tanques[idx2].nivel);
}

int main() {
    int c_tanques, a;
    tanque *p_tanques;

    printf("Ingrese la cantidad de tanques que va a cargar:\n");
    scanf("%d", &c_tanques);
    while (getchar() != '\n');

    p_tanques = (tanque *)malloc((size_t)c_tanques * sizeof(tanque));
    if (p_tanques == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    for (int i = 0; i < c_tanques; i++) {
        printf("Ingrese el nombre del tanque %d:\n", i + 1);
        scanf("%49s", p_tanques[i].nombreTanque);
        while (getchar() != '\n');

        printf("Ingrese el sector donde se encuentra el tanque %d:\n", i + 1);
        scanf("%49s", p_tanques[i].sector);
        while (getchar() != '\n');

        do {
            printf("Ingrese el porcentaje de agua del tanque [1;100]:\n");
            scanf("%d", &p_tanques[i].nivel);
            while (getchar() != '\n');
            if (p_tanques[i].nivel > 100 || p_tanques[i].nivel < 1) {
                printf("El valor ingresado tiene que estar entre [1;100], vuelva a intentarlo\n");
            }
        } while (p_tanques[i].nivel > 100 || p_tanques[i].nivel < 1);
    }

    printf("Ingrese la opcion que quiere realizar:\n1-Cargar un nuevo dato de algun tanque\n2-Ver los dos tanques con menor nivel de agua\n3-Ver todos los tanques\n");
    scanf("%d", &a);
    while (getchar() != '\n');

    switch (a) {
        case 1:
            CambiarDato(p_tanques, c_tanques);
            break;
        case 2:
            Encontrar2Menor(p_tanques, c_tanques);
            break;
        case 3:
            for (int i = 0; i < c_tanques; i++) {
                printf("%d) Sector: %s | Nombre: %s | Nivel: %d%%\n",
                       i + 1, p_tanques[i].sector, p_tanques[i].nombreTanque, p_tanques[i].nivel);
            }
            break;
        default:
            printf("Numero incorrecto\n");
            break;
    }

    free(p_tanques);
    return 0;
}
