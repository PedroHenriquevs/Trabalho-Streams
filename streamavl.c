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
    struct DiaSemana *dias;
    struct ArvProg *esq;
    struct ArvProg *dir;
    int altura;
}ArvProg;

typedef struct DiaSemana{
    char dia[9];
    struct DiaSemana *prox;

}DiaSemana;

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
    int altura;
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
    HistStream *streamhist;
    struct ListaApr *prox;
    struct ListaApr *ant;
}ListaApr;


int altura(ArvProg*no){
    if(no == NULL){
        return -1; }
    return no->altura;
}

int alturastream(nostream*no){
    if(no == NULL){
        return -1; 
    }
    return no->altura;
}

int ponto(int a, int b){
    return (a > b) ? a : b;
}

int fb(ArvProg*no){
    if(no == NULL){
        return 0;
    }
    return altura(no->esq) - altura(no->dir);
}

int fb_stream(nostream*no){
    if(no == NULL){
        return 0;
    }
    return alturastream(no->esq) - alturastream(no->direita);
}


// rotacao simples direita
nostream* rotacaodireita(nostream* raiz){
    nostream* novaraiz = raiz->esq;
    raiz->esq = novaraiz->direita;
    novaraiz->direita = raiz;

    //atualiza alturas
    raiz->altura = ponto(alturastream(raiz->esq), alturastream(raiz->direita)) + 1;
    novaraiz->altura = ponto(alturastream(novaraiz->esq), alturastream(novaraiz->direita)) + 1;

    return novaraiz;
}
// rotacao simples esquerda
nostream* rotacaoesquerda(nostream *raiz){
    nostream *nova_raiz = raiz->direita;
    raiz->direita = nova_raiz->esq;
    nova_raiz->esq = raiz;

    // atualiza as alturas
    raiz->altura = ponto(alturastream(raiz->esq), alturastream(raiz->direita)) + 1;
    nova_raiz->altura = ponto(alturastream(nova_raiz->esq), alturastream(nova_raiz->direita)) + 1;

    return nova_raiz;
}

// rotacao dupla direita
nostream* rotacaodupladireita(nostream* raiz){
    raiz->esq = rotacaoesquerda(raiz->esq);
    return rotacaodireita(raiz);
}

// rotacao dupla esquerda
nostream* rotacaoduplaesquerda(nostream* raiz){
    raiz->direita = rotacaodireita(raiz->direita);
    return rotacaoesquerda(raiz);
}

nostream* balancearstream(nostream*raiz){
    int fator_balanceamento = fb_stream(raiz);

     if(fator_balanceamento > 1){
        if(fb_stream(raiz->esq) >= 0){
            //rotacao simples direita
            return rotacaodireita(raiz);
     }else{
            //rotacao dupla direita
            return rotacaodupladireita(raiz);
        }
    }

    if(fator_balanceamento < -1){
        if(fb_stream(raiz->direita) <= 0){
            //rotacao simples esquerda
            return rotacaoesquerda(raiz);
        }else{
            //rotacao dupla esquerda
            return rotacaoduplaesquerda(raiz);
        }
    }
    return raiz;
}



ArvProg* rotacaodireitaprog(ArvProg* raiz){
    ArvProg* novaraiz = raiz->esq;
    raiz->esq = novaraiz->dir;
    novaraiz->dir = raiz;

    //atualiza alturas
    raiz->altura = ponto(altura(raiz->esq), altura(raiz->dir)) + 1;
    novaraiz->altura = ponto(altura(novaraiz->esq), altura(novaraiz->dir)) + 1;

    return novaraiz;
}

ArvProg* rotacaoesquerdaprog(ArvProg* raiz){
    ArvProg* nova_raiz = raiz->dir;
    raiz->dir = nova_raiz->esq;
    nova_raiz->esq = raiz;

    // atualiza as alturas
    raiz->altura = ponto(altura(raiz->esq), altura(raiz->dir)) + 1;
    nova_raiz->altura = ponto(altura(nova_raiz->esq), altura(nova_raiz->dir)) + 1;

    return nova_raiz;
}

ArvProg* rotacaodupladireitaprog(ArvProg* raiz){
    raiz->esq = rotacaoesquerdaprog(raiz->esq);
    return rotacaodireitaprog(raiz);
}

ArvProg* rotacaoduplaesquerdaprog(ArvProg* raiz){
    raiz->dir = rotacaodireitaprog(raiz->dir);
    return rotacaoesquerdaprog(raiz);
}

ArvProg* balancearprog(ArvProg*raiz){
    int fator_balanceamento = fb(raiz);

     if(fator_balanceamento > 1){
        if(fb(raiz->esq) >= 0){
            //rotacao simples direita
            return rotacaodireitaprog(raiz);
     }else{
            //rotacao dupla direita
            return rotacaodupladireitaprog(raiz);
        }
    }

    else if(fator_balanceamento < -1){
        if(fb(raiz->dir) <= 0){
            //rotacao simples esquerda
            return rotacaoesquerdaprog(raiz);
        }else{
            //rotacao dupla esquerda
            return rotacaoduplaesquerdaprog(raiz);
        }
    }
    return raiz;
}



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
    novo->altura = 0;
    return novo;
}

nostream *inserirStreamAVL(nostream *raiz, char *nome, char *site){
    if(raiz == NULL){
         return criarstream(nome, site);
    }
    int cmp = strcmp(nome, raiz -> nome);
    if(cmp < 0){
        raiz -> esq = inserirStreamAVL( raiz ->esq, nome, site);
    }else if(cmp > 0){
        raiz -> direita = inserirStreamAVL( raiz -> direita, nome, site);
    }else{
        printf("stream *%s* ja existente na base de dados.\n", nome);
        return raiz;
    }

    //atualiza altura
    raiz->altura = ponto(alturastream(raiz->esq), alturastream(raiz->direita)) + 1;
    //balanceia a arvore
    raiz = balancearstream(raiz);

    return raiz;
}

void mostrarstream(nostream*raiz){
    if(raiz !=NULL){
        mostrarstream(raiz->esq);
        printf("---------------------\n");
        printf("Nome: %s\n", raiz-> nome);
        printf("Site: %s\n", raiz->site);
        printf("-----------------------\n");
        mostrarstream(raiz->direita);
    }
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
        printf("Categoria adicionada: %s\n", novo->nomecat);
        return lista;
    }

    
    anterior->prox = novo;
    novo->prox = lista;
    printf("Categoria adicionada: %s\n", novo->nomecat);
    return lista;
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
    novo->altura = 0; 
    novo->dias = NULL;
    return novo;
}

DiaSemana *adicionaDiadasemana(ArvProg *programa) {
    int numDias;
    printf("Quantos dias da semana o programa sera exibido? ");
    scanf("%d", &numDias);
    getchar(); 

    printf("Digite os dias da semana (ex: Segunda, Terca, ...):\n");

    for (int i = 0; i < numDias; i++) {
        DiaSemana *novo = (DiaSemana *) malloc(sizeof(DiaSemana));
        if (novo == NULL) {
            printf("Erro ao alocar memoria para o dia da semana.\n");
            return programa->dias; // retorna o que já foi adicionado
        }

        printf("Dia %d: ", i + 1);
        fgets(novo->dia, sizeof(novo->dia), stdin);
        novo->dia[strcspn(novo->dia, "\n")] = '\0'; // remover \n
        
        
        // insere no início da lista
        novo->prox = programa->dias;
        programa->dias = novo;
    }

    return programa->dias;
}

void MostrarDiasSemana(ArvProg *programa) {
    if (programa == NULL || programa->dias == NULL) {
        printf("Nenhum dia da semana cadastrado para este programa.\n");
        return;
    }

    printf("Dias da semana em que o programa '%s' sera exibido:\n", programa->nomeProg);
    DiaSemana *atual = programa->dias;
    while (atual != NULL) {
        printf("- %s\n", atual->dia);
        atual = atual->prox;
    }
}


ArvProg *inserirProgramaAVL(ArvProg **raiz, char *nome, char *periodo, char *hora, bool vivo, char *apresentador){
    if(*raiz == NULL){
      return criarprograma(nome, periodo, hora, vivo, apresentador);
    }

    int cmp = strcmp(nome, (*raiz)->nomeProg);
    if(cmp < 0){
        (*raiz)->esq = inserirProgramaAVL(&(*raiz)->esq, nome, periodo, hora, vivo, apresentador);
    }else if(cmp > 0){
        (*raiz)->dir = inserirProgramaAVL(&(*raiz)->dir, nome, periodo, hora, vivo, apresentador);
    }else{
        printf("Programa '%s' ja cadastrado nesta categoria\n", nome);
        return *raiz;
    }
    //atualiza altura
    (*raiz)->altura = ponto(altura((*raiz)->esq), altura((*raiz)->dir)) + 1;
    //balanceia a arvore
    *raiz = balancearprog(*raiz);

    return *raiz;
}

void mostrarProgramas(ArvProg *raiz){
    if(raiz != NULL){
        mostrarProgramas(raiz->esq);
        printf("Programa: %s\n", raiz->nomeProg);
        printf("Periodo: %s\n", raiz->periodo);
        printf("Horario: %s\n", raiz->hora_inicio);
        MostrarDiasSemana(raiz);
        printf("Apresentador: %s\n", raiz->nome_apresent);
        printf("Ao Vivo: %s\n", raiz->ao_vivo ? "Sim" : "Nao");
        printf("-----------------------\n");
        mostrarProgramas(raiz->dir);
    }
}

void mostrarprog_por_filtro(ArvProg*raiz, char *dia, char *hora, char* nome_categoria){
    if(raiz == NULL){
        return;
    }

    mostrarprog_por_filtro(raiz->esq, dia, hora, nome_categoria);
    DiaSemana *atual = raiz->dias;
    while (atual != NULL) {
        if (strcmp(atual->dia, dia) == 0 && strcmp(raiz->hora_inicio, hora) == 0) {
            printf("  - Programa: %s\n", raiz->nomeProg);
            printf("    Categoria: %s\n", nome_categoria);
            printf("    Hora: %s\n", raiz->hora_inicio);
            printf("    Apresentador: %s\n", raiz->nome_apresent);
            printf("    Ao Vivo: %s\n", raiz->ao_vivo ? "Sim" : "Nao");
        }
        atual = atual->prox;
    }
    mostrarprog_por_filtro(raiz->dir, dia, hora, nome_categoria);
}


void buscarProgramasNaStream(nostream *streambuscada, char *dia, char *hora){
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
    DiaSemana *atual = raiz->dias;
    while (atual != NULL) {
        if (strcmp(atual->dia, dia) == 0) {
            printf("  - Programa: %s\n", raiz->nomeProg);
            printf("    Hora: %s\n", raiz->hora_inicio);
            printf("    Apresentador: %s\n", raiz->nome_apresent);
            printf("    Ao Vivo: %s\n", raiz->ao_vivo ? "Sim" : "Nao");
            printf("    Periodo: %s\n", raiz->periodo);
            printf("    Dias da Semana:\n");
            MostrarDiasSemana(raiz);
        }
        atual = atual->prox;
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
            printf("nome: %s - categoria: %s\n", atual->nomeapresent, atual->cattrab);
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
        }

        mostrarStreamsporCategoria(streams->direita, tipocategoria);
    }
}

void mostrarApresentadorporCategoria(ListaApr *apresentadores, char *categoria){
    if(apresentadores == NULL){
        printf("Sem apresentadores cadastrados\n");
        return;
    }
    int achado = 0;
    ListaApr *inicio = apresentadores;
    do{
        if(strcmp(apresentadores->cattrab, categoria)==0){
            if(!achado){
                printf("Apresentadores da categoria '%s':\n", categoria);
                achado = 1;
            }
            printf("-> %s\n", apresentadores->nomeapresent);
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
    if(stream == NULL){
        return;
    }
    mostrardadosPrograma(stream->esq, nomeprograma);

    ListaCat *lista = stream->cat;
    if(lista != NULL){
        ListaCat*atual =lista;
        do{
            ArvProg *prog_atual = atual->prog;
            
            while(prog_atual != NULL){
                 if(strcmp(prog_atual->nomeProg, nomeprograma) == 0){
                    printf("Programa: %s\n", prog_atual->nomeProg);
                    printf("Periodo: %s\n", prog_atual->periodo);
                    printf("Horario: %s\n", prog_atual->hora_inicio);
                    printf("Apresentador: %s\n", prog_atual->nome_apresent);
                    printf("Ao Vivo: %s\n", prog_atual->ao_vivo ? "Sim" : "Nao");
                    return; 
                }
                if(strcmp(nomeprograma, prog_atual->nomeProg) < 0)
                    prog_atual = prog_atual->esq;
                else
                    prog_atual = prog_atual->dir;
            }
            atual = atual->prox;
        }while (atual != lista);
    }
    mostrardadosPrograma(stream->direita, nomeprograma);
}

HistStream* adicionarHistorico(HistStream* lista, char* streamAntiga, char* inicio, char* termino) {
    HistStream* novo = (HistStream*) malloc(sizeof(HistStream));
    strcpy(novo->nomeStream, streamAntiga);
    strcpy(novo->data_inicio, inicio);
    strcpy(novo->data_termino, termino);
    novo->prox = NULL;
    novo->ant = NULL;

    if (lista == NULL) {
        return novo;
    }
    HistStream* atual = lista;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = novo;
    novo->ant = atual;
    return lista;
}

void mostrarCurriculo(ListaApr* apresentador){
    if (apresentador == NULL) {
        printf("apresentador inexistente.\n");
        return;
    }
    printf("curriculo de %s:\n", apresentador->nomeapresent);
    HistStream* atual = apresentador->streamhist;
    if(atual == NULL){
        printf("sem historico anterior.\n");
        return;
    }
    while(atual != NULL){
        printf(" stream: %s,  inicio: %s termino: %s\n",
               atual->nomeStream, atual->data_inicio, atual->data_termino);
        atual = atual->prox;
    }
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
        printf("15. remover categoria de uma stream:\n");
        printf("16. Alterar stream de um apresentador\n");
        printf("17. Mostrar curriculo de um apresentador\n");
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
            raizdastream = inserirStreamAVL(raizdastream, nome, site);
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
            {
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
            }
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
            // Verifica se o apresentador existe na lista de apresentadores
            ListaApr *apresentador_existente = NULL;
            if (listaApresentadores != NULL) {
                ListaApr *atual_apr = listaApresentadores;
                do {
                    if (strcmp(atual_apr->nomeapresent, apresentador) == 0) {
                        apresentador_existente = atual_apr;
                        break;
                    }
                    atual_apr = atual_apr->prox;
                } while (atual_apr != listaApresentadores);
            }

            if (apresentador_existente == NULL) {
                printf("apresentador '%s' nao cadastrado.\n", apresentador);
            } else {
                inserirProgramaAVL(&categoriaencontrada->prog, nomeProg, periodo, hora, ao_vivo_status, apresentador);
                
                adicionaDiadasemana(categoriaencontrada->prog);
                printf("programa cadastrado com sucesso\n");
            }
            break;
        }
        case 6:{
            printf("Digite o nome da stream a buscar: ");
            char busca[100];
            fgets(busca, sizeof(busca), stdin);
            busca[strcspn(busca, "\n")] = 0;
            nostream *r = BuscaStream(raizdastream, busca);
            if(r == NULL){
                printf("Stream nao encontrada.\n");
            }else{
                printf("Stream encontrada: %s - Site: %s\n", r->nome, r->site);
            }
            break;
        }
        case 7:{
            printf("Digite o nome da stream: ");
            char ns[100];
            fgets(ns, sizeof(ns), stdin);
            ns[strcspn(ns, "\n")] = 0;
            mostrarcategoriaStream(raizdastream, ns);
            break;
        }
        case 8:{
            printf("Digite o nome da stream: ");
            char ns[100];
            fgets(ns, sizeof(ns), stdin);
            ns[strcspn(ns, "\n")] = 0;
            nostream* st = BuscaStream(raizdastream, ns);
            if(st == NULL){
                printf("Stream nao encontrada.\n");
                break;
            }
            printf("Digite o nome da categoria: ");
            char nc[100];
            fgets(nc, sizeof(nc), stdin);
            nc[strcspn(nc, "\n")] = 0;
            ListaCat* cat = buscarcategoria(st->cat, nc);
            if(cat == NULL){
                printf("Categoria nao encontrada.\n");
            }else{
                if(cat->prog == NULL){
                    printf("Nenhum programa cadastrado nessa categoria.\n");
                }else{
                    mostrarProgramas(cat->prog);
                }
            }
            break;
        }
        case 9:{
            printf("Digite o nome da stream: ");
            char ns[100];
            char dia[100], horaq[100];
            fgets(ns, sizeof(ns), stdin);
            ns[strcspn(ns, "\n")] = 0;
            printf("Digite o dia (periodo): ");
            fgets(dia, sizeof(dia), stdin);
            dia[strcspn(dia, "\n")] = 0;
            printf("Digite a hora: ");
            fgets(horaq, sizeof(horaq), stdin);
            horaq[strcspn(horaq, "\n")] = 0;
            nostream* stt = BuscaStream(raizdastream, ns);
            buscarProgramasNaStream(stt, dia, horaq);
            break;
        }
        case 10:{
            printf("Digite o tipo de categoria: ");
            char tp[100];
            fgets(tp, sizeof(tp), stdin);
            tp[strcspn(tp, "\n")] = 0;
            mostrarStreamsporCategoria(raizdastream, tp);
            break;
        }
        case 11:{
            printf("Digite o nome da stream: ");
            char ns[100], nc[100], dia[100];
            fgets(ns, sizeof(ns), stdin);
            ns[strcspn(ns, "\n")] = 0;
            nostream* st = BuscaStream(raizdastream, ns);
            if(st == NULL){
                printf("Stream nao encontrada.\n");
                break;
            }
            printf("Digite o nome da categoria: ");
            fgets(nc, sizeof(nc), stdin);
            nc[strcspn(nc, "\n")] = 0;
            ListaCat* cat = buscarcategoria(st->cat, nc);
            if(cat == NULL){
                printf("Categoria nao encontrada.\n");
                break;
            }
            printf("Digite o dia (periodo): ");
            fgets(dia, sizeof(dia), stdin);
            dia[strcspn(dia, "\n")] = 0;
            mostrarprogpordia(cat->prog, dia);
            break;
        }
        case 12:{
            printf("Digite o nome da stream: ");
            char s[100];
            fgets(s, sizeof(s), stdin);
            s[strcspn(s, "\n")] = 0;
            mostrarapresentador_stream(listaApresentadores, s);
            break;
        }
        case 13:{
            printf("Digite a categoria: ");
            char cat[100];
            fgets(cat, sizeof(cat), stdin);
            cat[strcspn(cat, "\n")] = 0;
            mostrarApresentadorporCategoria(listaApresentadores, cat);
            break;
        }
        case 14:{
            printf("Digite o nome do programa: ");
            char np[100];
            fgets(np, sizeof(np), stdin);
            np[strcspn(np, "\n")] = 0;
            mostrardadosPrograma(raizdastream, np);
            break;
        }
        case 15:{
            printf("Digite o nome da stream: ");
            char ns[100], nc[100];
            fgets(ns, sizeof(ns), stdin);
            ns[strcspn(ns, "\n")] = 0;
            nostream* st = BuscaStream(raizdastream, ns);
            if(st == NULL){
                printf("Stream nao encontrada.\n");
                break;
            }
            printf("Digite o nome da categoria a remover: ");
            fgets(nc, sizeof(nc), stdin);
            nc[strcspn(nc, "\n")] = 0;
            st->cat = removercategoria(st->cat, nc);
            break;
        }
        case 16:{
            printf("Digite o nome do apresentador: ");
            char nome_ap[100], nova_stream[100], data_inicio[100], data_fim[100];
            fgets(nome_ap, sizeof(nome_ap), stdin);
            nome_ap[strcspn(nome_ap, "\n")] = 0;
            // procura apresentador
            if(listaApresentadores == NULL){
                printf("Nenhum apresentador cadastrado.\n");
                break;
            }
            ListaApr* atual = listaApresentadores;
            ListaApr* encontrado = NULL;
            do{
                if(strcmp(atual->nomeapresent, nome_ap) == 0){
                    encontrado = atual;
                    break;
                }
                atual = atual->prox;
            }while(atual != listaApresentadores);

            if(encontrado == NULL){
                printf("Apresentador nao encontrado.\n");
                break;
            }
            printf("Digite a nova stream: ");
            fgets(nova_stream, sizeof(nova_stream), stdin);
            nova_stream[strcspn(nova_stream, "\n")] = 0;
            if(BuscaStream(raizdastream, nova_stream) == NULL){
                printf("Stream '%s' nao existe.\n", nova_stream);
                break;
            }
            
            printf("Digite data de inicio: ");
            fgets(data_inicio, sizeof(data_inicio), stdin);
            data_inicio[strcspn(data_inicio, "\n")] = 0;
            printf("Digite data de termino ou se eh atual: ");
            fgets(data_fim, sizeof(data_fim), stdin);
            data_fim[strcspn(data_fim, "\n")] = 0;

            // adiciona historico com a stream antiga
            encontrado->streamhist = adicionarHistorico(encontrado->streamhist, encontrado->streamtrabalha, data_inicio, data_fim);
            // altera a stream atual
            strcpy(encontrado->streamtrabalha, nova_stream);
            printf("alteracao realizada: %s agora trabalha em %s\n", encontrado->nomeapresent, encontrado->streamtrabalha);
            break;
        }
        case 17:{
            printf("Digite o nome do apresentador: ");
            char nome_a[100];
            fgets(nome_a, sizeof(nome_a), stdin);
            nome_a[strcspn(nome_a, "\n")] = 0;
            if(listaApresentadores == NULL){
                printf("Nenhum apresentador cadastrado.\n");
                break;
            }
            ListaApr* atual2 = listaApresentadores;
            ListaApr* encontrado2 = NULL;
            do{
                if(strcmp(atual2->nomeapresent, nome_a) == 0){
                    encontrado2 = atual2;
                    break;
                }
                atual2 = atual2->prox;
            }while(atual2 != listaApresentadores);
            if(encontrado2 == NULL){
                printf("Apresentador nao encontrado.\n");
            }else{
                mostrarCurriculo(encontrado2);
            }
            break;
        }
        case 0:{
            printf("Saindo...\n");
            break;
        }
        default:{
            printf("Opcao invalida\n");
        }
       }
   }while(op != 0);

   return 0;
}