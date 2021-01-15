//Trabalho . ED1.
//Marianna Karenina de Almeida Fl�res
//N�USP: 10821144

//<<< �rvore de Decis�o >>>>

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h> 

struct auxiliar{
    char identificador [150];
};


struct NO{
   	char info [150];
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO* ArvBin;

//typedef struct NO Elem;

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}
//<<<<<<<<<< PROCURA >>>>>>>>>>>>>>>>>
ArvBin* Procura_preOrdem_ArvBin(ArvBin *raiz, char valor [150])
{

    if(raiz == NULL){
	
     printf("raiz NULL \n");
        return NULL;
    }
   
    if(*raiz != NULL)
    {
    	
    	int teste = strcmp (valor, ((*raiz)->info));

    	
        if (strcmp (valor, ((*raiz)->info)) == 0) {
        	
        //	printf("achou!!\n");
        	
			return raiz;
		}
        else{
           struct NO** achou;
           achou = Procura_preOrdem_ArvBin(&((*raiz)->esq), valor);
           if (achou != NULL)
           		return achou;
           achou = Procura_preOrdem_ArvBin(&((*raiz)->dir), valor);
           if (achou != NULL)
           		return achou;
           		    
        }
       
    }
    
    return NULL;
}

//<<<<<<<<<<<< INSER��O >>>>>>>>>>>>>>>>>>>>>>>>>
int insere_ArvBin(ArvBin* raiz, char valor_identif [150], char valor_esquerd [150], char valor_direit [150] ){
	
    if(raiz == NULL)
        return 0;
    
    struct NO* novo_esq;
    novo_esq = (struct NO*) malloc(sizeof(struct NO));	//filha_esquerda
    if(novo_esq == NULL)
        return 0;
        
    struct NO* novo_dir;
    novo_dir = (struct NO*) malloc(sizeof(struct NO));	//filha_direita
    if(novo_dir == NULL)
        return 0;

	
	strcpy((*novo_esq).info, valor_esquerd);			//filha_esquerda
    novo_esq->dir = NULL;
    novo_esq->esq = NULL;
    
    strcpy((*novo_dir).info, valor_direit);					//filha_direita
    novo_dir->dir = NULL;
    novo_dir->esq = NULL;

    if(*raiz == NULL){
	
   		struct NO* novo;														//pai
    	novo = (struct NO*) malloc(sizeof(struct NO));
   		novo->dir = NULL;
    	novo->esq = NULL;
	   	
		if(novo == NULL){  
		   return 0;
	    }
		   
   		strcpy((*novo).info, valor_identif);					
    	novo->dir = novo_dir;
    	novo->esq = novo_esq;
   		
   		*raiz = novo;
   	
 	}
        
	else{
		
		struct NO** insere;
		insere = Procura_preOrdem_ArvBin(raiz, valor_identif);
		
		if(insere == NULL){ 
			return 0; 
		}
		
		(*insere)-> dir = novo_dir;
		(*insere)-> esq = novo_esq;

	}
			
       
    return 1;

}

void preOrdem_ArvBin(ArvBin *raiz)

{	
	

	int filhos;
	int esquerda;
	int direita ;
	
	filhos = 0;
	esquerda = 0;
	direita = 0;
	
	char aux[150];
	char aux_esq[150];
	char aux_dir[150];
	
	
	
		strcpy(aux,(*raiz)->info);
			strcpy(aux_esq,(*raiz)->esq);
				strcpy(aux_dir,(*raiz)->dir );
			
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
    	
    	
    	 if (strcmp(aux_esq, "X") != 0 && aux_esq != NULL){
    	 	
        	filhos ++;
			esquerda ++;
			
    	}
    	
    	if (strcmp(aux_dir, "X") != 0 && aux_dir != NULL ){
     	
        	filhos ++;
			direita ++;
			
    	}
    	
    	if( strcmp(aux, "X") != 0 && aux != NULL ){
       		
				printf("%s ",(*raiz)->info);
        		printf("%d ", filhos);
        
        		if(esquerda == 1 && filhos ==  1){
        			printf("E \n");	
				}
				if(direita == 1 && filhos ==  1){
					printf("D \n");
				}
				if(filhos ==  2){
					printf("ED \n");
				}
				if (filhos == 0){
					printf("F \n");
				}
			}
		
        if(strcmp(((*raiz)->esq), "X") != 0) {
	
			preOrdem_ArvBin(&((*raiz)->esq));
		}
			
        if(strcmp(((*raiz)->dir), "X") != 0) {
		
			
			preOrdem_ArvBin(&((*raiz)->dir));
		}
        
    }
}

int totalNO_ArvBin(ArvBin *raiz){
	
	int alt_esq = 0;
	int alt_dir = 0;
	
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
        
     if(strcmp(((*raiz)->esq), "X") != 0) {
   		 alt_esq = totalNO_ArvBin(&((*raiz)->esq));
     }
     if(strcmp(((*raiz)->dir), "X") != 0) {
   		 alt_dir = totalNO_ArvBin(&((*raiz)->dir));
     }
     
    return(alt_esq + alt_dir + 1);
}


int totalFOLHA_ArvBin(ArvBin *raiz){
	int cont = 0;
	
	if(raiz == NULL) return 0;
	if(strcmp(((*raiz)->dir), "X") == 0 && strcmp(((*raiz)->esq), "X") == 0) cont = 1;
	else{if(strcmp(((*raiz)->esq), "X") != 0) cont += totalFOLHA_ArvBin(&((*raiz)->esq));
         if(strcmp(((*raiz)->dir), "X") != 0) cont += totalFOLHA_ArvBin(&((*raiz)->dir));
	}return cont;
}


void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada n�
    free(raiz);//libera a raiz
}

//<<<<<<<<<<<<<< main

int main (void){
	
	ArvBin* inicio;
		
	inicio = cria_ArvBin ();
	
	char comando[150];
	
	char identific [50];
	
	struct auxiliar ident;
	struct auxiliar esq;
	struct auxiliar dir;
	
	int tamanho_string = 0;
	int aux = 0;
	int space = 0;
	int k = 0;
	int j = 0;
	int m = 0;
	int n = 0; // vari�vel que sinaliza parada
	int *achou = 0;
	int total_nos_semfilho = 0;
	int total_nos = 0;
	
	while (n == 0){
		
		tamanho_string = 0;
		aux = 0;
		space = 0;
		k = 0;
		j = 0;
		m = 0;
			
		setbuf(stdin, NULL);
		
		fgets(comando, 150, stdin);
		
		while(comando[aux]!= '\n'){ 		    	//separa as strings 
	
			if (comando[aux]!=' ' && space == 0){   //separa Identificador
				identific[k] = comando[aux];
				ident.identificador[k] = comando[aux];
				ident.identificador[k+1] = '\0';
	
			}
			
			if (comando[aux]!=' ' && space == 1){  //separa Esquerda
				
				esq.identificador[j]=comando[aux];
				esq.identificador[j+1] = '\0';
		
				j ++;
			}
			
			if (comando[aux]!=' ' && space == 2){  //separa Direita
				
				dir.identificador[m]=comando[aux];
				dir.identificador[m+1] = '\0';
	
				m ++;
			}
			
			if (comando[aux]==' '){   
							             //sinaliza espa�o
				space ++;	
				
				if (space == 3){
					space = 0;
				}
				
			}
			
			if(identific[k] == 'X' ){             //descobre Parada	
				n = 1;
			}
			
			 k++;
			 aux ++;	 
		}
		
	
	
		insere_ArvBin(inicio, ident.identificador, esq.identificador, dir.identificador);		//insere o raiz
	
	}

	
	preOrdem_ArvBin(inicio);
	
	total_nos = totalNO_ArvBin (inicio);
	


	total_nos_semfilho = totalFOLHA_ArvBin (inicio);

	
	printf("%d %d", total_nos, total_nos_semfilho);
	
	libera_ArvBin(inicio);
		
	return 0;
	
}

