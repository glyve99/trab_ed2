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
	while(!vazia(f)){
		int ind;
		remocao(&f, &ind);
		for(int j=0; j<n; j++){
			if(*(M + n*ind + j) == 1){
				if(cor[j] == 'b'){
					cor[j] == 'c';
					dist[j] = dist[ind] + 1;
					pai[j] = ind;
					insercao(&f, j);
				}
			}
		}
		cor[ind] = 'p';
	}
	for(int k=0; k<n; k++){
		printf("%c   %d   %d\n",cor[k],dist[k],pai[k]);
	}
	
}

int main(void){
	
	int grafos[5][5] = {{0, 0, 1, 1, 0}, {1, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 0, 0, 1}, {1, 0, 0, 0, 0}};
	buscaLargura(*grafos, 5, 0);
	
}
