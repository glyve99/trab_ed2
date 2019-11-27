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
	
	fila f;
	f.ini = 0;
	f.fim = 0;
	char cor[n];
	int dist[n];
	int pai[n];
	for(int i=0; i<n; i++){
		cor[i] = 'b';
		dist[i] = -1;
		pai[i] = -1;
	}
	cor[raiz] = 'c';
	dist[raiz] = 0;
	insercao(&f, raiz);
	int ind;
	while(!vazia(f)){
		remocao(&f, &ind);
		for(int i=0; i<n; i++){
			if(*(M + n*ind + i) == 1){
				if(cor[i] == 'b'){
					cor[i] == 'c';
					dist[i] = dist[ind] + 1;
					pai[i] = ind;
					insercao(&f, i);
				}
			}
		}
		cor[ind] = 'p';
	}
	for(int i=0; i<n; i++){
		printf("%c   %d   %d\n",cor[i],dist[i],pai[i]);
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
	buscaLargura(*grafos, 10, 0);
	
}
