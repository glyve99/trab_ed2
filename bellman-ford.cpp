#include <stdio.h>
#include <stdlib.h>

void relaxa(int u, int v, int *M, int n, int *d, int *pai, FILE *arq){
	
	if((*(d+v) == -1) || (*(d+v) > *(d+u) + *(M + u*n + v))){
		
		fprintf(arq,"Encontrado um caminho menos custoso para o vértice %d.\n",v);
		*(d+v) = *(d+u) + *(M + u*n + v);
		fprintf(arq,"Vértice %d agora tem distância %d\n",v,*(d+v));
		*(pai+v) = u;
		fprintf(arq,"Vértice %d agora tem como pai o vértice %d\n",v,u);
		
	}
	
}

bool bellmanFord(int *M, int n, int raiz){
	
	FILE *arq;
	arq = fopen("bellmanFord.txt","w");
	fprintf(arq,"Aplicando o algoritmo de Bellman-ford em um grafo com %d vértices, partindo do vértice %d\n",n,raiz);
	int d[n];
	int pai[n];
	fputs("Inicializando os vértices...\n",arq);
	for(int i=0; i<n; i++){
		
		d[i] = -1;
		pai[i] = -1;
		
	}
	d[raiz] = 0;
	fprintf(arq,"Distância do vértice %d: 0\n",raiz);
	for(int i=1; i<n; i++){
		
		fprintf(arq,"Iteração número %d\n",i);
		for(int j=0; j<n; j++){
			
			for(int k=0; k<n; k++){
				
				if(*(M + j*n + k) != -1) {
					
					fprintf(arq,"Aplicando a função relaxa no vértice %d, em relação ao seu vizinho %d\n",j,k);
					relaxa(j, k, M, n, d, pai, arq);
					
				}
				
			}
			
		}
		
	}
	fputs("Vértice   Distância   Pai\n",arq);
	for(int i=0; i<n; i++) fprintf(arq,"%d         %d           %d\n",i,d[i],pai[i]);
	for(int i=0; i<n; i++){
		
		for(int j=0; j<n; j++){
			
			if(*(M + i*n + j) != -1){
				
				if(d[j] > d[i] + *(M + i*n + j)) return false;
				
			}
			
		}
		
	}
	
	return true;
	
}

int main(void){
	
	int grafos[4][4] = {
		{-1, 3, 7, 5},
		{-1, -1, 3, 1},
		{-1, -1, -1, -1},
		{-1, -1, 1, -1}
	};
	bellmanFord(*grafos, 4, 0);
	return 0;
	
}
