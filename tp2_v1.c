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


typedef struct {
	char nombre[1010];
	char apellido[1010];
	char localidad[1010];
	char edad[1010];
	char genero[10];
	char generoInteres[10];
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
            linea++;
            if(flag){
                stringList[j][k-1]='\0';
                printf("Linea: %d\n",linea-1);
                j++;
                flag=0;
                k=0;
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

char **leerLocalidades(FILE *fp, int max){
    //          -- Hay que hacer que la funcion lea el archivo mientras va 
    //          pasando los datos, sin tener que llamar a la funcion contarLineas--
    char c, **stringList;
	int i=0, j=0,linea=0,indice=0;
	stringList= malloc(sizeof(char*)*max);
	for(i=0;i<max;i++){
        stringList[i]=malloc(sizeof(char)*1010);
    }
    for(c = fgetc(fp); c != EOF; c = fgetc(fp)){
        if(!(c>47 && c<58) && c!=','){
            stringList[indice][j]=c;
            j++;
            if(c == '\n'){
                stringList[indice][j-1]='\0';
                j=0;
                indice++;
            }
            if(c==' ' && stringList[indice][j-2]==' '){
                stringList[indice][j-1]='\0';
                i++;
            }
        }
        }
    return stringList;

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

persona *transformarEnEstructura(char **stringList, int n){
    persona *list;
    list=malloc(sizeof(persona)*n);

    list[0].nombre[0]='c';

    int i,j,buff=0,contcomas=0;
    for(i=0;i<n;i++){
        for(j=0; stringList[i][j]!='\0'; j++){
            if(stringList[i][j]==','){
                buff=0;
                contcomas++;
            }else{
                switch(contcomas){
                case 0:
                    list[i].nombre[buff]=stringList[i][j];
                    buff++;
                    break;
                case 1:
                    list[i].apellido[buff]=stringList[i][j];
                    buff++;
                    break;
                case 2:
                    //list[i].localidad[buff]=stringList[i][j];  // COMPLETAR                     buff++;
                    break;
                case 3:
                    list[i].edad[buff]=stringList[i][j];
                    buff++;
                    break;
                case 4:
                    list[i].genero[0]=decodeGender(stringList[i][j]);
                    break;
                default:
                    list[i].generoInteres[0]=decodeInterest(stringList[i][j]);
            }
            }
        }


    }

    return list;
}

int main(){
    int i ,j ,n ,max , *listRands;
	char **arrayPersonas, **arrayLocalidades;
    struct persona *listaStructPersonas;
    scanf("%d", &n);
	FILE *fp;
 
    //>Lectura de personas<
	fp = fopen( "personas.txt", "r");
    max = contarLineas(fp); // Max es la cantidad de lineas en el archivo
    listRands=listRand(n, max);
    for(i=0;i<n;i++) {printf("%d\n",listRands[i]);}
    rewind(fp);
    arrayPersonas = leerArchivos(fp,listRands,n);
    //mostrarLista(arrayPersonas,n); Muestra la lista de personas
    rewind(fp);
    fclose( fp );

    //>Pasaje de lista de strings a lista de estructuras
    //listaStructPersonas=transformarEnEstructura(arrayPersonas, n);


    //>Lectura de localidades<
	fp = fopen("codigoLocalidades.txt", "r");
    
    max = contarLineas(fp);
    rewind(fp);
    arrayLocalidades=leerLocalidades(fp, max);
    //mostrarLista(arrayLocalidades,max); Muestra la lista de ciudades
    fclose( fp );



    

    free(listRands);
    free(arrayPersonas);
    free(listaStructPersonas);

	return 0;
}

