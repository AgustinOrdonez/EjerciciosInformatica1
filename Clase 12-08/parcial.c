#include <stdio.h>

#define MAX_INPUT_SIZE 11
#define CUIT_SIZE 14

int cuit(char ,char * ,char * );
int isNumber(char);
int validar_tipo(char);
int validar_dni(char *);
int getNumberFromChar(char);
char getCharFromInt(int);

int main(int argc, char* argv[]){
	//printf("%d\n",cuit('j',"asdad","sdfsdf"));
	//printf("%d\n",validar_tipo('M'));
	//printf("validar:%d\n",validar_dni("12345678"));
	char cuitS[CUIT_SIZE];
	int errCode;
	if(argc==3){
		errCode=cuit(*argv[1],argv[2],cuitS);
	
		if(!errCode){
			printf("==CUIT==\n");
			printf("%s\n",cuitS);
		}
		else{
			printf("==ERROR==\n");
			switch(errCode){
				case 1:
					printf("El tipo de persona jurídica no es válido, valores posibles M o F\n");
					break;
				case 2:
					printf("El DNI no es válido, únicamente tiene que tener 8 números\n");
					break;
				case 3:
					printf("Ni el tipo de persona jurídica  ni el DNI son válidos, valores posibles M o F\n");
					break;
			}
		}
	}
	else{
		printf("Cantidad de agumentos inválida\n");
	}

	return errCode;
}

/**Generates cuit based on given algorithm*/
int cuit(char t,char *dni, char *cuit){
	int errCode=0;
	int i;
	int j;
	int sumaY;
	int multip;
	float decY;
	int y;

	if(validar_tipo(t)){
		*cuit='2';
		i=1;
		switch (t){
			case 'M':
				//*(cuit)='2';
				*(cuit+i)='0';
				break;
			case 'F':
				//*(cuit)='2';
				*(cuit+i)='7';
				break;
		}
		i++;
		*(cuit+i)='-';
		i++;
	}
	else{
		errCode=1;
	}


	if(validar_dni(dni)){
		while(*dni){
			*(cuit+i)=*dni;
			dni++;
			i++;
		}
	}
	else if(errCode==1){
		errCode=3;
	}
	else{
		errCode=2;
	}
	if(!errCode){
		sumaY=0;
		multip=5;
		//printf("i%d\n",i);
		for(j=0;j<i;j++){
			//printf("j %d\n",j);
			if(isNumber(*(cuit+j))){
				//printf("numeroActual %c: numero mul %d: numero transformado %d\n",*(cuit+j),multip,getNumberFromChar(*(cuit+j)));
				sumaY+=multip*getNumberFromChar(*(cuit+j));
				//printf("numero:%d: sumasParciales%d\n",multip*getNumberFromChar(*cuit+j),sumaY);
				multip--;
				if(multip<2){
					multip=7;
				}
			}
		}
		//printf("sumaY:%d\n",sumaY);
		decY=sumaY/11.0F;
		//printf("decY %.2f\n",decY);
		//printf("(int) %.2f\n ", (decY-(int)decY)*10 );
		y= (int)11-(int)((decY-(int)decY)*10);
		*(cuit+i)='-';
		//printf("numeroY:%d\n", y);
		i++;
		if(y>9){/**Si el valor del algorítmo es superior a 9 tomo 0*/
			y=0;
		}
		*(cuit+i)=getCharFromInt(y);
		*(cuit+i+1)=0;
	}
	return errCode;
}

/**Returns 1 if type is valid, 0 if it is not*/
int isNumber(char chr){
	int isNumber=1;
		if(!(chr>='0'&&chr<='9')){
			isNumber=0;
		}
	return isNumber;
}

/**Returns 1 if type is valid, 0 if it is not */
int validar_tipo(char type){
	int isValid=1;
	if(type!='M'&&type!='F'){
		isValid=0;
	}
	return isValid;
}

/**Returns 1 if dni is valid, 0 if it is not. It asumes dni is a string*/
int validar_dni(char *dni){
	int dniChars=0;
	int isValid=1;

	while(*dni){
		if(!isNumber(*dni)){
			isValid=0;
		}
		dni++;
		dniChars++;
	}
	if(dniChars!=8){
		isValid=0;
	}
	
	return isValid;
}


/**Returns -1 if it is not a number*/
int getNumberFromChar(char chr){
	int number=-1;
	//printf("NUMERO: %d\n",chr);
	if(isNumber(chr)){
		number=chr-'0';
	}
	//printf("NUM:%d \n",number);

	return number;
}

/**Returns -1 if it is not a number*/
char getCharFromInt(int integer){
	int chr=-1;
	if(integer>=0&&integer<=9){
		chr=integer+'0';
	}
	return chr;
}