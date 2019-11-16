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
    
    char **stringList ,buffer[101000];
	stringList= malloc(sizeof(char*)*n+1);
    for(i=1;i<=max && cantLeidos<n;i++){
        fgets(buffer,10100,fp);
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

    //debugging   Hay que solucionar 
    int contRepetidos=0;

    listRands=malloc(sizeof(int)*n);
    if (listRands == NULL) 
        printf("malloc failed\n");
    srand(time(NULL));
    for(i=0; i<n; i++){
		listRands[i] = (rand()%(max-1))+1;
	}
	qsort(listRands, n, sizeof(int), greaterEqual);
    while(hayRepetidos(listRands, n)){
        contRepetidos++;
        // debbugprintf("%d\n",contRepetidos);
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


int  *eliminarDuplicados(int *list, int *n){
    int i,k=0,ncopy=*n;
    int *buffer=malloc(sizeof(int)*(*n));

    buffer[k]=list[0];
    k++;
    
    for(i=1;i<(ncopy);i++){
        if(list[i]!=list[i-1] && list[i]!=0){
            buffer[k]=list[i];
            k++;
        }
        else{
            (*n)=(*n)-1;
        }
    }
    return buffer;
}


int *listaLocalidades(char **listStrings, int n){
    int i=0, *lista;
	char buffer[6][10100];
	lista = malloc(sizeof(int) * n);
	for(i = 0; i < n; i++){
		sscanf(listStrings[i],"%[^,]  %c  %[^,]  %c  %[^,]  %[^\n]",buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);
        lista[i]=atoi(buffer[4]);
	}
    qsort(lista, n, sizeof(int), greaterEqual);
	return lista;
}

void devolverLocalidad(char *localidad, char **listaLocalidades, int largoLista){
    int i=0;
    char dumm_num[1010], dumm_name[1010];
    for(i=0; i<largoLista; i++){
        sscanf(listaLocalidades[i],"%[^,] %*c %[^\n]", dumm_num, dumm_name);
        if(atoi(localidad) == atoi(dumm_num)){
            strcpy(localidad, dumm_name);
        }
    }
}

void trimSpaces(char *cadena)
{
    int indice = -1,  i = 0;
    while(cadena[i] != '\0'){
        if(cadena[i] != ' ' && cadena[i] != '\n'){
            indice= i;
        }
        i++;
    }
    cadena[indice] = '\0';
}

void writeOutput(FILE *fpOutput, char **arrayPersonas, int largoLista, char **arrayLocalidades, int largoListaLocalidades){ 
    int i=0;
    char buffer[6][1010];

    for(i=0; i<(largoLista); i++){
        sscanf(arrayPersonas[i], "%[^,]  %*c  %[^,]  %*c  %[^,] %*c %[^,] %*c %c %*c %c", buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5]);
        
        //buffer [0] tenemos jnombre
        //bufer[1] apellido
        //buffer[2] es la localidad
        //buffer[3] es edad
        //buffer[4] es gen 
        //buffer[5] gen interes
 
        devolverLocalidad(buffer[2], arrayLocalidades, largoListaLocalidades);
        //printf("%s\n",buffer[2]);
        trimSpaces(buffer[2]);
        //printf("%s,%s,%s,%s,%c,%c\n", buffer[0],buffer[1],buffer[2],buffer[3],decodeGender(atoi(buffer[4])),decodeInterest(atoi(buffer[5])));
        fprintf(fpOutput, "%s,%s,%s,%s,%c,%c\n", buffer[0],buffer[1],buffer[2],buffer[3],decodeGender(atoi(buffer[4])),decodeInterest(atoi(buffer[5])));
    }



}


//char *devolverLocalidad(){}

void mostrarLista(char **stringList, int n){
    int i,j;
    for(i=0;i<n;i++){
            printf("%d =  %s",i, stringList[i]);  
        }
	}

int main(){
    int i,n ,max , *listRands, *arrayNumsLocalidadesInt, *numeroIngresado, nInicial, *arrayNumsLocalidadesIntSinRep;
	char **arrayPersonas, **arrayLocalidades;
    scanf("%d", &n);
	FILE *fp1,*fp2,*fp3;
 
    //______________Lectura de personas________________
	fp1 = fopen( "personas.txt", "r");
    max = contarLineas(fp1); // Max es la cantidad de lineas en el archivo
    listRands=listRand(n, max);
    rewind(fp1);
    arrayPersonas = leerArchivos(fp1,listRands,n, max);
    //mostrarLista(arrayPersonas,n);// Muestra la lista de personas
    fclose( fp1 );
    
	//______Lista de localidades a leer del archivo localidades.txt____
	arrayNumsLocalidadesInt=listaLocalidades(arrayPersonas,n);

    nInicial=n;
    numeroIngresado=&n;
    arrayNumsLocalidadesIntSinRep=eliminarDuplicados(arrayNumsLocalidadesInt,numeroIngresado);
   // for(i=0;i<n;i++){printf("%d:  %d\n",i, arrayNumsLocalidadesIntSinRep[i]);}


    //__________Lectura de localidades___________
    fp2 = fopen("codigoLocalidades.txt", "r");
    max = contarLineas(fp2);
    rewind(fp2);
    arrayLocalidades=leerArchivos(fp2, arrayNumsLocalidadesIntSinRep, n, max);
    fclose(fp2);

   

    //_____________Escritura_____________-
    fp3= fopen("Output.txt", "w+");
    writeOutput(fp3, arrayPersonas, nInicial,arrayLocalidades,n);
    fclose(fp3);


    free(listRands);
    free(arrayPersonas);

    free(arrayNumsLocalidadesInt);
    free(arrayNumsLocalidadesIntSinRep);
    free(arrayLocalidades);
	return 0;
}
