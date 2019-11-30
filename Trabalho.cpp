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

void visita(int *M, int n, int ind, char *cor, int *cont, int *tdes, int *tfin, FILE *arq){
	
	*(cor+ind) = 'c';
	fprintf(arq,"Pintando o vértice %d de cinza\n",ind);
	*cont = *cont + 1;
	*(tdes+ind) = *cont;
	fprintf(arq,"Tempo de descobrimento do vértice %d: %d\n",ind,*cont);
	for(int i=0; i<n; i++){
		
		if((*(M + n*ind + i)) == 1){
		
			if((*(cor+i)) == 'b') {
				
				fprintf(arq,"Visitando o vértice %d...\n",i);
				visita(M, n, i, cor, cont, tdes, tfin, arq);
				
			}
		
		}
		
	}
	
	*(cor+ind) = 'p';
	fprintf(arq,"Pintando o vértice %d de preto\n",ind);
	*cont = *cont + 1;
	*(tfin+ind) = *cont;
	fprintf(arq,"Tempo de finalização do vértice %d: %d\n",ind,*cont);
	
}

void buscaProfundidade(int *M, int n, int raiz){
	
	FILE *arq;
	arq = fopen("buscaProfundidade.txt", "w");
	fprintf(arq,"Realizando a busca em profundidade em um grafo com %d vértices, partindo do vértice %d\n",n,raiz);
	char cor[n];
	int tdes[n];
	int tfin[n];
	int cont = 0;
	fputs("Inicializando os vértices...\n", arq);
	for(int i=0; i<n; i++) cor[i] = 'b';
	
	fputs("Realizando a busca a partir da raiz...\n", arq);
	visita(M, n, raiz, cor, &cont, tdes, tfin, arq);
	
	for(int i=0; i<n; i++){
		
		if(cor[i] == 'b') {
			
			fprintf(arq,"Visitando o vértice %d...\n",i);
			visita(M, n, i, cor, &cont, tdes, tfin, arq);
			
		}
		
	}
	fputs("Vértice   Cor   Tempo de descoberta   Tempo de finalização\n", arq);
	for(int i=0; i<n; i++) fprintf(arq,"%d         %c     %d                     %d\n",i,cor[i],tdes[i],tfin[i]);
	fclose(arq);
	
}

void buscaLargura(int *M, int n, int raiz){
	
	FILE *arq;
	arq = fopen("buscaLargura.txt","w");
	fprintf(arq,"Realizando a busca em largura em um grafo com %d vértices, partindo do vértice %d\n",n,raiz);
	fila f;
	f.ini = 0;
	f.fim = 0;
	char cor[n];
	int dist[n];
	int pai[n];
	fputs("Inicializando os vértices...\n",arq);
	for(int i=0; i<n; i++){
		
		cor[i] = 'b';
		dist[i] = -1;
		pai[i] = -1;
		
	}
	cor[raiz] = 'c';
	fprintf(arq,"Pintando o vértice %d de cinza\n",raiz);
	dist[raiz] = 0;
	fprintf(arq,"Distância do vértice %d: 0\n",raiz);
	insercao(&f, raiz);
	fprintf(arq,"Inserindo o vértice %d na fila\n",raiz);
	int ind;
	while(!vazia(f)){
		
		remocao(&f, &ind);
		fprintf(arq,"Removendo o vértice %d da fila\n",ind);
		for(int i=0; i<n; i++){
			
			if(*(M + n*ind + i) == 1){
				
				if(cor[i] == 'b'){
					
					cor[i] == 'c';
					fprintf(arq,"Pintando o vértice %d de cinza\n",i);
					dist[i] = dist[ind] + 1;
					fprintf(arq,"Distância do vértice %d: %d\n",i,dist[i]);
					pai[i] = ind;
					fprintf(arq,"Pai do vértice %d: %d\n",i,pai[i]);
					insercao(&f, i);
					fprintf(arq,"Inserindo o vértice %d na fila\n",i);
					
				}
				
			}
			
		}
		
		cor[ind] = 'p';
		fprintf(arq,"Pintando o vértice %d de preto\n",ind);
		
	}
	fputs("Vértice   Cor   Distância   Pai\n",arq);
	for(int i=0; i<n; i++) fprintf(arq,"%d         %c     %d           %d\n",i,cor[i],dist[i],pai[i]);
	fclose(arq);
	
}

void relaxa(int u, int v, int *M, int n, int *d, int *pai, FILE *arq){
	
	if((*(d+v) == -1) || (*(d+v) > *(d+u) + *(M + u*n + v))){
		
		fprintf(arq,"Encontrado um caminho menos custoso para o vértice %d.\n",v);
		*(d+v) = *(d+u) + *(M + u*n + v);
		fprintf(arq,"Vértice %d agora tem distância %d\n",v,*(d+v));
		*(pai+v) = u;
		fprintf(arq,"Vértice %d agora tem como pai o vértice %d\n",v,u);
		
	}
	
}

bool vazio(bool *v, int n){
	
	for(int i=0; i<n; i++){
		
		if((*(v+i)) == true) return false;
		
	}
	
	return true;
	
}

void dijkstra(int *M, int n, int raiz){
	
	FILE *arq;
	arq = fopen("dijkstra.txt","w");
	fprintf(arq,"Aplicando o algoritmo de Dijkstra em um grafo com %d vértices, partindo do vértice %d\n",n,raiz);
	bool Q[n];
	bool S[n];
	int d[n];
	int pai[n];
	fputs("Inicializando os vértices...\n",arq);
	for(int i=0; i<n; i++){
		
		d[i] = -1;
		pai[i] = -1;
		Q[i] = true;
		
	}
	d[raiz] = 0;
	fprintf(arq,"Distância do vértice %d: 0\n",raiz);
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
		
		fprintf(arq,"Extraindo, para processamento, o vértice de menor distância que ainda não foi processado. (Vértice %d)\n",menorind);
		S[menorind] = true;
		Q[menorind] = false;
		for(int i=0; i<n; i++){
			
			if(*(M + menorind*n + i) != -1){
				
				fprintf(arq,"Aplicando a função relaxa no vértice %d, em relação ao seu vizinho %d\n",menorind,i);
				 relaxa(menorind, i, M, n, d, pai,arq);
				
			}
			
		}
		
	}
	fputs("Vértice   Distância   Pai\n",arq);
	for(int i=0; i<n; i++) fprintf(arq,"%d         %d           %d\n",i,d[i],pai[i]);
	fclose(arq);
	
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

void lertamanhografo(FILE *arq, int *numvertices){
	
	if(arq != NULL){
		
		fseek(arq, 2, SEEK_SET);
		fscanf(arq, "%d", numvertices);
		
	}
	
}

int main(void){
	
	FILE *f1, *f2;
	f1 = fopen("Grafos-textual.txt","r");
	int n;
	lertamanhografo(f1, &n);
	int grafo[n][n];
	int type;
	lergrafo(f1,&type,&n,*grafo);
	buscaProfundidade(*grafo,n,0);
	buscaLargura(*grafo,n,0);
	f2 = fopen("Grafos-textual2.txt","r");
	lertamanhografo(f2, &n);
	int grafo2[n][n];
	lergrafo(f2,&type,&n,*grafo2);
	dijkstra(*grafo2,n,0);
	bellmanFord(*grafo2,n,0);
	return 0;
	
}
