#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
	int nivel;
	char sector [50];
	char nombreTanque[50];
}tanque;
void CambiarDato (tanque *p_tanques){
	int b, n_tanque, n_nivel;
	char n_nombre[50], n_seccion[50];
	printf("¿Que dato quiere cambiar? 1-Nombre\n 2-Seccion\n 3-Nivel");
	scanf("%d",&b);
	switch (b){
	  case 1:
		  printf("De que tanque?\n");
		  scanf("%d",&n_tanque);
		  printf("Ingrese nuevo nombre\n");
		  scanf("%49s",n_nombre);
		  while(getchar() != '\n');
		  strcpy(p_tanques[n_tanque].nombreTanque,n_nombre);
		break;
	case 2:
		printf("De que tanque?\n");
		scanf("%d",&n_tanque);
		printf("Ingrese nueva seccion\n");
		scanf("%49s",n_seccion);
		while(getchar() != '\n');
		strcpy(p_tanques[n_tanque].sector,n_seccion);
		break;
	case 3:
		printf("De que tanque?\n");
		scanf("%d",&n_tanque);
		printf("Ingrese nuevo nivel\n");
		scanf("%d",&n_nivel);
		p_tanques[n_tanque].nivel=n_nivel;
		break;
	}
}
void Encontrar2Menor(tanque *p_tanques,int &c_tanques ){
	int menor1=0,menor2=0;
	for(int i=0; i<c_tanques;i++){
		if(i==0){
			p_tanques[i].nivel=menor1;
		}
		if (i==1){
			p_tanques[i].nivel=menor2;
		}
		if(i>1){
			if (menor1>p_tanques[i].nivel && menor2>p_tanques[i].nivel){
				if(menor1>p_tanques[i].nivel && menor1>=menor2){
					menor1=p_tanques[i].nivel;
				}
				if(menor2>p_tanques[i].nivel && menor1<menor2){
					menor2=p_tanques[i].nivel;
				}
			}
			if (menor1>p_tanques[i].nivel && menor2<p_tanques[i].nivel){
				menor1=p_tanques[i].nivel;
			}
			if (menor2>p_tanques[i].nivel && menor1<p_tanques[i].nivel){
				menor2=p_tanques[i].nivel;
			}
		}
	}
	printf("Los dos menores valores de nivel de agua son: %d y %d", menor1, menor2);
}
int main() {
	int c_tanques, a;
	tanque *p_tanques;
	printf("Ingrese la cantidad de tanques que va a cargar:\n");
	scanf("%d",&c_tanques);
	p_tanques=((tanque*)malloc (c_tanques * sizeof(tanque)));
	for(int i=0; i<c_tanques;i++){
		printf("Ingrese el nombre del tanque: %d\n",i+1);
		scanf("%49s",p_tanques->nombreTanque);
		while(getchar() != '\n');
		printf("Ingrese el sector donde se encuentra el tanque %d\n",i+1);
		scanf("%49s",p_tanques->sector);
		while(getchar() != '\n');
		do{
			printf("Ingrese el porcentaje de agua del tanque:\n");
			scanf("%d",&p_tanques->nivel);
			if(p_tanques->nivel>100 || p_tanques->nivel<0){
				printf("El valor ingresado tiene que estar entre [0;100], vuelva a intentarlo\n");
			}
		} while(p_tanques->nivel>100 || p_tanques->nivel<0);
	}
	printf("Ingrese la opcion que quiere realizar: 1-Cargar un nuevo dato de algun tanque\n 2-Ver los dos tanques con menor nivel de agua\n 3-Ver todos los tanques");
	scanf("%d",&a);
	switch (a){
		case 1:
			CambiarDato (p_tanques);
		break;
		case 2:
			Encontrar2Menor(p_tanques, c_tanques);
		break;
		default:
			printf("Numero incorrecto");
		}
	return 0;
	}
