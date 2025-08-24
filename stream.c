#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>

typedef struct ArvProg{
    char *nomeProg;
    char *periodo;
    char *hora_inicio;
    bool ao_vivo;
    char *nome_apresent;

}ArvProg;

typedef struct ListCat{
    char *tipo;
    char *nomecat;
    struct ListCat *prox;
    struct ArvProg *prog;
}ListCat;

typedef struct NoStream{
    char *nome;
    char *site;
    struct ListCat *categoria;
    struct NoStream *esq;
    struct NoStream *dir;
} NoStream;



NoStream *criarNostream(char *nome, char site)