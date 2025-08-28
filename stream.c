#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//no da arvore de programas
typedef struct ArvProg{
    char nomeProg[100];
    char periodo[100];
    char hora_inicio[100];
    bool ao_vivo;
    char nome_apresent[100];

}ArvProg;

typedef struct arvcat{
    char tipo[100];
    char nomecat[100];
    struct ARVCat *ant;
    struct ARVcat *prox;
    struct ArvProg *prog; //ponteiro para a arvore de programas 
}ARVcat;
//no da arvore de streams
typedef struct nostream{
    char nome[100];
    char site [100];

    struct nostream *esq; // ponteiro para sub arvore esquerda 
    struct nostream *direita; // ponteiro para sub arvore direita 


}nostream;

nostream *criarstream(char *nome, char *site){
    nostream* novo = (nostream*)malloc(sizeof (nostream));

    if(novo == NULL){
        printf("erroh ao alocar");
        exit(1);

    }

    strcpy(novo -> nome, nome);
    strcpy( novo -> site, site);

    novo-> esq= NULL;
    novo ->direita = NULL;
    return novo;

}

nostream *inserirstream(nostream *raiz, char *nome, char *site){

    if(raiz == NULL){
         return criarstream(nome, site);
    }  //cria um novo no se a arvore estiver vazia, o tornando raiz.

    int cmp = strcmp(nome, raiz -> nome); //compara o nome da nova stream com o nome atual

    if(cmp < 0){
        raiz -> esq = inserirstream( raiz ->esq, nome, site); // insere na sub arvore esquerda 

    }else if(cmp > 0){
        raiz -> direita = inserirstream( raiz -> direita, nome, site);
    }else{
        printf("Stream * %s * ja existente na base de dados.\n", nome);
    } 
    return raiz;


    }

    void mostrarstream(nostream*raiz){
        if(raiz !=NULL){
            mostrarstream(raiz->esq);
            printf("\nNome: %s", raiz-> nome);
            printf("\nSite: %s", raiz->site);

            mostrarstream(raiz->direita);
           
        }
    }

    ARVcat *criarcategoria(char *tipo, char *nomecategoria){
    ARVcat *novo = (ARVcat *) malloc (sizeof(ARVcat));

    if(novo == NULL){
        printf("erro ao alocar ");
        exit(1);
    }

    strcpy(novo->tipo, tipo);
    strcpy(novo->nomecat, nomecategoria);

    novo->prox = NULL;
    novo->ant = NULL;

    return novo;
}

ARVcat *adicionarcategoria(ARVcat *lista, char *tipocat, char *nomecategoria){
    if(lista == NULL){
        criarcategoria(tipocat, nomecategoria);
    }

    ARVcat *novo = (ARVcat *) malloc(sizeof(ARVcat));
}




int main(){
   nostream * raizdastream = NULL; // raiz começando vazia 
   char nome [100];
   char site [100];
   int op;

   do{
    printf("\nBiblioteca de streams\n");
    printf("1. Cadastrar Stream\n");
    printf("2. Mostrar Stream\n");
    scanf("%d", &op);
    getchar();


       switch (op){
        case 1: 
        printf("Digite o nome do stream:\n");
        fgets(nome, sizeof(nome), stdin);
        printf("Digite o site da stream:\n");
        fgets(site, sizeof(site), stdin);
        
        raizdastream = inserirstream(raizdastream, nome, site);
        printf("Stream cadadastrada com sucesso\n");
        break;

        case 2: 
        printf("Streams Cadstradas\n");
        if(raizdastream == NULL){
             printf("Nenhuma stream cadastrada.\n");

        }else{ 
        mostrarstream(raizdastream);
        }
        break;

        default:
        printf("Opcao invalida/n");

       }
    }while (op!=0);
   
    return 0;
}



