#include <stdio.h>
#include <stdlib.h>

void visita(int *M, int n, int ind, char *cor, int *cont, int *tdes, int *tfin, FILE *arq){
	
	*(cor+ind) = 'c';
	fprintf(arq,"Pintando o v�rtice %d de cinza\n",ind);
	*cont = *cont + 1;
	*(tdes+ind) = *cont;
	fprintf(arq,"Tempo de descobrimento do v�rtice %d: %d\n",ind,*cont);
	for(int i=0; i<n; i++){
		
		if((*(M + n*ind + i)) == 1){
		
			if((*(cor+i)) == 'b') {
				
				fprintf(arq,"Visitando o v�rtice %d...\n",i);
				visita(M, n, i, cor, cont, tdes, tfin, arq);
				
			}
		
		}
		
	}
	
	*(cor+ind) = 'p';
	fprintf(arq,"Pintando o v�rtice %d de preto\n",ind);
	*cont = *cont + 1;
	*(tfin+ind) = *cont;
	fprintf(arq,"Tempo de finaliza��o do v�rtice %d: %d\n",ind,*cont);
	
}

void buscaProfundidade(int *M, int n, int raiz){
	
	FILE *arq;
	arq = fopen("buscaProfundidade.txt", "w");
	fprintf(arq,"Realizando a busca em profundidade em um grafo com %d v�rtices, partindo do v�rtice %d\n",n,raiz);
	char cor[n];
	int tdes[n];
	int tfin[n];
	int cont = 0;
	fputs("Inicializando os v�rtices...\n", arq);
	for(int i=0; i<n; i++) cor[i] = 'b';
	
	fputs("Realizando a busca a partir da raiz...\n", arq);
	visita(M, n, raiz, cor, &cont, tdes, tfin, arq);
	
	for(int i=0; i<n; i++){
		
		if(cor[i] == 'b') {
			
			fprintf(arq,"Visitando o v�rtice %d...\n",i);
			visita(M, n, i, cor, &cont, tdes, tfin, arq);
			
		}
		
	}
	fputs("V�rtice   Cor   Tempo de descoberta   Tempo de finaliza��o\n", arq);
	for(int i=0; i<n; i++) fprintf(arq,"%d         %c     %d                     %d\n",i,cor[i],tdes[i],tfin[i]);
	fclose(arq);
	
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
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0}
	};
	buscaProfundidade(*grafos, 10, 0);
	return 0;
	
}
