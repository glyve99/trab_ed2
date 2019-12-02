#include <stdio.h>
#include <stdlib.h>

void visita2(int *M, int n, int ind, char *cor, int *cont, int *tdes, int *tfin){   //Função visita para o algoritmo de caminho
	
	*(cor+ind) = 'c';
	*cont = *cont + 1;
	*(tdes+ind) = *cont;
	for(int i=0; i<n; i++){
		
		if((*(M + n*ind + i)) == 1){
		
			if((*(cor+i)) == 'b') visita2(M, n, i, cor, cont, tdes, tfin);
			
		}
		
	}
	
	*(cor+ind) = 'p';
	*cont = *cont + 1;
	*(tfin+ind) = *cont;
	
}

bool caminho(int *M, int n, int u, int v){   //Função para verificar se há caminho entre dois vértices de um grafo (mesma lógica da busca em profundidade)
	
	char cor[n];
	int tdes[n];
	int tfin[n];
	int cont = 0;
	for(int i=0; i<n; i++) cor[i] = 'b';
	visita2(M, n, u, cor, &cont, tdes, tfin);
	
	if(cor[v] == 'b') return false;
	
	return true;
	
}

void lergrafo(FILE *arq, int *tipografo, int *numvertices, int *gr){
	
	if(arq != NULL){
		
		fseek(arq, 0, SEEK_SET);
		fscanf(arq, "%d", tipografo);
		fseek(arq, 1, SEEK_CUR);
		fscanf(arq, "%d", numvertices);
		fseek(arq, 1, SEEK_CUR);
		int num;
		for(int i=0; i<(*numvertices); i++){
				
			for(int j=0; j<(*numvertices); j++){
					
				fscanf(arq, "%d", &num);
				*(gr + (*numvertices)*i + j) = num;
				fseek(arq, 1, SEEK_CUR);
						
			}
				
			fseek(arq, 1, SEEK_CUR);
				
		}
		
	}
	
}

bool conexo(int *M, int n){   //Função para verificar se um grafo é conexo
	
	for(int i=0; i<n; i++){
		
		for(int j=0; j<n; j++){
			
			if((!(caminho(M, n, i, j))) && (!(caminho(M, n, j, i)))) return false;
			
		}
		
	}
	
	return true;
	
}

int main(void){
	
	FILE *f1;
	f1 = fopen("Grafos-textual.txt","r");
	int type,n;
	int grafo[5][5];
	lergrafo(f1,&type,&n,*grafo);
	printf("%d",conexo(*grafo,n));
	return 0;
	
}
