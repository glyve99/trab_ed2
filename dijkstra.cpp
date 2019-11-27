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
		
		for(int i=0; i<n; i++){
			
			if((Q[i] == true) && (d[i] != -1)){
				
				if(!aux){
					
					aux = 1;
					menor = d[i];
					menorind = i;
					
				}
				
				if(d[i] < menor){
					
					menor = d[i];
					menorind = i;
					
				}
				
			}
			
		}
		
		S[menorind] = true;
		Q[menorind] = false;
		for(int i=0; i<n; i++){
			
			if(*(M + menorind*n + i) != -1) relaxa(menorind, i, M, n, d, pai);
			
		}
		
	}
	for(int i=0; i<n; i++){
		
		printf("%d   %d   %d   %d\n", d[i], pai[i], Q[i], S[i]);
		
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
