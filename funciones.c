#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"
#include "estructuras.h"
/*
 * Funcion existsFile
*/
int existsFile(char* filename) 
{
	FILE* f = NULL;
	f = fopen(filename,"r");
	if (f == NULL)
		return 0;
	else {
		fclose(f);
		return 1;
		}
	return 0;
}

/*
 * Funcion loadValues
*/
void loadValues(char* filename,int numberCoins[],int valueCoins[] )
{
	FILE* inputFile;
	inputFile = fopen(filename,"r");
	int quantity;
	int value;
	int index = 0;
	while (!feof(inputFile)){
		fscanf(inputFile,"%d %d\n",&quantity, &value);
		//printf("valores: %3d %4d\n",quantity , value );
		numberCoins[index] = quantity;
		valueCoins[index] = value;
		index += 1;
	}
	fclose(inputFile);
}

/*
 * Funcion initDeliveredCoins
*/
void initDeliveredCoins(int deliveredCoins[])
{
	int i;
	for (i=0;i<11;i++){
		deliveredCoins[i]=0;
	}
}

/*
 * Funcion showChange
*/
void showChange(int deliveredCoins[],int valueCoins[])
{
	int i;
	for (i=0;i<11;i++){
		if (deliveredCoins[i]!=0){
			if(valueCoins[i]>=1000){
				printf("%2d billete(s) de $%d\n",deliveredCoins[i],valueCoins[i] );
			}
			else{
				printf("%2d moneda(s)  de $%d\n",deliveredCoins[i],valueCoins[i] );
			}
		}
	}
}

int addCash(int numberCoins[],int valueCoins[])
{
	int i = 0;
	int total = 0;
	while (i<11){
		total += (numberCoins[i]) * (valueCoins[i]);
		i++;
	}
	return total;
}

/*
 * Funcion calculate
*/
int calculate(int numberCoins[],int deliveredCoins[],int valueCoins[],int totalToPay,int customerPayment,FILE* outfile,int* payment)
{
	initDeliveredCoins(deliveredCoins);
	int change = customerPayment - totalToPay;
	int changeAux = change;
	//Aqui se agrega el efectivo a la caja (el que paga el cliente)
	greedyDeposit(numberCoins,valueCoins,customerPayment);
	

	// Aqui se obitiene lo que se debe entregar al cliente
	// PROGRAMACION DINAMICA
	if (loadChange(deliveredCoins,change))
	{
		//no realiza nada por que si encuentra el vuelto 
		//en el archivo, los valores se cargan inmediatamente
		//printf("Se encontro el valor en el archivo\n");
	}
	else
	{
		greedyChange(deliveredCoins,valueCoins,change);
		saveChange(deliveredCoins,change);
		//printf("No se encontro el valor en el archivo\n");
	}

	


	// Se verifica si el efectivo alcanza para el vuelto
    if(!validateChange(numberCoins,deliveredCoins))
    {
        printf("No existen monedas suficientes\n");
		return 0;
    }
    else
    {
		//Mostrando el dinero que se debe entregar
		printf("Vuelto          : %d\n", change );
		showChange(deliveredCoins,valueCoins);
		//Guardando en el archivo de salida, la suma total que se tiene en la caja.
		int total = addCash(numberCoins,valueCoins);
		fprintf(outfile, "Pago %2d: $%d\n", *payment, total );
		*payment+=1;
		return 1;
	}
}

void showArray(int array[])
{
	int i;
	for (int i = 0; i < 11; ++i)
	{
		printf("array[%d]: %d\n",i, array[i] );
	}
}

void greedyDeposit(int numberCoins[],int valueCoins[],int customerPayment)
{
	int i=0;
	//Aqui se agrega el efectivo a la caja (el que paga el cliente)
	while (i<11){
        while (customerPayment>=valueCoins[i]){
			numberCoins[i]+=1;
			customerPayment -= valueCoins[i];
        }
        i++;
    }
}

void greedyChange(int deliveredCoins[],int valueCoins[],int change)
{
	initDeliveredCoins(deliveredCoins);
	int i=0;
	while (i<11){
        while (change>=valueCoins[i]){
            deliveredCoins[i]+=1;
			change -= valueCoins[i];
			//printf("%d\n",change );
        }
        i++;
    }
}


void copyChange(Change lChange, int deliveredCoins[])
{
	deliveredCoins[0] = atoi(lChange.d1);
	deliveredCoins[1] = atoi(lChange.d2);
	deliveredCoins[2] = atoi(lChange.d3);
	deliveredCoins[3] = atoi(lChange.d4);
	deliveredCoins[4] = atoi(lChange.d5);
	deliveredCoins[5] = atoi(lChange.d6);
	deliveredCoins[6] = atoi(lChange.d7);
	deliveredCoins[7] = atoi(lChange.d8);
	deliveredCoins[8] = atoi(lChange.d9);
	deliveredCoins[9] = atoi(lChange.d10);
	deliveredCoins[10] = atoi(lChange.d11);

}
int loadChange(int deliveredCoins[],int change)
{
	if (change!= 0){
		if (existsFile("file.txt")){

			Change lChange;
			char buffer[150];
			FILE* file = fopen("file.txt","r");
			while (!feof(file)){
				memset(buffer,0,sizeof(buffer));
				fgets(buffer,150,file);
				memcpy(&lChange,buffer,sizeof(Change));
				if (change == atoi(lChange.change)){
					copyChange(lChange,deliveredCoins);
					return 1;
				}
			}
			fclose(file);

		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}

void saveChange(int deliveredCoins[],int change)
{
	//initDeliveredCoins(deliveredCoins);//comentar esto al final
	//showArray(deliveredCoins);
	FILE* file = fopen("file.txt","a");
	Change sChange;
	sChange.f1 = '/';
	sChange.f2 = '/';
	sChange.f3 = '/';
	sChange.f4 = '/';
	sChange.f5 = '/';
	sChange.f6 = '/';
	sChange.f7 = '/';
	sChange.f8 = '/';
	sChange.f9 = '/';
	sChange.f10 = '/';
	sChange.f11 = '/';

	memset(sChange.change,' ',10);
	memset(sChange.d1,' ',10);
	memset(sChange.d2,' ',10);
	memset(sChange.d3,' ',10);
	memset(sChange.d4,' ',10);
	memset(sChange.d5,' ',10);
	memset(sChange.d6,' ',10);
	memset(sChange.d7,' ',10);
	memset(sChange.d8,' ',10);
	memset(sChange.d9,' ',10);
	memset(sChange.d10,' ',10);
	memset(sChange.d11,' ',10);
	//printf("%c\n",sChange.change[0] );
	char aux[11];
	//printf("sizeof: %d\n",sizeof(aux));

	//Change
	memset(aux,0,10);
	sprintf(aux,"%010d",change);
	memcpy(sChange.change,aux,10);
	//printf("change:%s\n", sChange.change);

	//d1->20.000
	memset(aux,0,10);
	sprintf(aux,"%010d",deliveredCoins[0]);
	memcpy(sChange.d1,aux,10);
	//printf("d1: %s\n", sChange.d1);

	//d2->10.000
	memset(aux,0,10);
	sprintf(aux,"%010d",deliveredCoins[1]);
	memcpy(sChange.d2,aux,10);
	//printf("d2: %s\n", sChange.d2);

	//d3->5.000
	memset(aux,0,10);
	sprintf(aux,"%010d",deliveredCoins[2]);
	memcpy(sChange.d3,aux,10);
	//printf("d3: %s\n", sChange.d3);

	//d4->2.000
	memset(aux,0,10);
	sprintf(aux,"%010d",deliveredCoins[3]);
	memcpy(sChange.d4,aux,10);
	//printf("d4: %s\n", sChange.d4);

	//d5->1.000
	memset(aux,0,10);
	sprintf(aux,"%010d",deliveredCoins[4]);
	memcpy(sChange.d5,aux,10);
	//printf("d5: %s\n", sChange.d5);

	//d6->500
	memset(aux,0,10);
	sprintf(aux,"%010d",deliveredCoins[5]);
	memcpy(sChange.d6,aux,10);
	//printf("d6: %s\n", sChange.d6);

	//d7->100
	memset(aux,0,10);
	sprintf(aux,"%010d",deliveredCoins[6]);
	memcpy(sChange.d7,aux,10);
	//printf("d7: %s\n", sChange.d7);

	//d8->50
	memset(aux,0,10);
	sprintf(aux,"%010d",deliveredCoins[7]);
	memcpy(sChange.d8,aux,10);
	//printf("d8: %s\n", sChange.d8);

	//d9->10
	memset(aux,0,10);
	sprintf(aux,"%010d",deliveredCoins[8]);
	memcpy(sChange.d9,aux,10);
	//printf("d9: %s\n", sChange.d9);

	//d10->5
	memset(aux,0,10);
	sprintf(aux,"%010d",deliveredCoins[9]);
	memcpy(sChange.d10,aux,10);
	//printf("d10: %s\n", sChange.d10);

	//d11->1
	memset(aux,0,10);
	sprintf(aux,"%010d",deliveredCoins[10]);
	memcpy(sChange.d11,aux,10);
	//printf("d11: %s\n", sChange.d11);




	char aux2[250];
	memset(aux2,0,sizeof(aux2));
   	memcpy(aux2,&sChange,sizeof(Change));
   	strcat(aux2,"\n");
	fputs(aux2,file);
	fclose(file);
}

int validateChange(int numberCoins[],int deliveredCoins[])
{
	int i;
	for (int i = 0; i < 11; ++i)
	{
		numberCoins[i] = numberCoins[i] - deliveredCoins[i];
		if (numberCoins[i] < 0)
		{ 
			return 0;
		}
	}
	return 1;
}


