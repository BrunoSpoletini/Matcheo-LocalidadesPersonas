/*/
Trabajo práctico 2.
* Bruno Spoletini y Catalina Silvestri
/*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


char decodeGender(int x){ // decodeGender toma un entero (1 o 2), devuelve 'M' si el entero es 1 o 'F' en caso contrario.
	if(x == 1){
		return 'M';
	}else{
		return 'F';
	}
}

char decodeInterest(int x){ //decodeInterest toma un numero en el rango [[1,4]]. Retorna el caracter asociado a cada uno de estos enteros acorde a la consigna.
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

// leerArchivos toma un puntero a un archivo, una lista de enteros (las líneas a leer del archivo), 
// la cantidad de líneas a leer y la cantidad de líneas que hay en el archivo a leer.
// Devuelve una lista de cadenas cuyos elementos son las líneas del archivo leído.
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

// greaterEqual es una función de comparación entre dos enteros, 
// que retorna un entero mayor o igual a 0 si a<=b, o un entero negativo si a > b.
int greaterEqual(const void *a, const void *b){
   return ( *(int*)a - *(int*)b );
}

// hayRepetidos toma una lista de enteros su largo
// devuelve 1 si hay números repetidos en ella y 0 en caso contrario.
int hayRepetidos(int *list, int n){
    int i, flag =0;
    for(i=0; i<n-1; i++){
        if(list[i] == list[i+1])
            flag = 1;
    }
    return flag;
}

// listRand toma el número de usuarios que se extrajeron del archivo de personas y la cantidad de líneas del mismo. 
// Devuelve una lista ordenada de enteros distintos generados aleatoriamente. 
int *listRand(int n, int max){
    int i, *listRands;
    listRands=malloc(sizeof(int)*n);
    srand(time(NULL));
    if(n <= max/2){ // Se genera una lista de líneas a leer
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
    }else{ //Primero se genera una lista de líneas a "ignorar".
        int listNoLeer[max-n],contRands=0,j=0;
        for(i=0; i<(max - n); i++){
            listNoLeer[i]= (rand()%(max-1))+1;
        }
        qsort(listNoLeer, max-n, sizeof(int), greaterEqual);
        while(hayRepetidos(listNoLeer, max-n)){
            for(i=0; i<max-n; i++){
                if(listNoLeer[i] == listNoLeer[i+1]){
                    listNoLeer[i] = (rand()%(max-1))+1;
                }
            }
            qsort(listNoLeer, max-n, sizeof(int), greaterEqual);
        }
        for(i=1; i<=max; i++){
            if(listNoLeer[j]==i){
                j++;
            }
            else{ // Finalmente, listRands contiene las líneas del archivo que deberán leerse.
                listRands[contRands]=i;
                contRands++;
            } 
        }
    }
    return listRands;
}

// contarLineas toma un puntero a un archivo
// Devuelve la cantidad de líneas que tiene ese archivo.
int contarLineas(FILE *fp){
  int count = 0;
  char buf[1010];
  while(fgets(buf,sizeof(buf), fp) != NULL){
    count++;
  }
  return count;
}

// eliminarDuplicados toma una lista de enteros y su longitud.
// Modifica dicha lista para que no haya elementos duplicado, retorna la lista modificada.
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

// listaLocaliades toma la lista de cadenas de información de los usuarios seleccionados y el largo de dicha lista.
// Devuelve una lista con los códigos de las localidades de los usuarios seleccionados. 
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

// trimSpaces toma una cadena con espacios al final.
// Devuelve la misma cadena sin los espacios "extra".
void trimSpaces(char *cadena){
    int indice = -1,  i = 0;
    while(cadena[i] != '\0'){
        if(cadena[i] != ' ' && cadena[i] != '\n'){
            indice= i;
        }
        i++;
    }
    cadena[indice+1] = '\0';
}

// mapLocalidades toma una lista de cadenas de la forma "codigo, localidad    ", la cantidad de usuarios seleccionados y la cantidad total de localidades (max).
// devuelve un array de tamaño max, donde el índice del array es el código de la localidad y el array en dicho índice contiene la localidad asociada a ese código.
char **mapLocalidades(char **localidadesSinParsear, int n, int max){ 
    int i=0;
    char **localidadesParseadas, buffer_num[10], buffer_name[10000];
    localidadesParseadas = malloc(sizeof(char*)*(max+1));

    for(i=0; i<n;i++){
        sscanf(localidadesSinParsear[i],"%[^,] %*c %[^\n]", buffer_num, buffer_name);
        trimSpaces(buffer_name);
        localidadesParseadas[atoi(buffer_num)] =  malloc(((strlen(buffer_name)+1)*sizeof(char)));
        strcpy(localidadesParseadas[atoi(buffer_num)], buffer_name);
    }
    return localidadesParseadas;
}

// writeOutput toma un puntero a un archivo, el arreglo que contiene la información de cada usuario,
// el largo de dicho arreglo y el arreglo de localidades retornado por mapLocalidades.
// Escribe la información de cada usuario en el archivo "Output.txt".
void writeOutput(FILE *fpOutput, char **arrayPersonas, int largoLista, char **localidadesParseadas){ 
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
 
        strcpy(buffer[2], localidadesParseadas[atoi(buffer[2])]);
        fprintf(fpOutput, "%s,%s,%s,%s,%c,%c\n", buffer[0],buffer[1],buffer[2],buffer[3],decodeGender(atoi(buffer[4])),decodeInterest(atoi(buffer[5])));
    }
}



int main(){
    int n ,max , *listRands, *arrayNumsLocalidadesInt, *numeroIngresado, nInicial, *arrayNumsLocalidadesIntSinRep;
	char **arrayPersonas, **arrayLocalidades,**localidadesParseadas;
    char f_personas[1010], f_localidades[1010];
    
    printf("Ingrese el nombre del archivo que contiene la informacion de los usuarios, con su extension correspondiente\n");
    scanf("%s", f_personas);
    FILE *fp;
 
    //______________Lectura de personas________________
    
	fp = fopen( f_personas, "r");
	while(fp == NULL){
        printf("La apertura del archivo ha fallado, por favor ingrese correctamente el nombre del archivo que desea abrir, con su extension correspondiente \n");
		scanf("%s", f_personas);
		fp = fopen( f_personas, "r");
    }
    printf("Ingrese el numero de usuarios que quiere extraer del archivo\n");
    scanf("%d", &n);
    max = contarLineas(fp); // Max es la cantidad de lineas en el archivo
    while(n > max){
        printf("Este numero es demasiado grande, por favor seleccione otro\n");
        scanf("%d", &n);
    }
    listRands=listRand(n, max);
    rewind(fp);
    arrayPersonas = leerArchivos(fp,listRands,n, max);
    fclose(fp);
    
	//______Lista de localidades a leer del archivo localidades.txt____
	arrayNumsLocalidadesInt=listaLocalidades(arrayPersonas,n);

    nInicial=n;
    numeroIngresado=&n;
    arrayNumsLocalidadesIntSinRep=eliminarDuplicados(arrayNumsLocalidadesInt,numeroIngresado);


    //__________Lectura de localidades___________
    printf("Ingrese el nombre del archivo que contiene las localidades, con su extension correspondiente\n");
    scanf("%s", f_localidades);
    fp = fopen(f_localidades, "r");
	while(fp == NULL){
        printf("La apertura del archivo ha fallado, por favor ingrese correctamente el nombre del archivo que desea abrir, con su extension correspondiente \n");
		scanf("%s", f_localidades);
		fp = fopen(f_localidades, "r");
    }
    max = contarLineas(fp);
    rewind(fp);
    arrayLocalidades=leerArchivos(fp, arrayNumsLocalidadesIntSinRep, n, max);
    
    fclose(fp);
    localidadesParseadas=mapLocalidades(arrayLocalidades,n,max);
    
   

    //_____________Escritura_____________-
    fp= fopen("Output.txt", "w+");
    writeOutput(fp, arrayPersonas, nInicial,localidadesParseadas);
    fclose(fp);


    free(listRands);
    free(arrayPersonas);
    free(arrayNumsLocalidadesInt);
    free(arrayNumsLocalidadesIntSinRep);
    free(arrayLocalidades);    
    free(localidadesParseadas);

	return 0;
}
