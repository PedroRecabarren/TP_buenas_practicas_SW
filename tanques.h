#ifndef TANQUES_H
#define TANQUES_H

const int MAX_TEXTO = 50;
const int MAX_LECTURA_CADENA = 49;
const int NIVEL_MINIMO = 1;
const int NIVEL_MAXIMO = 100;

typedef struct {
    int nivel;
    char sector[MAX_TEXTO];
    char nombreTanque[MAX_TEXTO];
} tanque;

void LimpiarBufferEntrada();
void CargarRangoTanques(tanque *p_tanques, int inicio, int fin);
void AgregarTanques(tanque **p_tanques, int *c_tanques);
void CambiarDato(tanque *p_tanques, int c_tanques);
void Encontrar2Menor(tanque *p_tanques, int c_tanques);
void MostrarTodos(tanque *p_tanques, int c_tanques);
void BuscarEnCadenas(tanque *p_tanques, int c_tanques);

#endif /* TANQUES_H */
