//        Diseño de datos
/*/
Leer n lineas random del archivo de personas, eliminando los que ya leimos para evitar los repetidos.
Leer el archivo de localidades y pasarlo a una lista de strings.
Parsear el archivo de localidades. (sacarle espacios y todo lo q esta antes de la coma)
En la lista de personas, cambiar la codificascion de los generos.
/*/


// ___________________________________________
//
//
//     Falta pasar los nombres de los
//     archivos como parametros del main.
//
//___________________________________________________

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
char **leerArchivos(FILE *fp, int *linesToRead, int n, int max){
    int cantLeidos=0, i;
    char **stringList,c ,buffer[1010],buffer2[1010];
	stringList= malloc(sizeof(char*)*n);
    for(i=1;i<=max && cantLeidos<n;i++){
        fgets(buffer,1010,fp);
        if(i==linesToRead[cantLeidos]){
            stringList[cantLeidos]=malloc(sizeof(buffer));
            strcpy(stringList[cantLeidos],buffer);
            cantLeidos++;
        }
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
    return flag;
}

int *listRand(int n, int max){
    int i, *listRands;
    listRands=malloc(sizeof(int)*n);
    srand(time(NULL));
    for(i=0; i<n; i++){
		listRands[i] = (rand()%(max-1))+1;
	}
	qsort(listRands, n, sizeof(int), greaterEqual);
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
  int count = 0;
  char buf[1010];
  while(fgets(buf,sizeof(buf), fp) != NULL){
    count++;
  }
  return count;
}

void mostrarLista(char **stringList, int n){
    int i,j;
    for(i=0;i<n;i++) {
	    for(j=0;stringList[i][j]!='\0';j++){
            printf("%c",stringList[i][j]);
	    }
	    printf("\n");
	    j=0;
	}
}

int *eliminarDuplicados(int *list, int *n){
    int i,k=0;
    int *listSinDuplicados = malloc(sizeof(int) * (*n));
    for(i=0;i<(*n);i++){
        if(!(list[i]==list[i+1]) && list[i]!=0){
            listSinDuplicados[k]=list[i];
            k++;
        }
        else{
            (*n)--;
        }
    }
    return listSinDuplicados;
}

int *listaLocalidades(char **listStrings, int n){
    int i=0, *lista;
	char caracterbuff, buffer[6][300];
	lista = malloc(sizeof(int) * n);

	for(i = 0; i < n; i++){
		sscanf(listStrings[i],"%[^,]  %c  %[^,]  %c  %[^,]  %[^\n]",buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);
        lista[i]=atoi(buffer[4]);
	}
    qsort(lista, n, sizeof(int), greaterEqual);
	return lista;
}

//char *devolverLocalidad(){}

int main(){
    int i,n ,max , *listRands, *arrayNumsLocalidadesInt, *numeroIngresado;
	char **arrayPersonas, **arrayLocalidades;
    scanf("%d", &n);
	FILE *fp;
 
    //______________Lectura de personas________________
	fp = fopen( "personas.txt", "r");
    max = contarLineas(fp); // Max es la cantidad de lineas en el archivo
    listRands=listRand(n, max);
    rewind(fp);
    arrayPersonas = leerArchivos(fp,listRands,n, max);
    //mostrarLista(arrayPersonas,n);// Muestra la lista de personas
    fclose( fp );


    
	//______Lista de localidades a leer del archivo localidades.txt____
	arrayNumsLocalidadesInt=listaLocalidades(arrayPersonas,n);
    numeroIngresado=&n;
    arrayNumsLocalidadesInt=eliminarDuplicados(arrayNumsLocalidadesInt,numeroIngresado);
    //debuggin --> for(i=0;i<n;i++){printf("%d\n",arrayNumsLocalidadesInt[i]);}



    //__________Lectura de localidades___________
	fp = fopen("codigoLocalidades.txt", "r");
    max = contarLineas(fp);
    rewind(fp);
    arrayLocalidades=leerArchivos(fp, arrayNumsLocalidadesInt, n, max);
    //mostrarLista(arrayLocalidades,n);
    fclose(fp);

    free(listRands);
    free(arrayPersonas);
    free(arrayNumsLocalidadesInt);
	return 0;
}
