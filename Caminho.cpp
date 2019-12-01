#include <stdio.h>
#include <stdlib.h>

bool caminho(int *M, int n, int u, int v){
	
	if(*(M + u*n + v) == 0){
		
		for(int i=0; i<n; i++){
			
			if(*(M + u*n + i) != 0){
				
				if(caminho(M, n, i, v) == true) return true;
				return false;
				
			}
			
		}
		
	} else return true;
	
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

int main(void){
	
	FILE *f1;
	f1 = fopen("Grafos-textual.txt","r");
	int type,n;
	int grafo[5][5];
	lergrafo(f1,&type,&n,*grafo);
	printf("%d",caminho(*grafo,n,0,1));
	return 0;
	
}
