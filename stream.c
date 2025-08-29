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

typedef struct ListaCat{
    char tipo[100];
    char nomecat[100];
    struct ARVCat *ant;
    struct ARVcat *prox;
    struct ArvProg *prog; //ponteiro para a arvore de programas 
}ListaCat;
//no da arvore de streams
typedef struct nostream{
    char nome[100];
    char site [100];
    struct ARVcat *cat;
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
    novo -> direita = NULL;
    novo->cat = criarcategoria();

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


ListaCat *criarcategoria(){
    return NULL;

}

ListaCat *adicionarcategoria(ListaCat *lista, char *tipocat, char *nomecategoria){
    ListaCat *novo = (ListaCat *) malloc(sizeof(ListaCat));
    strcpy(novo->tipo, tipocat);
    strcpy(novo->nomecat, nomecategoria);
    
    if(lista == NULL){
        novo->prox = novo;
        novo->ant = novo;

        return novo;
    }
    
    ListaCat *atual = lista;

    do{
        if(strcpm(novo->nomecat, atual->nomecat) < 0){
            break;
        }
        atual = atual->prox;

    }while(atual!= lista);

    ListaCat *anterior = atual->ant;

    novo->prox = atual;
    novo-> ant =anterior;
    anterior->prox = novo;
    atual->ant= novo;

    if(strcmp(novo->nomecat, lista->nomecat)< 0){
        return novo;
    }else{
        return lista;
    }
}

nostream *BuscaStream(nostream *arvstream, char *nome){
    if(arvstream != NULL){
        if(strcmp(nome, arvstream->nome) < 0){
            return BuscaStream(arvstream->esq, nome);
        }else if(strcmp(nome, arvstream->nome) > 0){
            return BuscaStream(arvstream->direita, nome);
        }else{
            return arvstream;
        }
    }

    return NULL;
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
        case 3: 
            printf("Adicionar Categoria");
            printf("Adicionar a qual stream? Digite o nome: \n");
            char nomestream[100];
            scanf('%s', nomestream);
            nostream *achou = BuscaStream(raizdastream, &nomestream);

            if(achou == NULL){
                printf("Stream não cadastrada!\n");
            }else{
                char tipocat[100];
                char nomecat[100];
                printf("Tipo da categoria: \n");
                scanf("%s", tipocat);
                printf("Nome Catego")
                adicionarcategoria(raizdastream)
            }

        default:
        printf("Opcao invalida/n");

       }
    }while (op!=0);
   
    return 0;
}