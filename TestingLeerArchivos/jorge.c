
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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
    
    long long list[6]={1,2,3,4,5,10}, max;




   
    
    
    rewind(fp);
	

	

    


    return 0;
}
