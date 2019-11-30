#include <stdio.h>
#include <stdlib.h>

void relaxa(int u, int v, int *M, int n, int *d, int *pai, FILE *arq){
	
	if((*(d+v) == -1) || (*(d+v) > *(d+u) + *(M + u*n + v))){
		
		fprintf(arq,"Encontrado um caminho menos custoso para o v�rtice %d.\n",v);
		*(d+v) = *(d+u) + *(M + u*n + v);
		fprintf(arq,"V�rtice %d agora tem dist�ncia %d\n",v,*(d+v));
		*(pai+v) = u;
		fprintf(arq,"V�rtice %d agora tem como pai o v�rtice %d\n",v,u);
		
	}
	
}

bool bellmanFord(int *M, int n, int raiz){
	
	FILE *arq;
	arq = fopen("bellmanFord.txt","w");
	fprintf(arq,"Aplicando o algoritmo de Bellman-ford em um grafo com %d v�rtices, partindo do v�rtice %d\n",n,raiz);
	int d[n];
	int pai[n];
	fputs("Inicializando os v�rtices...\n",arq);
	for(int i=0; i<n; i++){
		
		d[i] = -1;
		pai[i] = -1;
		
	}
	d[raiz] = 0;
	fprintf(arq,"Dist�ncia do v�rtice %d: 0\n",raiz);
	for(int i=1; i<n; i++){
		
		fprintf(arq,"Itera��o n�mero %d\n",i);
		for(int j=0; j<n; j++){
			
			for(int k=0; k<n; k++){
				
				if(*(M + j*n + k) != -1) {
					
					fprintf(arq,"Aplicando a fun��o relaxa no v�rtice %d, em rela��o ao seu vizinho %d\n",j,k);
					relaxa(j, k, M, n, d, pai, arq);
					
				}
				
			}
			
		}
		
	}
	fputs("V�rtice   Dist�ncia   Pai\n",arq);
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
