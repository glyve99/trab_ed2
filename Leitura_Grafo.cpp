#include <stdio.h>
#include <stdlib.h>

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
	f1 = fopen("Grafos-textual2.txt", "r");
	int type, n;
	int grafo[5][5];
	lergrafo(f1, &type, &n, *grafo);
	printf("%d   %d\n",type,n);
	for(int i=0; i<n; i++){
		
		for(int j=0; j<n; j++){
			
			printf("%d",grafo[i][j]);
			
		}
		
		printf("\n");
		
	}
	
}
