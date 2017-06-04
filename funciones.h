#include "estructuras.h"

#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
/*
 * Funcion existFile
 * Funcion que verifica si un archivo existe
 * @param char* filename, nombre del archivo
 * @return entero 1 en caso de que si exista y 0 en caso contrario
*/
int existsFile(char* filename) ;

/*
 * Funcion loadValues
 * Funcion que carga los valores entregados desde un archivo de entrada
 * @param char* filename,int numberCoins[],int valueCoins[] , nombre del archivo de entrada,arreglo de la cantidad de monedas que se tiene por cada tipo de moneda, arreglo que contiene los valores de cada tipo de moneda.
*/
void loadValues(char* filename,int numberCoins[],int valueCoins[] );

/*
 * Funcion initDeliveredCoins
 * Funcion que inicializa el arreglo de la cantidad de monedas entregadas en un pago.
 * @param int deliveredCoins[], arreglo de la cantidad de monedas que se entregaran por cada tipo de moneda.
*/
void initDeliveredCoins(int deliveredCoins[]);
/*
 * Funcion showChange
 * Funcion que muestra cuales son las cantidades y tipo de moneda que se debe entregar.
 * @param int deliveredCoins[],int valueCoins[] ,arreglo de la cantidad de monedas que se entregaran por cada tipo de moneda, arreglo que contiene los valores de cada tipo de moneda.
*/
void showChange(int deliveredCoins[],int valueCoins[]);

/*
 * Funcion addCash
 * Funcion que suma todo el dinero que se tiene en la caja
 * @param int numberCoins[],int valueCoins[] , arreglo de la cantidad de monedas que se tiene por cada tipo de moneda, arreglo que contiene los valores de cada tipo de moneda.
 * @return devulve la suma del dinero de la caja.
*/
int addCash(int numberCoins[],int valueCoins[]);
/*
 * Funcion calculate
 * Funcion que calcula las monedas minimas que se deben entregar, el algoritmo se raliza con metodo goloso.
 * @param int numberCoins[],int deliveredCoins[],int valueCoins[],int totalToPay,int customerPayment,FILE* outfile,int* payment
   numberCoins: arreglo de la cantidad de monedas que se tiene por cada tipo de moneda.
   deliveredCoins: arreglo de la cantidad de monedas que se entregaran por cada tipo de moneda.
   valueCoins: arreglo que contiene los valores de cada tipo de moneda.
   totalToPay: total que se debe pagar
   customerPayment: dinero pagado por el cliente.
   outfile: nombre del archivo de salida.
   payment: numero de pago, esto es como un contador de todos los pagos que se han realizado.
 * @return devulve 1 en caso de que se pueda dar vuelto. Devuelve 0 en caso de NO poder dar vuelto por que no alcanza el dinero de la caja.
*/
int calculate(int numberCoins[],int deliveredCoins[],int valueCoins[],int totalToPay,int customerPayment,FILE* outfile,int* payment);

void showArray(int array[]);
void greedyDeposit(int numberCoins[],int valueCoins[],int customerPayment);
void greedyChange(int deliveredCoins[],int valueCoins[],int change);
void copyChange(Change lChange, int deliveredCoins[]);
int loadChange(int deliveredCoins[],int change);
void saveChange(int deliveredCoins[],int change);
int validateChange(int numberCoins[],int deliveredCoins[]);
#endif // FUNCIONES_H_INCLUDED
	