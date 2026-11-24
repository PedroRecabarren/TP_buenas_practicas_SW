#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_TEXTO = 50;
const int MAX_LECTURA_CADENA = 49;
const int NIVEL_MINIMO = 1;
const int NIVEL_MAXIMO = 100;

typedef struct {
    int nivel;
    char sector[MAX_TEXTO];
    char nombreTanque[MAX_TEXTO];
} tanque;

/*
 * Limpia el bufer de entrada hasta encontrar un salto de linea o EOF.
 * Parametros: ninguno.
 * Precondicion: entrada estandar disponible.
 */
void LimpiarBufferEntrada() {
    int caracter = 0;
    while ((caracter = getchar()) != '\n' && caracter != EOF) {
        /* Descarta caracteres residuales del bufer */
    }
} // fin LimpiarBufferEntrada

/*
 * Carga los datos de los tanques en el rango [inicio, fin).
 * Parametros: p_tanques (puntero al arreglo dinamico), inicio y fin (indices del rango).
 * Precondicion: p_tanques apunta a memoria valida para al menos 'fin' elementos.
 */
void CargarRangoTanques(tanque *p_tanques, int inicio, int fin) {
    if (p_tanques == NULL || inicio < 0 || fin <= inicio) {
        return;
    }

    for (int i = inicio; i < fin; i++) {
        printf("Ingrese el nombre del tanque %d:\n", i + 1);
        scanf("%49s", p_tanques[i].nombreTanque);
        LimpiarBufferEntrada();

        printf("Ingrese el sector donde se encuentra el tanque %d:\n", i + 1);
        scanf("%49s", p_tanques[i].sector);
        LimpiarBufferEntrada();

        do {
            printf("Ingrese el porcentaje de agua del tanque [%d;%d]:\n", NIVEL_MINIMO, NIVEL_MAXIMO);
            if (scanf("%d", &p_tanques[i].nivel) != 1) {
                p_tanques[i].nivel = NIVEL_MINIMO - 1;
            }
            LimpiarBufferEntrada();

            if (p_tanques[i].nivel > NIVEL_MAXIMO || p_tanques[i].nivel < NIVEL_MINIMO) {
                printf("El valor ingresado tiene que estar entre [%d;%d], vuelva a intentarlo\n",
                       NIVEL_MINIMO, NIVEL_MAXIMO);
            }
        } while (p_tanques[i].nivel > NIVEL_MAXIMO || p_tanques[i].nivel < NIVEL_MINIMO);
    } // fin for carga tanques
} // fin CargarRangoTanques

/*
 * Amplia dinamicamente el arreglo de tanques con realloc y carga los nuevos registros.
 * Parametros: p_tanques (puntero doble al arreglo), c_tanques (puntero a cantidad actual).
 * Precondicion: *p_tanques es NULL o apunta a memoria asignada dinamicamente.
 */
void AgregarTanques(tanque **p_tanques, int *c_tanques) {
    int cantidad_extra = 0;
    int nuevo_total = 0;
    tanque *temp = NULL;

    if (p_tanques == NULL || c_tanques == NULL) {
        printf("Error de punteros en agregar tanques.\n");
        return;
    }

    printf("¿Cuantos tanques nuevos desea agregar?\n");
    if (scanf("%d", &cantidad_extra) != 1) {
        cantidad_extra = 0;
    }
    LimpiarBufferEntrada();

    if (cantidad_extra <= 0) {
        printf("Cantidad invalida. No se agregaron tanques.\n");
        return;
    }

    nuevo_total = *c_tanques + cantidad_extra;
    temp = (tanque *)realloc(*p_tanques, (size_t)nuevo_total * sizeof(tanque));
    if (temp == NULL) {
        printf("Error al reasignar memoria. Se conservan los datos anteriores.\n");
        return;
    }

    *p_tanques = temp;
    CargarRangoTanques(*p_tanques, *c_tanques, nuevo_total);
    *c_tanques = nuevo_total;
    printf("Se agregaron los nuevos tanques. Total actual: %d\n", *c_tanques);
} // fin AgregarTanques

/*
 * Modifica el nombre, sector o nivel de un tanque seleccionado por el usuario.
 * Parametros: p_tanques (puntero al arreglo), c_tanques (cantidad de tanques cargados).
 * Precondicion: c_tanques >= 0; si c_tanques > 0, p_tanques es valido.
 */
void CambiarDato(tanque *p_tanques, int c_tanques) {
    int tipo_dato = 0;
    int indice_tanque = 0;
    int nuevo_nivel = 0;
    char nuevo_nombre[MAX_TEXTO] = "";
    char nueva_seccion[MAX_TEXTO] = "";

    if (p_tanques == NULL || c_tanques <= 0) {
        printf("No hay tanques cargados para modificar.\n");
        return;
    }

    printf("De que tanque (1 a %d)?\n", c_tanques);
    if (scanf("%d", &indice_tanque) != 1) {
        indice_tanque = 0;
    }
    LimpiarBufferEntrada();
    indice_tanque--;

    if (indice_tanque < 0 || indice_tanque >= c_tanques) {
        printf("Indice de tanque invalido.\n");
        return;
    }

    printf("¿Que dato quiere cambiar? 1-Nombre\n 2-Seccion\n 3-Nivel\n");
    if (scanf("%d", &tipo_dato) != 1) {
        tipo_dato = 0;
    }
    LimpiarBufferEntrada();

    switch (tipo_dato) {
        case 1:
            printf("Ingrese nuevo nombre\n");
            scanf("%49s", nuevo_nombre);
            LimpiarBufferEntrada();
            strncpy(p_tanques[indice_tanque].nombreTanque, nuevo_nombre, MAX_LECTURA_CADENA);
            p_tanques[indice_tanque].nombreTanque[MAX_LECTURA_CADENA] = '\0';
            break;
        case 2:
            printf("Ingrese nueva seccion\n");
            scanf("%49s", nueva_seccion);
            LimpiarBufferEntrada();
            strncpy(p_tanques[indice_tanque].sector, nueva_seccion, MAX_LECTURA_CADENA);
            p_tanques[indice_tanque].sector[MAX_LECTURA_CADENA] = '\0';
            break;
        case 3:
            do {
                printf("Ingrese nuevo nivel [%d;%d]\n", NIVEL_MINIMO, NIVEL_MAXIMO);
                if (scanf("%d", &nuevo_nivel) != 1) {
                    nuevo_nivel = NIVEL_MINIMO - 1;
                }
                LimpiarBufferEntrada();

                if (nuevo_nivel > NIVEL_MAXIMO || nuevo_nivel < NIVEL_MINIMO) {
                    printf("El valor ingresado tiene que estar entre [%d;%d], vuelva a intentarlo\n",
                           NIVEL_MINIMO, NIVEL_MAXIMO);
                }
            } while (nuevo_nivel > NIVEL_MAXIMO || nuevo_nivel < NIVEL_MINIMO);
            p_tanques[indice_tanque].nivel = nuevo_nivel;
            break;
        default:
            printf("Opcion invalida.\n");
            break;
    } // fin switch CambiarDato
} // fin CambiarDato

/*
 * Muestra los dos tanques con menor nivel de agua junto con su sector y nombre.
 * Parametros: p_tanques (puntero al arreglo), c_tanques (cantidad de tanques cargados).
 * Precondicion: c_tanques >= 0; si c_tanques > 0, p_tanques es valido.
 */
void Encontrar2Menor(tanque *p_tanques, int c_tanques) {
    int idx1 = 0;
    int idx2 = 1;
    int temp = 0;

    if (p_tanques == NULL || c_tanques <= 0) {
        printf("No hay tanques cargados.\n");
        return;
    }

    if (c_tanques == 1) {
        printf("Solo hay 1 tanque cargado:\n");
        printf("1) Sector: %s | Nombre: %s | Nivel: %d%%\n",
               p_tanques[0].sector, p_tanques[0].nombreTanque, p_tanques[0].nivel);
        return;
    }

    if (p_tanques[idx2].nivel < p_tanques[idx1].nivel) {
        temp = idx1;
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
    } // fin for buscar 2 menores

    printf("Los dos tanques con menor nivel de agua son:\n");
    printf("1) Sector: %s | Nombre: %s | Nivel: %d%%\n",
           p_tanques[idx1].sector, p_tanques[idx1].nombreTanque, p_tanques[idx1].nivel);
    printf("2) Sector: %s | Nombre: %s | Nivel: %d%%\n",
           p_tanques[idx2].sector, p_tanques[idx2].nombreTanque, p_tanques[idx2].nivel);
} // fin Encontrar2Menor

/*
 * Muestra en pantalla todos los tanques cargados.
 * Parametros: p_tanques (puntero al arreglo), c_tanques (cantidad de tanques cargados).
 * Precondicion: c_tanques >= 0; si c_tanques > 0, p_tanques es valido.
 */
void MostrarTodos(tanque *p_tanques, int c_tanques) {
    if (p_tanques == NULL || c_tanques <= 0) {
        printf("No hay tanques cargados.\n");
        return;
    }

    for (int i = 0; i < c_tanques; i++) {
        printf("%d) Sector: %s | Nombre: %s | Nivel: %d%%\n",
               i + 1, p_tanques[i].sector, p_tanques[i].nombreTanque, p_tanques[i].nivel);
    } // fin for mostrar todos
} // fin MostrarTodos

/*
 * Busca un caracter (strchr) o una silaba/subcadena (strstr) en nombre y/o sector.
 * Parametros: p_tanques (puntero al arreglo), c_tanques (cantidad de tanques cargados).
 * Precondicion: c_tanques >= 0; cadenas terminadas en '\0'.
 */
void BuscarEnCadenas(tanque *p_tanques, int c_tanques) {
    int tipo_busqueda = 0;
    int campo = 0;
    int coincidencias = 0;
    char caracter_buscado = '\0';
    char texto_buscado[MAX_TEXTO] = "";

    if (p_tanques == NULL || c_tanques <= 0) {
        printf("No hay tanques cargados para buscar.\n");
        return;
    }

    printf("¿Que desea buscar?\n1 - Un caracter (strchr)\n2 - Una silaba o subcadena (strstr)\n");
    if (scanf("%d", &tipo_busqueda) != 1) {
        tipo_busqueda = 0;
    }
    LimpiarBufferEntrada();

    printf("¿En que campo desea buscar?\n1 - Nombre del tanque\n2 - Sector\n3 - Ambos\n");
    if (scanf("%d", &campo) != 1) {
        campo = 0;
    }
    LimpiarBufferEntrada();

    if (tipo_busqueda == 1) {
        printf("Ingrese el caracter a buscar:\n");
        scanf(" %c", &caracter_buscado);
        LimpiarBufferEntrada();
    } else if (tipo_busqueda == 2) {
        printf("Ingrese la silaba o texto a buscar:\n");
        scanf("%49s", texto_buscado);
        LimpiarBufferEntrada();
    } else {
        printf("Tipo de busqueda invalido.\n");
        return;
    }

    for (int i = 0; i < c_tanques; i++) {
        int coincide_nombre = 0;
        int coincide_sector = 0;

        if (tipo_busqueda == 1) {
            if ((campo == 1 || campo == 3) && strchr(p_tanques[i].nombreTanque, caracter_buscado) != NULL) {
                coincide_nombre = 1;
            }
            if ((campo == 2 || campo == 3) && strchr(p_tanques[i].sector, caracter_buscado) != NULL) {
                coincide_sector = 1;
            }
        } else {
            if ((campo == 1 || campo == 3) && strstr(p_tanques[i].nombreTanque, texto_buscado) != NULL) {
                coincide_nombre = 1;
            }
            if ((campo == 2 || campo == 3) && strstr(p_tanques[i].sector, texto_buscado) != NULL) {
                coincide_sector = 1;
            }
        }

        if (coincide_nombre || coincide_sector) {
            printf("Coincidencia -> Tanque %d | Sector: %s | Nombre: %s | Nivel: %d%%\n",
                   i + 1, p_tanques[i].sector, p_tanques[i].nombreTanque, p_tanques[i].nivel);
            coincidencias++;
        }
    } // fin for recorrer tanques

    if (coincidencias == 0) {
        printf("No se encontraron coincidencias.\n");
    }
} // fin BuscarEnCadenas

/*
 * Punto de entrada del programa de monitoreo de tanques de agua.
 * Parametros: ninguno.
 * Precondicion: entorno de consola estandar disponible.
 */
int main() {
    int c_tanques = 0;
    int opcion = 0;
    tanque *p_tanques = NULL;

    printf("Ingrese la cantidad de tanques que va a cargar:\n");
    if (scanf("%d", &c_tanques) != 1) {
        c_tanques = 0;
    }
    LimpiarBufferEntrada();

    if (c_tanques < 0) {
        c_tanques = 0;
    }

    if (c_tanques > 0) {
        p_tanques = (tanque *)malloc((size_t)c_tanques * sizeof(tanque));
        if (p_tanques == NULL) {
            printf("Error al asignar memoria.\n");
            return 1;
        }
        CargarRangoTanques(p_tanques, 0, c_tanques);
    }

    do {
        printf("\nIngrese la opcion que quiere realizar:\n");
        printf("1 - Modificar un dato de algun tanque\n");
        printf("2 - Ver los dos tanques con menor nivel de agua\n");
        printf("3 - Ver todos los tanques\n");
        printf("4 - Agregar nuevos tanques\n");
        printf("5 - Buscar caracter o silaba en nombre o sector\n");
        printf("0 - Salir\n");
        if (scanf("%d", &opcion) != 1) {
            opcion = -1;
        }
        LimpiarBufferEntrada();

        switch (opcion) {
            case 1:
                CambiarDato(p_tanques, c_tanques);
                break;
            case 2:
                Encontrar2Menor(p_tanques, c_tanques);
                break;
            case 3:
                MostrarTodos(p_tanques, c_tanques);
                break;
            case 4:
                AgregarTanques(&p_tanques, &c_tanques);
                break;
            case 5:
                BuscarEnCadenas(p_tanques, c_tanques);
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Numero incorrecto\n");
                break;
        } // fin switch menu
    } while (opcion != 0); // fin do-while menu

    free(p_tanques);
    p_tanques = NULL;
    return 0;
} // fin main
