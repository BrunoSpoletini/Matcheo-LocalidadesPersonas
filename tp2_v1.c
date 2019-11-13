//        Diseño de datos
/*/
Leer n lineas random del archivo de personas, eliminando los que ya leimos para evitar los repetidos.
Leer el archivo de localidades y pasarlo a una lista de strings.
Parsear el archivo de localidades. (sacarle espacios y todo lo q esta antes de la coma)
En la lista de personas, cambiar la codificascion de los generos.
/*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>



char decodeGender(int x){
	if(x == 1){
		return 'M';
	}else{
		return 'F';
	}
}

char decodeInterest(int x){
    switch(x){
        case 1:
            return 'F';
            break;
        case 2:
            return 'M';
            break;
        case 3:
            return 'A';
            break;
        case 4:
            return 'N';
            break;
        default:
            return 'E';
    }
}


typedef struct {
	char nombre[1010];
	char apellido[1010];
	char localidad[1010];
	int edad;
	int genero;
	int generoInteres;
} persona;



int busquedaBinaria(long long list[], long long elemento, long long n){
    long long mid, top=n, low=0;
    mid=top/2;
    int flag=0;
    while (top>=low && (!flag)){
        if(elemento==mid){
            flag=1;
        }
        if(elemento<mid){
            top=mid-1;
        }else{
            low=mid+1;
        }
        mid=low + (top-low)/2;
    }
    return flag;
}



int hayRepetidos(long long list[], long long n){
    int i, flag =0;
    for(i=0; i<n-1; i++){
        if(list[i] == list[i+1])
            flag =1;
    }
    return flag; // devuelve 1 si hay repetidos, 0 si no hay repetidos
}

void setRepetidos(long long list[], long long n){
    int i, buff[n];
    memset(buff, 0, sizeof(buff)); // setea el buffer para contener solo 0s
    for(i = 0; i<n; i++){
        if(list[i] == list[i+1]){
            buff[i+1] = -1;
        }
    }
	for(i=0; i<n; i++){
		if(buff[i] == -1){
			list[i] = -1;
		}
	}
	// setea todos los numeros repetidos menos uno en -1
}

int greaterEqual(const void *a, const void *b){
   return ( *(int*)a - *(int*)b );
}


void listRand(long long *list, long long n, long long max){
    int i;
    srand(time(NULL)); 
    for(i=0; i<n; i++){
		list[i] = (rand() % (max)) + 1;
	}
	qsort(list, n, sizeof(long long), greaterEqual); // sortea la lista inicial de randoms (puede tener repetidos)
    while(hayRepetidos(list, n)){
        setRepetidos(list, n);
        for(i=0; i<n; i++){
            if(list[i] == -1){
                list[i] = rand()% 1 + max;
            }
        }
        qsort(list, n, sizeof(long long), greaterEqual);
        // mientras haya repetidos, se setean los repetidos menos uno en -1
        // luego se rellena esas posiciones con nuevos enteros random
        // se vuelve a sortear la lista y se repite el procedimiento en caso
        // que siga habiendo elementos repetidos
    }
}





/*
void leerArchivos(FILE *fp){
    char c;
    c = fgetc(fp);
    while( c != EOF){

    }



}*/


int contarLineas(FILE *fp){
    long long contador = 0;
    char c;
    for(c = getc(fp); c != EOF; c = getc(fp)){
        if(c == '\n'){
            contador ++;
        }
    }
    return contador;
}

int main(){
	// este main puede contener basura
	long long n, i, max;
	scanf("%lld", &n);
	long long list[n];
	for(i=0; i<n; i++){
		scanf("%lld", &list[i]);
	}
	max = 40;
	listRand(list, n, max);
	for(i=0;i<n;i++){
        printf("%lld\n",list[i]);
    }
	
	
	return 0;
}

