#include <stdio.h>
#include <stdlib.h>

#define MAX   100

typedef struct f{   //Struct fila para a busca em largura
	
	int V[MAX];
	int ini, fim;
	
} fila;

bool insercao(fila *f, int elem){   //Fun��o inser��o em uma fila
	
	if(f->fim != MAX){
		
		f->V[f->fim] = elem;
		f->fim++;
		return true;
		
	}
	
	return false;
	
}

bool remocao(fila *f, int *elem){   //Fun��o remo��o em uma fila
	
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

bool vazia(fila f){   //Fun��o para verificar se uma dada fila est� vazia
	
	if(f.ini == f.fim) return true;
	else return false;
	
}

void visita(int *M, int n, int ind, char *cor, int *cont, int *tdes, int *tfin, FILE *arq){   //Fun��o visita para a busca em profundidade
	
	*(cor+ind) = 'c';
	fprintf(arq,"Pintando o v�rtice %d de cinza\n",ind);
	*cont = *cont + 1;
	*(tdes+ind) = *cont;
	fprintf(arq,"Tempo de descobrimento do v�rtice %d: %d\n",ind,*cont);
	for(int i=0; i<n; i++){
		
		if((*(M + n*ind + i)) == 1){   //Se o v�rtice i for adjacente ao v�rtice ind
		
			if((*(cor+i)) == 'b') {   //E se a cor do v�rtice i for branco, fa�a...
				
				fprintf(arq,"Visitando o v�rtice %d...\n",i);
				visita(M, n, i, cor, cont, tdes, tfin, arq);
				
			}
		
		}
		
	}
	
	*(cor+ind) = 'p';
	fprintf(arq,"Pintando o v�rtice %d de preto\n",ind);
	*cont = *cont + 1;
	*(tfin+ind) = *cont;
	fprintf(arq,"Tempo de finaliza��o do v�rtice %d: %d\n",ind,*cont);
	
}

void visita2(int *M, int n, int ind, char *cor, int *cont, int *tdes, int *tfin){   //Fun��o visita para o algoritmo de caminho
	
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

void buscaProfundidade(int *M, int n, int raiz){   //Busca em profundidade
	
	FILE *arq;
	arq = fopen("buscaProfundidade.txt", "w");
	fprintf(arq,"Realizando a busca em profundidade em um grafo com %d v�rtices, partindo do v�rtice %d\n",n,raiz);
	char cor[n];   //Vetor de cores de cada v�rtice
	int tdes[n];   //Vetor de tempo de descobrimento de cada v�rtice
	int tfin[n];   //Vetor de tempo de finaliza��o de cada v�rtice
	int cont = 0;
	fputs("Inicializando os v�rtices...\n", arq);
	for(int i=0; i<n; i++) cor[i] = 'b';   //Pintando todos os v�rtices de branco
	
	fputs("Realizando a busca a partir da raiz...\n", arq);
	visita(M, n, raiz, cor, &cont, tdes, tfin, arq);   //Realizando a visita a partir da raiz
	
	for(int i=0; i<n; i++){
		
		if(cor[i] == 'b') {   //Verificando se h� algum v�rtice que n�o foi alcan�ado pela primeira busca (a partir da raiz).
		                      //Se houver, come�ar� a busca novamente a partir desse v�rtice.
			
			fprintf(arq,"Visitando o v�rtice %d...\n",i);
			visita(M, n, i, cor, &cont, tdes, tfin, arq);
			
		}
		
	}
	fputs("V�rtice   Cor   Tempo de descoberta   Tempo de finaliza��o\n", arq);
	for(int i=0; i<n; i++) fprintf(arq,"%d         %c     %d                     %d\n",i,cor[i],tdes[i],tfin[i]);
	fclose(arq);
	
}

void buscaLargura(int *M, int n, int raiz){   //Busca em largura
	
	FILE *arq;
	arq = fopen("buscaLargura.txt","w");
	fprintf(arq,"Realizando a busca em largura em um grafo com %d v�rtices, partindo do v�rtice %d\n",n,raiz);
	fila f;   //Iniciando a fila
	f.ini = 0;
	f.fim = 0;
	char cor[n];   //Vetor de cores de cada v�rtice
	int dist[n];   //Vetor de dist�ncia de cada v�rtice
	int pai[n];   //Vetor de pai de cada v�rtice
	fputs("Inicializando os v�rtices...\n",arq);
	for(int i=0; i<n; i++){
		
		cor[i] = 'b';
		dist[i] = -1;
		pai[i] = -1;
		
	}
	cor[raiz] = 'c';
	fprintf(arq,"Pintando o v�rtice %d de cinza\n",raiz);
	dist[raiz] = 0;
	fprintf(arq,"Dist�ncia do v�rtice %d: 0\n",raiz);
	insercao(&f, raiz);   //Inserindo v�rtice raiz na fila
	fprintf(arq,"Inserindo o v�rtice %d na fila\n",raiz);
	int ind;
	while(!vazia(f)){
		
		remocao(&f, &ind);
		fprintf(arq,"Removendo o v�rtice %d da fila\n",ind);
		for(int i=0; i<n; i++){
			
			if(*(M + n*ind + i) == 1){   //Se o v�rtice i for adjacente ao v�rtice ind
				
				if(cor[i] == 'b'){   //E se a cor do v�rtice i for branco, fa�a...
					
					cor[i] == 'c';
					fprintf(arq,"Pintando o v�rtice %d de cinza\n",i);
					dist[i] = dist[ind] + 1;
					fprintf(arq,"Dist�ncia do v�rtice %d: %d\n",i,dist[i]);
					pai[i] = ind;
					fprintf(arq,"Pai do v�rtice %d: %d\n",i,pai[i]);
					insercao(&f, i);
					fprintf(arq,"Inserindo o v�rtice %d na fila\n",i);
					
				}
				
			}
			
		}
		
		cor[ind] = 'p';
		fprintf(arq,"Pintando o v�rtice %d de preto\n",ind);
		
	}
	fputs("V�rtice   Cor   Dist�ncia   Pai\n",arq);
	for(int i=0; i<n; i++) fprintf(arq,"%d         %c     %d           %d\n",i,cor[i],dist[i],pai[i]);
	fclose(arq);
	
}

void relaxa(int u, int v, int *M, int n, int *d, int *pai, FILE *arq){   //Fun��o relaxa, utilizada no algoritmo de Dijkstra e Bellman-ford
	
	if((*(d+v) == -1) || (*(d+v) > *(d+u) + *(M + u*n + v))){
		
		fprintf(arq,"Encontrado um caminho menos custoso para o v�rtice %d.\n",v);
		*(d+v) = *(d+u) + *(M + u*n + v);
		fprintf(arq,"V�rtice %d agora tem dist�ncia %d\n",v,*(d+v));
		*(pai+v) = u;
		fprintf(arq,"V�rtice %d agora tem como pai o v�rtice %d\n",v,u);
		
	}
	
}

bool vazio(bool *v, int n){   //Fun��o para verificar se o conjunto Q do algoritmo de Dijkstra est� vazio.
	
	for(int i=0; i<n; i++){
		
		if((*(v+i)) == true) return false;
		
	}
	
	return true;
	
}

void dijkstra(int *M, int n, int raiz){
	
	FILE *arq;
	arq = fopen("dijkstra.txt","w");
	fprintf(arq,"Aplicando o algoritmo de Dijkstra em um grafo com %d v�rtices, partindo do v�rtice %d\n",n,raiz);
	bool Q[n];   //Conjunto dos v�rtices ainda n�o processados
	bool S[n];   //Conjunto dos v�rtices j� processados
	int d[n];   //Vetor da dist�ncia de cada v�rtice
	int pai[n];   //Vetor do pai de cada v�rtice
	fputs("Inicializando os v�rtices...\n",arq);
	for(int i=0; i<n; i++){
		
		d[i] = -1;
		pai[i] = -1;
		Q[i] = true;
		
	}
	d[raiz] = 0;
	fprintf(arq,"Dist�ncia do v�rtice %d: 0\n",raiz);
	int menor, menorind, aux;
	while(!vazio(Q,n)){   //Enquanto o conjunto Q n�o estiver vazio, ache o v�rtice com menor dist�ncia que est� em Q
		
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
		
		fprintf(arq,"Extraindo, para processamento, o v�rtice de menor dist�ncia que ainda n�o foi processado. (V�rtice %d)\n",menorind);
		//Movendo o v�rtice menorind (v�rtice de menor dist�ncia que est� no conjunto Q) do conjunto Q para o conjunto S
		S[menorind] = true;
		Q[menorind] = false;
		for(int i=0; i<n; i++){
			
			if(*(M + menorind*n + i) != -1){   //Se o v�rtice i for adjacente ao v�rtice menorind...
				
				fprintf(arq,"Aplicando a fun��o relaxa no v�rtice %d, em rela��o ao seu vizinho %d\n",menorind,i);
				relaxa(menorind, i, M, n, d, pai,arq);
				
			}
			
		}
		
	}
	fputs("V�rtice   Dist�ncia   Pai\n",arq);
	for(int i=0; i<n; i++) fprintf(arq,"%d         %d           %d\n",i,d[i],pai[i]);
	fclose(arq);
	
}

bool bellmanFord(int *M, int n, int raiz){   //Algoritmo de Bellman-Ford
	
	FILE *arq;
	arq = fopen("bellmanFord.txt","w");
	fprintf(arq,"Aplicando o algoritmo de Bellman-ford em um grafo com %d v�rtices, partindo do v�rtice %d\n",n,raiz);
	int d[n];   //Vetor de dist�ncia de cada v�rtice
	int pai[n];   //Vetor de pai de cada v�rtice
	fputs("Inicializando os v�rtices...\n",arq);
	for(int i=0; i<n; i++){
		
		d[i] = -1;
		pai[i] = -1;
		
	}
	d[raiz] = 0;
	fprintf(arq,"Dist�ncia do v�rtice %d: 0\n",raiz);
	for(int i=1; i<n; i++){   //Algoritmo itera de 1 at� V-1, sendo V o n�mero de v�rtices
		
		fprintf(arq,"Itera��o n�mero %d\n",i);
		for(int j=0; j<n; j++){
			
			for(int k=0; k<n; k++){
				
				if(*(M + j*n + k) != -1) {   //Se o v�rtice k for adjacente ao v�rtice j...
					
					fprintf(arq,"Aplicando a fun��o relaxa no v�rtice %d, em rela��o ao seu vizinho %d\n",j,k);
					relaxa(j, k, M, n, d, pai, arq);
					
				}
				
			}
			
		}
		
	}
	fputs("V�rtice   Dist�ncia   Pai\n",arq);
	for(int i=0; i<n; i++) fprintf(arq,"%d         %d           %d\n",i,d[i],pai[i]);
	for(int i=0; i<n; i++){   //Verificando se h� um ciclo negativo no grafo.
		
		for(int j=0; j<n; j++){
			
			if(*(M + i*n + j) != -1){
				
				if(d[j] > d[i] + *(M + i*n + j)) {
					
					fputs("Encontrado um ciclo negativo no grafo. Fun��o retornando falso",arq);
					return false;
					
				}
				
			}
			
		}
		
	}
	
	return true;
	
}

void lergrafo(FILE *arq, int *tipografo, int *numvertices, int *gr){   //Leitura de grafo em um arquivo, no formato de matriz de adjac�ncia
	
	if(arq != NULL){
		
		fseek(arq, 0, SEEK_SET);
		fscanf(arq, "%d", tipografo);   //Leitura do tipo do grafo (1 se grafo, 2 se d�grafo)
		fseek(arq, 1, SEEK_CUR);
		fscanf(arq, "%d", numvertices);   //Leitura do n�mero de v�rtices do grafo
		fseek(arq, 1, SEEK_CUR);
		int num;
		for(int i=0; i<(*numvertices); i++){   //Leitura da matriz dee adjac�ncia referente ao grafo
				
			for(int j=0; j<(*numvertices); j++){
					
				fscanf(arq, "%d", &num);
				*(gr + (*numvertices)*i + j) = num;
				fseek(arq, 1, SEEK_CUR);
						
			}
				
			fseek(arq, 1, SEEK_CUR);
				
		}
		
	}
	
}

void lertamanhografo(FILE *arq, int *numvertices){   //Fun��o para ler o tamanho do grafo em um arquivo
	
	if(arq != NULL){
		
		fseek(arq, 2, SEEK_SET);
		fscanf(arq, "%d", numvertices);
		
	}
	
}

void lertipografo(FILE *arq, int *type){   //Fun��o para ler o tipo do grafo em um arquivo
	
	if(arq != NULL){
		
		fseek(arq, 0, SEEK_SET);
		fscanf(arq, "%d", type);
		
	}
	
}

bool caminho(int *M, int n, int u, int v){   //Fun��o para verificar se h� caminho entre dois v�rtices de um grafo (mesma l�gica da busca em profundidade)
	
	char cor[n];
	int tdes[n];
	int tfin[n];
	int cont = 0;
	for(int i=0; i<n; i++) cor[i] = 'b';
	visita2(M, n, raiz, cor, &cont, tdes, tfin);
	
	if(cor[v] == 'b') return false;
	
	return true;
	
}

bool conexo(int *M, int n){   //Fun��o para verificar se um grafo � conexo
	
	for(int i=0; i<n; i++){
		
		for(int j=0; j<n; j++){
			
			if((!(caminho(M, n, i, j))) && (!(caminho(M, n, j, i)))) return false;
			
		}
		
	}
	
	return true;
	
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
