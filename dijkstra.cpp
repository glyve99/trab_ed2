#include <stdio.h>
#include <stdlib.h>

void relaxa(int u, int v, int *M, int n, int *d, int *pai){
	
	if((*(d+v) == -1) || (*(d+v) > *(d+u) + *(M + u*n + v))){
		
		*(d+v) = *(d+u) + *(M + u*n + v);
		*(pai+v) = u;
		
	}
	
}

bool vazio(bool *v, int n){
	
	for(int i=0; i<n; i++){
		
		if((*(v+i)) == true) return false;
		
	}
	
	return true;
	
}

void dijkstra(int *M, int n, int raiz){
	
	bool Q[n];
	bool S[n];
	int d[n];
	int pai[n];
	for(int i=0; i<n; i++){
		
		d[i] = -1;
		pai[i] = -1;
		Q[i] = true;
		
	}
	d[raiz] = 0;
	int menor, menorind, aux;
	while(!vazio(Q,n)){
		
		aux = 0;
		
		for(int j=0; j<n; j++){
			
			if((Q[j] == true) && (d[j] != -1)){
				
				if(!aux){
					
					aux = 1;
					menor = d[j];
					menorind = j;
					
				}
				
				if(d[j] < menor){
					
					menor = d[j];
					menorind = j;
					
				}
				
			}
			
		}
		
		S[menorind] = true;
		Q[menorind] = false;
		for(int k=0; k<n; k++){
			
			if(*(M + menorind*n + k) != -1) relaxa(menorind, k, M, n, d, pai);
			
		}
		
	}
	for(int l=0; l<n; l++){
		
		printf("%d   %d   %d   %d\n",d[l],pai[l],Q[l],S[l]);
		
	}
	
}

int main(void){
	
	int grafos[5][5] = {
		{-1, 10, -1, 5, -1},
		{-1, -1, 1, 2, -1},
		{-1, -1, -1, -1, 4},
		{-1, 3, 9, -1, 2},
		{7, -1, 6, -1, -1},
	};
	dijkstra(*grafos, 5, 0);
	return 0;
	
}
