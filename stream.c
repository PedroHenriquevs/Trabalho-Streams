#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct ArvProg{
    char nomeProg[100];
    char periodo[100];
    char hora_inicio[100];
    bool ao_vivo;
    char nome_apresent[100];
    struct ArvProg *esq;
    struct ArvProg *dir;
}ArvProg;

typedef struct ListaCat{
    char tipo[100];
    char nomecat[100];
    struct ListaCat *prox;
    struct ArvProg *prog;
}ListaCat;

typedef struct nostream{
    char nome[100];
    char site [100];
    struct ListaCat *cat;
    struct nostream *esq;
    struct nostream *direita;
}nostream;

typedef struct histTrabstream{
    char nomeStream[100];
    char data_inicio[100];
    char data_termino[100];
    struct histTrabstream *prox;
    struct histTrabstream *ant;
}HistStream;

typedef struct ListaApr{
    char nomeapresent[100];
    char cattrab[100];
    char streamtrabalha[100];
    struct HistStream *streamhist;
    struct ListaApr *prox;
    struct ListaApr *ant;
}ListaApr;

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
    }
    int cmp = strcmp(nome, raiz -> nome);
    if(cmp < 0){
        raiz -> esq = inserirstream( raiz ->esq, nome, site);
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
    novo->prog = NULL;
    ListaCat *anterior = NULL;

    if(lista == NULL){
        novo->prox = novo;
        printf("Categoria adicionada com sucesso!\n");
        return novo;
    }
    ListaCat *atual = lista;
    do{
        if(strcmp(novo->nomecat, atual->nomecat) == 0){
            printf("Erro: Categoria '%s' ja existe.\n", novo->nomecat);
            free(novo);
            return lista;
        }  
    
        if(strcmp(novo->nomecat, atual->nomecat) < 0){
            break;
        }
        anterior = atual;
        atual = atual->prox;

    }while(atual != lista);

    if(anterior == NULL){
        ListaCat *ultimo = lista;
        while(ultimo->prox != lista){
            ultimo = ultimo->prox;
        }
        novo->prox = lista;
        ultimo->prox = novo;
        return novo;
    }

    if(atual != lista){
        anterior->prox = novo;
        novo->prox = atual;
        printf("[MEIO] Categoria adicionada: %s\n", novo->nomecat);
        return lista;
    }

    
    anterior->prox = novo;
    novo->prox = lista;
    printf("[FIM] Categoria adicionada: %s\n", novo->nomecat);
    return lista;
}

nostream *BuscaStream(nostream *arvstream, char *nome){
    if(arvstream == NULL || strcmp(nome, arvstream->nome) == 0){
        return arvstream;
    }
    if(strcmp(nome, arvstream->nome) < 0){
        return BuscaStream(arvstream->esq, nome);
    }else{
        return BuscaStream(arvstream->direita, nome);
    }
}

ListaCat *buscarcategoria(ListaCat *lista, char *nomecat){
    if(lista == NULL){
        return NULL;
    }
    ListaCat *atual = lista;
    do{
        if(strcmp(atual->nomecat, nomecat) == 0){
            return atual;
        }
        atual=atual->prox;
    }while(atual != lista);
    return NULL;
}

void mostrarcategoriaStream(nostream *stream, char *nomestream){
    nostream *noStream = BuscaStream(stream, nomestream);
    if(noStream == NULL){
        printf("Stream nao encontrada.\n");
        return;
    }
    ListaCat *lista = noStream->cat;
    if (lista == NULL){
        printf("\nO stream *%s* nao possui categorias cadastradas.\n", nomestream);
        return;
    }
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

ArvProg *criarprograma(char *nome, char *periodo, char *hora, bool vivo, char *apresentador){
    ArvProg *novo= (ArvProg*) malloc (sizeof(ArvProg));
    if(novo == NULL){
        printf("erro ao alocar");
        exit(1);
    }
    strcpy(novo->nomeProg, nome);
    strcpy(novo->periodo, periodo);
    strcpy(novo->hora_inicio, hora);
    novo->ao_vivo = vivo;
    strcpy(novo->nome_apresent, apresentador);
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void inserirprograma(ArvProg **raiz, char *nome, char *periodo, char *hora, bool vivo, char *apresentador){
    if(*raiz == NULL){
      *raiz = criarprograma(nome, periodo, hora, vivo, apresentador);
      return;
    }
    ArvProg *atual = *raiz;
    int cmp = strcmp(nome, atual->nomeProg);
    if(cmp < 0){
        inserirprograma(&atual->esq, nome, periodo, hora, vivo, apresentador);
    }else if(cmp > 0){
        inserirprograma(&atual->dir, nome, periodo, hora, vivo, apresentador);
    }else{
        printf("Programa '%s' ja cadastrado nesta categoria\n", nome);
    }
}

void mostrarProgramas(ArvProg *raiz){
    if(raiz != NULL){
        mostrarProgramas(raiz->esq);
        printf("Programa: %s\n", raiz->nomeProg);
        printf("Periodo: %s\n", raiz->periodo);
        printf("Horario: %s\n", raiz->hora_inicio);
        printf("Apresentador: %s\n", raiz->nome_apresent);
        printf("Ao Vivo: %s\n", raiz->ao_vivo ? "Sim" : "Nao");
        mostrarProgramas(raiz->dir);
    }
}

void mostrarprog_por_filtro(ArvProg*raiz, char *dia, char *hora, char* nome_categoria){
      if(raiz == NULL){
        return;
      }
      mostrarprog_por_filtro(raiz->esq, dia, hora, nome_categoria);
      if(strcmp(raiz->periodo, dia)== 0 && strcmp(raiz->hora_inicio, hora) == 0){
        printf("  - Programa: %s (Categoria: %s)\n", raiz->nomeProg, nome_categoria);
      }
    mostrarprog_por_filtro(raiz->dir, dia, hora, nome_categoria);
}

void buscarProgramasNaStream(nostream* streambuscada, char *dia, char *hora){
    if(streambuscada == NULL){
        printf("Stream nao encontrada.\n");
        return;
    }
    if(streambuscada->cat == NULL){
        printf("Stream nao possui categorias.\n");
        return;
    }
    ListaCat*categoriaatual = streambuscada->cat;
    do{
        mostrarprog_por_filtro(categoriaatual->prog, dia, hora, categoriaatual->nomecat);
        categoriaatual = categoriaatual->prox;
    }while(categoriaatual != streambuscada->cat);
}

void mostrarprogpordia(ArvProg *raiz, char *dia){
    if(raiz == NULL){
        return;
    }
    mostrarprogpordia(raiz->esq, dia);
    if(strcmp(raiz->periodo, dia) == 0){
        printf("pograma: %s (hora: %s - apresentador:%s)\n", raiz->nomeProg, raiz->hora_inicio, raiz->nome_apresent);
    }
    mostrarprogpordia(raiz->dir, dia);
}

ListaApr *criarListaApr(){
    return NULL;
}

ListaApr *adicionarApr(ListaApr *listaApr, char *nome, char *categoria, char *stream){
    ListaApr *novo= (ListaApr *) malloc(sizeof(ListaApr));
    strcpy(novo->nomeapresent, nome);
    strcpy(novo->cattrab,categoria);
    strcpy(novo->streamtrabalha, stream);
    novo->streamhist = NULL;
    if(listaApr == NULL){
        novo->prox = novo;
        novo->ant= novo;
        printf("Apresentador *%s* adicionado com sucesso! \n", nome);
        return novo;
    }
    ListaApr *atual = listaApr;
    do{
        if(strcmp(novo->nomeapresent, atual->nomeapresent) == 0){
            printf("Erro: Apresentador '%s' ja existe.\n", nome);
            free(novo);
            return listaApr;
        }
        if(strcmp(novo->nomeapresent, atual->nomeapresent)< 0){
            break;
        }
        atual = atual->prox;
    }while(atual != listaApr);
    ListaApr *anterior = atual->ant;
    novo->prox = atual;
    anterior->prox = novo;
    novo->ant = anterior;
    atual->ant = novo;
    printf("Apresentador *%s* adicionado com sucesso! \n", nome);
    if (strcmp(novo->nomeapresent, listaApr->nomeapresent) < 0){
        return novo;
    }
    return listaApr;
}

void mostrarapresentador_stream(ListaApr *lista, char* stream){
    if(lista == NULL){
        printf("nenhum apresentador cadastrado.\n");
        return;
    }
    ListaApr *atual = lista;
    int encontrou = 0;
    do{
        if(strcmp(atual->streamtrabalha, stream) == 0){
            if(!encontrou){
            printf("apresentadores que trabalham na stream *%s*:\n", stream);
            encontrou = 1;
            }
            printf("nome; %s - categoria: %s\n", atual->nomeapresent, atual->cattrab);
        }
        atual = atual->prox;
    }while(atual != lista);
    if(!encontrou){
        printf("nenhum apresentador encontrado para a stream *%s*.\n", stream);
    }
}

void mostrarStreamsporCategoria(nostream *streams, char *tipocategoria){

    if(streams != NULL){
        mostrarStreamsporCategoria(streams->esq, tipocategoria);
        
        ListaCat *lista = streams->cat;
        
        if(lista!= NULL){
            ListaCat *atual = lista;
            do{
                if(strcmp(atual->tipo, tipocategoria) == 0){
                    printf("-> %s\n", streams->nome);
                }
                atual= atual->prox;
            }while(atual != lista);
           
            mostrarStreamsporCategoria(streams->direita, tipocategoria);
        }


    }
}

void mostrarApresentadorporCategoria(ListaApr *apresentadores, char *categoria){

    if(apresentadores == NULL){
        printf("Sem apresentadores cadastrados");
        return;

    }

    int achado = 0;
    ListaApr *inicio = apresentadores;
    do{
        if(strcmp(apresentadores->cattrab, categoria)==0){
            printf("-> %s\n", apresentadores->nomeapresent);
            achado = 1;
        }
        apresentadores=apresentadores->prox;
    }
    while(apresentadores != inicio);

    if(!achado){
        printf("Sem apresentadores para essa categoria\n");
    } 
}


ListaCat *removercategoria(ListaCat *lista, char *nome){
    if(lista == NULL){
        printf("Nao existe categoria para remover\n");
        return NULL;
    }

    ListaCat *atual = lista;
    ListaCat *anterior = NULL;

    // procurar a categoria
    do {
        if(strcmp(atual->nomecat, nome) == 0){
            break;
        }
        anterior = atual;
        atual = atual->prox;
    } while(atual != lista);

    // nao encontrou
    if(strcmp(atual->nomecat, nome) != 0){
        printf("Categoria nao encontrada\n");
        return lista;
    }

    // verificar se tem programa cadastrado
    if(atual->prog != NULL){
        printf("Nao eh possivel remover categoria com programa cadastrado\n");
        return lista;
    }

    // caso unico no na lista
    if(atual->prox == atual){
        free(atual);
        printf("Categoria removida (lista ficou vazia)\n");
        return NULL;
    }

    // caso seja o primeiro (cabeça da lista)
    if(atual == lista){
        // achar o ultimo pra manter circularidade
        ListaCat *ultimo = lista;
        while(ultimo->prox != lista){
            ultimo = ultimo->prox;
        }
        lista = atual->prox;   // novo inicio
        ultimo->prox = lista;  // ultimo aponta pro novo inicio
        free(atual);
        printf("Categoria removida (era a primeira)\n");
        return lista;
    }

    // caso meio ou fim
    anterior->prox = atual->prox;
    free(atual);
    printf("Categoria removida\n");
    return lista;
}


int buscarprog_por_apresentador(ArvProg*raiz, char* nome_apresent){
     if(raiz == NULL){
        return 0;
     }
     if(strcmp(raiz->nome_apresent, nome_apresent)== 0){
        return 1;
     }
     return buscarprog_por_apresentador(raiz->esq, nome_apresent) || buscarprog_por_apresentador(raiz->dir, nome_apresent);
}

int apresentador_prog_stream(nostream *streamalvo, char* nome_apresent){
     if(streamalvo == NULL || streamalvo-> cat == NULL){
        return 0;
     }
    // percorrer a lista de cat da stream
     ListaCat *cat_atual = streamalvo->cat;
     do{
        if(buscarprog_por_apresentador(cat_atual->prog, nome_apresent)){
            return 1;
        }
        cat_atual = cat_atual->prox;
     }while(cat_atual != streamalvo->cat);
     return 0;
}

void mostrardadosPrograma(nostream *stream, char *nomeprograma){
    if(stream != NULL){
        mostrardadosPrograma(stream->esq, nomeprograma);
        ListaCat *lista = stream->cat;
        if(lista!=NULL){
            ListaCat*atual =lista;
            do{
                ArvProg *prog_atual = atual->prog;
                if(prog_atual != NULL){
                    if(strcmp(prog_atual->nomeProg, nomeprograma) == 0){
                        printf("Programa: %s\n", prog_atual->nomeProg);
                        printf("Periodo: %s\n", prog_atual->periodo);
                        printf("Horario: %s\n", prog_atual->hora_inicio);
                        printf("Apresentador: %s\n", prog_atual->nome_apresent);
                        printf("Ao Vivo: %s\n", prog_atual->ao_vivo ? "Sim" : "Nao");
                    }
                    
                }
                atual = atual->prox;

            }while (atual != lista);
        }else{
            printf("A stream nao possui categorias cadastradas\n");
        }
    }else{
        printf("não possui streams cadastradas\n");
    }
}

ArvProg *Removerprograma(ArvProg **raiz, char *nome){
    if(*raiz != NULL){
        int cmp = strcmp(nome, (*raiz)->nomeProg);
        if(cmp < 0){
            (*raiz)->esq = Removerprograma(&(*raiz)->esq, nome);
        }else if(cmp > 0){
            (*raiz)->dir = Removerprograma(&(*raiz)->dir, nome);
        }else{
            // No encontrado
            if((*raiz)->esq == NULL){
                ArvProg *temp = (*raiz)->dir;
                free(*raiz);
                return temp;
            }else if((*raiz)->dir == NULL){
                ArvProg *temp = (*raiz)->esq;
                free(*raiz);
                return temp;
            }
        // No com dois filhos
            ArvProg *temp = (*raiz)->dir;
            while(temp->esq != NULL){
                temp = temp->esq;
            }
            strcpy((*raiz)->nomeProg, temp->nomeProg);
            strcpy((*raiz)->periodo, temp->periodo);
            strcpy((*raiz)->hora_inicio, temp->hora_inicio);
            (*raiz)->ao_vivo = temp->ao_vivo;
            strcpy((*raiz)->nome_apresent, temp->nome_apresent);
            (*raiz)->dir = Removerprograma(&(*raiz)->dir, temp->nomeProg);
        }
        return *raiz;
    }
    return NULL;
}


int main(){
   nostream * raizdastream = NULL;
   ListaApr * listaApresentadores = NULL;
   char nome [100];
   char site [100];
   int op;
   do{
        printf("\nBiblioteca de streams\n");
        printf("1. Cadastrar Stream\n");
        printf("2. Mostrar Todas as Streams\n");
        printf("3. Adicionar Categoria ao Stream\n");
        printf("4. Cadastrar Apresentador\n");
        printf("5. Cadastrar Programa\n");
        printf("6. Buscar Stream por Nome\n");
        printf("7. Listar Categorias de uma Stream\n");
        printf("8. Listar Programas de uma Categoria\n");
        printf("9. Buscar Programa por Stream, Dia e Hora\n");
        printf("10. Listar streams pelo tipo de categoria:\n");
        printf("11. Listar programa por dia da semana em uma categoria:\n");
        printf("12. Listar apresentadores por stream:\n");
        printf("13. Listar apresentadores por categoria:\n");
        printf("14. Mostrar dados de um programa:\n");
        printf("15. Remover programa de uma categoria:\n");
        printf("16. remover categoria de uma stream:\n");
        printf("17. Alterar stream de um apresentador\n");
        printf("0. Sair\n");
        scanf("%d", &op);
        getchar();
       switch (op){
        case 1:{
            printf("Digite o nome do stream:\n");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;
            printf("Digite o site da stream:\n");
            fgets(site, sizeof(site), stdin);
            site[strcspn(site, "\n")] = 0;
            raizdastream = inserirstream(raizdastream, nome, site);
            break;
        }
        case 2:{
            printf("Streams Cadastradas\n");
            if(raizdastream == NULL){
                 printf("Nenhuma stream cadastrada.\n");
            }else{
                mostrarstream(raizdastream);
            }
            break;
        }
        case 3:{
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
            }else{
                printf("Stream nao cadastrada\n");
            }
            break;
        }
        case 4:{
            char nome_apr[100], cat_apr[100], stream_apr[100];
            printf("Nome do apresentador: \n");
            fgets(nome_apr, sizeof(nome_apr), stdin);
            nome_apr[strcspn(nome_apr, "\n")] = 0;
            printf("Categoria que trabalha: \n");
            fgets(cat_apr, sizeof(cat_apr), stdin);
            cat_apr[strcspn(cat_apr, "\n")] = 0;
            printf("Stream que trabalha atualmente: \n");
            fgets(stream_apr, sizeof(stream_apr), stdin);
            stream_apr[strcspn(stream_apr, "\n")] = 0;
            if(BuscaStream(raizdastream, stream_apr) == NULL){
                printf("Erro: A stream '%s' nao existe.\n", stream_apr);
                break;
            }
            listaApresentadores = adicionarApr(listaApresentadores, nome_apr, cat_apr, stream_apr);
            break;
        }
        case 5:{
            char nome_stream_prog[100];
            char nome_categoria_prog[100];
            printf("Digite o nome da stream para adicionar o programa: ");
            fgets(nome_stream_prog, sizeof(nome_stream_prog), stdin);
            nome_stream_prog[strcspn(nome_stream_prog, "\n")] = 0;
            nostream* streamencontrada = BuscaStream(raizdastream, nome_stream_prog);
            if(streamencontrada == NULL){
               printf("Stream nao encontrada.\n");
               break;
            }
            printf("Digite o nome da categoria para adicionar o programa: ");
            fgets(nome_categoria_prog, sizeof(nome_categoria_prog), stdin);
            nome_categoria_prog[strcspn(nome_categoria_prog, "\n")] = 0;
            ListaCat *categoriaencontrada = buscarcategoria(streamencontrada->cat, nome_categoria_prog);
            if(categoriaencontrada == NULL){
                 printf("Categoria nao encontrada.\n");
               break;
            }
            char nomeProg[100], periodo[100], hora[100], apresentador[100];
            int vivo_op;
            bool ao_vivo_status;
            printf("Digite o nome do programa: ");
            fgets(nomeProg, sizeof(nomeProg), stdin);
            nomeProg[strcspn(nomeProg, "\n")] = 0;
            printf("Digite o periodo do programa: ");
            fgets(periodo, sizeof(periodo), stdin);
            periodo[strcspn(periodo, "\n")] = 0;
            printf("Digite a hora de inicio do programa: ");
            fgets(hora, sizeof(hora), stdin);
            hora[strcspn(hora, "\n")] = 0;
            printf("Digite o nome do apresentador: ");
            fgets(apresentador, sizeof(apresentador), stdin);
            apresentador[strcspn(apresentador, "\n")] = 0;
            printf("O programa eh ao vivo? (1 para sim, 0 para nao): ");
            scanf("%d", &vivo_op);
            getchar();
            ao_vivo_status = (vivo_op == 1);
            inserirprograma(&categoriaencontrada->prog, nomeProg, periodo, hora, ao_vivo_status, apresentador);
            printf("Programa cadastrado com sucesso!\n");
            break;
        }
        case 6:{
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
            }else{
                printf("\n Stream nao encontrado! \n");
            }
            break;
        }
        case 7:{
            char nomeStreamCat[100];
            printf("Nome stream: \n");
            fgets(nomeStreamCat, sizeof(nomeStreamCat), stdin);
            nomeStreamCat[strcspn(nomeStreamCat, "\n")] = 0;
            mostrarcategoriaStream(raizdastream, nomeStreamCat);
            break;
        }
        case 8:{
            char nome_stream_list[100];
            char nome_cat_list[100];
            printf("Digite o nome da stream: ");
            fgets(nome_stream_list, sizeof(nome_stream_list), stdin);
            nome_stream_list[strcspn(nome_stream_list, "\n")] = 0;
            nostream* s_encontrada = BuscaStream(raizdastream, nome_stream_list);
            if(s_encontrada == NULL){
               printf("Stream nao encontrada.\n");
               break;
            }
            printf("Digite o nome da categoria para listar os programas: ");
            fgets(nome_cat_list, sizeof(nome_cat_list), stdin);
            nome_cat_list[strcspn(nome_cat_list, "\n")] = 0;
            ListaCat* c_encontrada = buscarcategoria(s_encontrada->cat, nome_cat_list);
            if(c_encontrada == NULL){
                 printf("Categoria nao encontrada.\n");
               break;
            }
            printf("\n Programas da Categoria '%s'\n", nome_cat_list);
            if(c_encontrada->prog == NULL){
                printf("Nenhum programa cadastrado nesta categoria.\n");
            }else{
                mostrarProgramas(c_encontrada->prog);
            }
            break;
        }
        case 9:{
            char nome_stream_busca[100];
            char dia_busca[100];
            char hora_busca[100];
            printf("digite o nome da stream:\n");
            fgets(nome_stream_busca, sizeof(nome_stream_busca), stdin);
            nome_stream_busca[strcspn(nome_stream_busca, "\n")] = 0;
            nostream *streamencontrada = BuscaStream(raizdastream, nome_stream_busca);
            if(streamencontrada == NULL){
                printf("stream nao encontrada\n");
                break;
            }
            printf("digite o dia do programa:\n");
            fgets(dia_busca, sizeof(dia_busca), stdin);
            dia_busca[strcspn(dia_busca, "\n")] = 0;
            printf("digite o horario de inicio: \n");
            fgets(hora_busca, sizeof(hora_busca), stdin);
            hora_busca[strcspn(hora_busca, "\n")] = 0;
            printf("Programas em '%s' no dia '%s' as '%s'\n", nome_stream_busca, dia_busca, hora_busca);
            buscarProgramasNaStream(streamencontrada, dia_busca, hora_busca);
            break;
        }

          case 10:{
            char tipoBusca[100];
            printf("Tipo da categoria: ");
            fgets(tipoBusca, sizeof(tipoBusca), stdin);
            tipoBusca[strcspn(tipoBusca, "\n")] = 0;
            printf("Tipo de categoria presente nas streams: \n");
            mostrarStreamsporCategoria(raizdastream, tipoBusca);
            break;
        }

        case 11:{
            char nome_stream[100];
            char nome_busca[100];
            char dia_busca[100];
            printf("Digite  o nome da stream:\n");
            fgets(nome_stream, sizeof(nome_stream), stdin);
            nome_stream[strcspn(nome_stream, "\n")] = 0;
            nostream*stream_enc = BuscaStream(raizdastream, nome_stream);
            if(stream_enc == NULL){
                printf("Stream nao encontrada\n");
                break;
            }
            printf("digite onome da categoria:\n");
            fgets(nome_busca, sizeof(nome_busca), stdin);
            nome_busca[strcspn(nome_busca, "\n")] = 0;
            ListaCat* categoria_enc = buscarcategoria(stream_enc->cat, nome_busca);
            if(categoria_enc == NULL){
                printf("Categoria nao encontrada\n");
                break;
            }
            printf("digite o dia da semana:\n");
            fgets(dia_busca, sizeof(dia_busca), stdin);
            dia_busca[strcspn(dia_busca, "\n")] = 0;
            printf("programas na categoria %s no dia %s: \n", nome_busca, dia_busca);
            mostrarprogpordia(categoria_enc->prog, dia_busca);
            break;
        }
        case 12:{
            char nome_stream_busca[100];
            printf("digite o nome da stream:\n");
            fgets(nome_stream_busca, sizeof(nome_stream_busca), stdin);
            nome_stream_busca[strcspn(nome_stream_busca, "\n")] =0;
            if(BuscaStream(raizdastream, nome_stream_busca) == NULL){
                printf("stream nao encontrada\n");
                break;
            }
            mostrarapresentador_stream(listaApresentadores, nome_stream_busca);
            break;
        }
         case 13:{
            char nomecategoria[100];
            printf("Digite o nome categoria: ");
            fgets(nomecategoria, sizeof(nomecategoria), stdin);
            nomecategoria[strcspn(nomecategoria, "\n")] = 0;
            mostrarApresentadorporCategoria(listaApresentadores, nomecategoria);
            break;

        }

         case 14:{
            char nomeprograma[100];
            printf("Digite o nome do programa: ");
            fgets(nomeprograma, sizeof(nomeprograma), stdin);
            nomeprograma[strcspn(nomeprograma, "\n")] = 0;
            mostrardadosPrograma(raizdastream, nomeprograma);
            break;
        }

        case 15:{
            char nomestream[100];
            char nomecategoria[100];
            char nomeprograma[100];
            printf("Digite o nome da stream: ");
            fgets(nomestream, sizeof(nomestream), stdin);
            nomestream[strcspn(nomestream, "\n")] = 0;
            nostream* streamencontrada = BuscaStream(raizdastream, nomestream);
            if(streamencontrada == NULL){
                printf("stream nao encontrada.\n");
                break;
            }
            printf("Digite o nome da categoria: ");
            fgets(nomecategoria, sizeof(nomecategoria), stdin);
            nomecategoria[strcspn(nomecategoria, "\n")] = 0;
            ListaCat* categoriaencontrada = buscarcategoria(streamencontrada->cat, nomecategoria);
            if(categoriaencontrada == NULL){
                printf("categoria nao encontrada.\n");
                break;
            }
            printf("Digite o nome do programa a ser removido: ");
            fgets(nomeprograma, sizeof(nomeprograma), stdin);   
            nomeprograma[strcspn(nomeprograma, "\n")] = 0;
            categoriaencontrada->prog = Removerprograma(&categoriaencontrada->prog, nomeprograma);
            printf("Programa removido com sucesso.\n");
            break;
        }
        case 16:{
            char nomestream_remove[100];
            char nomecategoria_remove[100];
            printf("Digite o nome da stream: ");
            fgets(nomestream_remove, sizeof(nomestream_remove), stdin);
            nomestream_remove[strcspn(nomestream_remove, "\n")] = 0;
            nostream* streamencontrada = BuscaStream(raizdastream, nomestream_remove);
            if(streamencontrada == NULL){
                printf("stream nao encontrada.\n");
                break;
            }
            printf("digite o nome da categoria a ser removida: ");
            fgets(nomecategoria_remove, sizeof(nomecategoria_remove), stdin);
            nomecategoria_remove[strcspn(nomecategoria_remove, "\n")] = 0;
            streamencontrada->cat = removercategoria(streamencontrada->cat, nomecategoria_remove);
            break;
        }
        case 17:{
            char nome_apresentador[100];
            char novastream[100];
            printf("digite o nome do apresentador que deseja alterar a stream: ");
            fgets(nome_apresentador, sizeof(nome_apresentador), stdin);
            nome_apresentador[strcspn(nome_apresentador, "\n")] = 0;
            
            ListaApr* apresentador = NULL;
            if (listaApresentadores != NULL) {
                ListaApr* atual = listaApresentadores;
                do {
                    if (strcmp(atual->nomeapresent, nome_apresentador) == 0) {
                        apresentador = atual;
                        break;
                    }
                    atual = atual->prox;
                } while (atual != listaApresentadores);
            }

            if(apresentador == NULL){
                printf("apresentador nao encontrado\n");
                break;
            }
            char streamantiga[100];
            strcpy(streamantiga, apresentador->streamtrabalha);
            printf("digite o nome da nova stream: ");
            fgets(novastream, sizeof(novastream), stdin);
            novastream[strcspn(novastream, "\n")] = 0;
            nostream* nova_stream = BuscaStream(raizdastream, novastream);
            if(nova_stream == NULL){
                printf("stream nao encontrada\n");
                break;
            }
            nostream* stream_antiga = BuscaStream(raizdastream, streamantiga);
            if(apresentador_prog_stream(stream_antiga, nome_apresentador)){
                printf("apresentador possui programas na stream atual\n");
                break;
            }
            strcpy(apresentador->streamtrabalha, novastream);
            printf("stream do apresentador alterada com sucesso\n");
            break;
        }
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida/n");
       }
    }while (op!=0);
    return 0;
}