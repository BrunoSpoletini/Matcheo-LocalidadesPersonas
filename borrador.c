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
		case 2:
			return 'M';
		case 3:
			return 'A';
		case 4:
			return 'N';
	}
}

int main(){
	long long n;
	scanf("%lld", &n);

	leerLocalidades() // a medida que lee el archivo de localidades, las guarda en una lista de cadenas (listaLocalidades (array))
	leerPersonas() // 


	return 0;
}
