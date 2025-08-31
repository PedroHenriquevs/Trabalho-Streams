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
    struct ListaCat *ant;
    struct ListaCat *prox;
    struct ArvProg *prog; //ponteiro para a arvore de programas 
}ListaCat;
//no da arvore de streams
typedef struct nostream{
    char nome[100];
    char site [100];
    struct ListaCat *cat;
    struct nostream *esq; // ponteiro para sub arvore esquerda 
    struct nostream *direita; // ponteiro para sub arvore direita 


}nostream;

ListaCat *criarcategoria(){
    return NULL;

}

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
        printf("---------------------");
        printf("\nNome: %s", raiz-> nome);
        printf("\nSite: %s\n", raiz->site);
        printf("-----------------------\n");

        mostrarstream(raiz->direita);
           
    }
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
        if(strcmp(novo->nomecat, atual->nomecat) < 0){
            break;
        }
        atual = atual->prox;

    }while(atual!= lista);

    ListaCat *anterior = atual->ant;

    novo->prox = atual;
    novo-> ant =anterior;
    anterior->prox = novo;
    atual->ant= novo;

    printf("Categoria adicionada com sucesso!\n");

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

void mostrarcategoriaStream(nostream *stream, char *nomestream){
    
    ListaCat *lista = stream->cat;
    if (lista != NULL) {
        
        int cmp = strcmp(nomestream, stream->nome);

        if(cmp < 0){
            return mostrarcategoriaStream(stream->esq, nomestream);
        }else if(cmp > 0){
            return mostrarcategoriaStream(stream->direita, nomestream);
        }else{

            ListaCat *atual = lista;
            printf("\nLISTA DE CATEGORIAS DO STREAM *%s*\n", nomestream);
            do{
                printf("-----------------------\n");
                printf("Tipo: %s\n", atual->tipo);
                printf("Nome categoria: %s\n", atual->nomecat);
                printf("--------------------\n");

                atual = atual->prox;
            }while(atual!=lista);
        }
    }else{
        printf("\nO stream *%s* não possui categorias cadastradas.\n", nomestream);
    }

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
        printf("3. Adicionar categoria ao stream\n");
        printf("4- Buscar stream\n");
        printf("5- Listar categorias de uma stream\n");
        scanf("%d", &op);
        getchar();


       switch (op){
        case 1: 
        printf("Digite o nome do stream:\n");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = 0; 

        printf("Digite o site da stream:\n");
        fgets(site, sizeof(site), stdin);
        site[strcspn(site, "\n")] = 0; 

        raizdastream = inserirstream(raizdastream, nome, site);

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
            printf("Adicionar Categoria\n");
            printf("Adicionar a qual stream? Digite o nome: \n");
            char nomestream[100];
            fgets(nomestream, sizeof(nomestream), stdin);
            nomestream[strcspn(nomestream, "\n")] = 0;
            nostream *achou = BuscaStream(raizdastream, nomestream);

            if(achou != NULL){
                char tipocat[100];
                char nomecat[100];
                printf("Tipo da categoria: \n");
                fgets(tipocat, sizeof(tipocat), stdin);
                tipocat[strcspn(tipocat, "\n")] = 0; 

                printf("Nome Categoria: \n");
                fgets(nomecat, sizeof(nomecat),stdin);
                nomecat[strcspn(nomecat, "\n")] = 0; 
                
                achou->cat = adicionarcategoria(achou->cat, tipocat, nomecat);
                printf("\n");
            }else{
                printf("Stream não cadastrada\n");
            }
            break;
        case 4:
            printf("\nBUSCAR STREAM\n");
            char nomeS[100];
            printf("Nome stream: \n");
            fgets(nomeS, sizeof(nomeS), stdin);
            nomeS[strcspn(nomeS, "\n")] = 0;
            nostream *achouNo = BuscaStream(raizdastream, nomeS);

            if(achouNo != NULL){
                printf("\n----------------------\n");
                printf("Nome: %s \n", achouNo->nome);
                printf("Site: %s \n", achouNo->site);
                printf("----------------------\n");
                break;
            }else{
                printf("\n Stream não encontrado! \n");
                break;
            }
            
        case 5:
            char nomeStream[100];
            printf("Nome stream: \n");
            fgets(nomeStream, sizeof(nomeStream), stdin);
            nomeStream[strcspn(nomeStream, "\n")] = 0;
            nostream *encontrouNo = BuscaStream(raizdastream, nomeStream);

            if(encontrouNo != NULL){
                mostrarcategoriaStream(raizdastream, nomeStream);
                break;
            }else{
                printf("Sem categoria cadastrada! \n");
                break;
            }

        default:
        printf("Opcao invalida/n");

       }
    }while (op!=0);
   
    return 0;
}