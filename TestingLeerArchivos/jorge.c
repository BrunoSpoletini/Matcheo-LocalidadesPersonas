
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char **leerArchivos(FILE *fp, long long list[], long long n){
    char c, **stringList;
	int linea = 0, i,k=0,j=0;
	int flag=0;
	stringList=(malloc(sizeof(char)*n));
	for(i=0;i<n;i++){
        stringList[i]=malloc(sizeof(char)*1010);
	} //Esto hace una matriz de punteros, necesaria para poder devolver el array de chars sin que se pierda
    c = fgetc(fp);
    for(i=0; c != EOF && j<n; i++){
        if(list[j]==linea){
            stringList[j][k]=c;
            //printf("%c",stringList[j][k]);
            k++;
            flag=1;
        }
        if(c == '\n'){
            linea++;
        }
        if(c =='\n' && flag){
            stringList[j][k]='\0';
            j++;
            flag=0;
            k=0;
        }
        c = fgetc(fp);
    }
    return stringList;
}

int contarLineas(FILE *fp){
    long long contador = 0;
    char c;
    for(c = fgetc(fp); c != EOF; c = fgetc(fp)){
        if(c == '\n'){
            contador ++;
        }
    }
    return contador;
}


int main(){
    long long n=6;
    char **stringList;

    long long list[6]={1,2,3,4,5,10}, max;


	FILE *fp;
	fp = fopen( "personas.txt", "r");


    max = contarLineas(fp); // Max es la cantidad de lineas en el archivo

    rewind(fp); //Cuando la funcion contarLineas termina, deja el puntero del archivo apuntando al final de este, con esta funcion el puntero vuelve a apuntar al inicio

    stringList = leerArchivos(fp,list,n);

    rewind(fp);
	fclose( fp );

	int i,j;
	for(i=0;i<n;i++) {
	    for(j=0;stringList[i][j]!='\n';j++){
            printf("%c",stringList[i][j]);
	    }
	    printf("\n");
	    j=0;
	    }

    free(stringList);


    return 0;
}
