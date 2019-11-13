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



int greaterEqual(const void *a, const void *b){
   return ( *(int*)a - *(int*)b );
}

int hayRepetidos(long long list[], long long n){
    int i, flag =0;
    for(i=0; i<n-1; i++){
        if(list[i] == list[i+1])
            flag =1;
    }
    return flag;
}


void setRepetidos(long long list[], long long n){
    int i, buff[n];
    for(i = 0; i<n-1; i++){
        if(list[i] == list[i+1]){
            buff[i+1] = -1;
        }
    }
    if(hayRepetidos(list,n)){
        for(i=0; i<n; i++){
            if(buff[i] == -1){
                list[i] = -1;
            }
        }
    }
}


long long listRand(int n, int max){
    long long list[n], i;
    for(i=0 ;i<n ;i++){
        list[i] = (rand()% 1) + max;
    }
	qsort(list, n, sizeof(long long), greaterEqual);
    while(hayRepetidos(list, n)){
        setRepetidos(list, n);
        for(i=0; i<n; i++){
            if(list[i] == -1){
                list[i] = rand()% 1 + max;
            }
        }
        qsort(list, n, sizeof(long long), greaterEqual);
    }

    return *list;
}





void leerArchivos(FILE *fp, long long list[], long long n){
    char c, stringList[n][10010];
	int linea = 0;
    c = fgetc(fp);
    while( c != EOF){
		if(linea[i]==linea){
			
		}
		if(c == '\n'){
			linea++;
		}
    }
}


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
    long long n;

    scanf("%lld", &n);
    long long list[n], max;
	FILE *fp;
	fp = fopen( "personas.txt", "r");



    max=contarLineas(fp); // Max es la cantidad de lineas en el archivo

    list[0]=listRand(n, max);
    //leerArchivos(list);

	fclose( fp );
	int i;
	for(i=0;i<n;i++){
		printf("%lld\n",list[i]);
	}

	//leerLocalidades() // a medida que lee el archivo de localidades, las guarda en una lista de cadenas (listaLocalidades (array))
	//leerPersonas() //



    return 0;
}
