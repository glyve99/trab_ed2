#include <stdio.h>
#include <stdlib.h>

#define MAX   100

typedef struct f{
	
	int V[MAX];
	int ini, fim;
	
} fila;

bool insercao(fila *f, int elem){
	
	if(f->fim != MAX){
		
		f->V[f->fim] = elem;
		f->fim++;
		return true;
		
	}
	
	return false;
	
}

bool remocao(fila *f, int *elem){
	
	if(f->ini != f->fim){
		
		*elem = f->V[f->ini];
		f->ini++;
		if(f->ini == f->fim){
			
			f->ini = 0;
			f->fim = 0;
			
		}
		
		return true;
		
	}
	
	return false;
	
}

bool vazia(fila f){
	
	if(f.ini == f.fim) return true;
	else return false;
	
}

void buscaLargura(int *M, int n, int raiz){
	
	FILE *arq;
	arq = fopen("buscaLargura.txt","w");
	fprintf(arq,"Realizando a busca em largura em um grafo com %d vértices, partindo do vértice %d\n",n,raiz);
	fila f;
	f.ini = 0;
	f.fim = 0;
	char cor[n];
	int dist[n];
	int pai[n];
	fputs("Inicializando os vértices...\n",arq);
	for(int i=0; i<n; i++){
		
		cor[i] = 'b';
		dist[i] = -1;
		pai[i] = -1;
		
	}
	cor[raiz] = 'c';
	fprintf(arq,"Pintando o vértice %d de cinza\n",raiz);
	dist[raiz] = 0;
	fprintf(arq,"Distância do vértice %d: 0\n",raiz);
	insercao(&f, raiz);
	fprintf(arq,"Inserindo o vértice %d na fila\n",raiz);
	int ind;
	while(!vazia(f)){
		
		remocao(&f, &ind);
		fprintf(arq,"Removendo o vértice %d da fila\n",ind);
		for(int i=0; i<n; i++){
			
			if(*(M + n*ind + i) == 1){
				
				if(cor[i] == 'b'){
					
					cor[i] == 'c';
					fprintf(arq,"Pintando o vértice %d de cinza\n",i);
					dist[i] = dist[ind] + 1;
					fprintf(arq,"Distância do vértice %d: %d\n",i,dist[i]);
					pai[i] = ind;
					fprintf(arq,"Pai do vértice %d: %d\n",i,pai[i]);
					insercao(&f, i);
					fprintf(arq,"Inserindo o vértice %d na fila\n",i);
					
				}
				
			}
			
		}
		
		cor[ind] = 'p';
		fprintf(arq,"Pintando o vértice %d de preto\n",ind);
		
	}
	fputs("Vértice   Cor   Distância   Pai\n",arq);
	for(int i=0; i<n; i++) fprintf(arq,"%d         %c     %d           %d\n",i,cor[i],dist[i],pai[i]);
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
	buscaLargura(*grafos, 10, 0);
	return 0;
	
}
