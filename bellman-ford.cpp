#include <stdio.h>
#include <stdlib.h>

void relaxa(int u, int v, int *M, int n, int *d, int *pai){
	
	if((*(d+v) == -1) || (*(d+v) > *(d+u) + *(M + u*n + v))){
		
		*(d+v) = *(d+u) + *(M + u*n + v);
		*(pai+v) = u;
		
	}
	
}

bool bellmanford(int *M, int n, int raiz){
	
	int d[n];
	int pai[n];
	for(int i=0; i<n; i++){
		
		d[i] = -1;
		pai[i] = -1;
		
	}
	d[raiz] = 0;
	for(int i=1; i<n; i++){
		
		for(int j=0; j<n; j++){
			
			for(int k=0; k<n; k++){
				
				if(*(M + j*n + k) != -1) relaxa(j, k, M, n, d, pai);
				
			}
			
		}
		
	}
	for(int i=0; i<n; i++) printf("%d   %d\n",d[i],pai[i]);
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
	bellmanford(*grafos, 4, 0);
	return 0;
	
}
