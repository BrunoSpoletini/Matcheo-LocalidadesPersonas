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


typedef struct {
	char nombre[1010];
	char apellido[1010];
	char localidad[1010];
	int edad;
	int genero;
	int generoInteres;
} persona;


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

char **leerArchivos(FILE *fp, int *list, int n){
    char c, **stringList;
	int linea = 1, i,k=0,j=0,flag=0;
	stringList= malloc(sizeof(char*)*n);
	for(i=0;i<n;i++){
        stringList[i]=malloc(sizeof(char)*1010);
	} //Esto hace una matriz de punteros, necesaria para poder devolver el array de chars sin que se pierda
    c = fgetc(fp);
    for(i=0; c != EOF && j<n; i++){

        if(list[j]==linea){
            stringList[j][k]=c;
            k++;
            flag=1;
        }
        if(c =='\n'){
            if(flag){
            stringList[j][k]='\0';
            printf("Linea: %d\n",linea);
            j++;
            flag=0;
            k=0;
            }else{
                linea++;
            }
        }
        c = fgetc(fp);
    }
    return stringList;
}

int greaterEqual(const void *a, const void *b){
   return ( *(int*)a - *(int*)b );
}

int hayRepetidos(int *list, int n){
    int i, flag =0;
    for(i=0; i<n-1; i++){
        if(list[i] == list[i+1])
            flag = 1;
    }
    return flag; // devuelve 1 si hay repetidos, 0 si no hay repetidos
}

int *listRand(int n, int max){
    int i, *listRands;
    listRands=malloc(sizeof(int)*n);
    srand(time(NULL));
    for(i=0; i<n; i++){
		listRands[i] = (rand()%(max-1))+1;
	}
	qsort(listRands, n, sizeof(int), greaterEqual); // sortea la lista inicial de randoms (puede tener repetidos)
    while(hayRepetidos(listRands, n)){
        for(i=0; i<n; i++){
            if(listRands[i] == listRands[i+1]){
                listRands[i] = (rand()%(max-1))+1;
            }
        }
        qsort(listRands, n, sizeof(int), greaterEqual);
    }
    return listRands;
}


int contarLineas(FILE *fp){
    int contador = 0;
    char c;
    for(c = getc(fp); c != EOF; c = getc(fp)){
        if(c == '\n'){
            contador ++;
        }
    }
    return contador;
}

int main(){
    int i ,j ,n ,max , *listRands;
	char **stringList;
    scanf("%d", &n);

	printf("Hola: %d", n);

	FILE *fp;
	fp = fopen( "personas.txt", "r");
    max = contarLineas(fp); // Max es la cantidad de lineas en el archivo

    listRands=listRand(n, max);
    for(i=0;i<n;i++) {
        printf("%d\n",listRands[i]);
    }

    rewind(fp); //Cuando la funcion contarLineas termina, deja el puntero del archivo apuntando al final de este, con esta funcion el puntero vuelve a apuntar al inicio

    stringList = leerArchivos(fp,listRands,n);
    rewind(fp);
    fclose( fp );


	for(i=0;i<n;i++) {
	    for(j=0;stringList[i][j]!='\n';j++){
            printf("%c",stringList[i][j]);
	    }
	    printf("\n");
	    j=0;
	    }

    free(listRands);
    free(stringList);

	return 0;
}

