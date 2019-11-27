#include <stdio.h>
#include <stdlib.h>

void visita(int *M, int n, int ind, char *cor, int *cont, int *tdes, int *tfin){
	
	*(cor+ind) = 'c';
	*cont = *cont + 1;
	*(tdes+ind) = *cont;
	for(int i=0; i<n; i++){
		
		if((*(M + n*ind + i)) == 1){
		
			if((*(cor+i)) == 'b') visita(M, n, i, cor, cont, tdes, tfin);
		
		}
		
	}
	
	*(cor+ind) = 'p';
	*cont = *cont + 1;
	*(tfin+ind) = *cont;
	
}

void buscaProfundidade(int *M, int n, int raiz){
	
	char cor[n];
	int tdes[n];
	int tfin[n];
	int cont = 0;
	for(int i=0; i<n; i++){
		cor[i] = 'b';
	}
	visita(M, n, raiz, cor, &cont, tdes, tfin);
	for(int i=0; i<n; i++){
		if(cor[i] == 'b') visita(M, n, i, cor, &cont, tdes, tfin);
	}
	for(int i=0; i<n; i++){
		
		printf("%c   %d   %d\n",cor[i], tdes[i], tfin[i]);
		
	}
	
}

int main(void){
	
	int grafos[10][10] = {
	{0, 0, 1, 1, 0, 0, 1, 0, 0, 0}, 
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, 
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 1, 1, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, 
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, 
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0}};
	buscaProfundidade(*grafos, 10, 0);
	return 0;
	
}
