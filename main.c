#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100

struct nodo
{
    char musica[max];
    struct nodo *prox;
};

struct fila
{
    struct nodo *ini;
    struct nodo *fim;
    struct nodo *indicador;
};

typedef struct fila *tipofila;

tipofila cria_fila()
{
    tipofila F;
    F = (tipofila)malloc(sizeof(struct fila));
    if (F != NULL)
    {
        F->ini = NULL;
        F->fim = NULL;
        F->indicador = NULL;
    }
    return F;
}

int fila_vazia(tipofila F)
{
    if (F != NULL && F->ini == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int insere_musica(tipofila *F, char musica[])
{
    struct nodo *N = (struct nodo *)malloc(sizeof(struct nodo));
    if (N == NULL || *F == NULL)
    {
        return 0;
    }
    strncpy(N->musica, musica, 100);
    N->prox = NULL;
    if (fila_vazia(*F) == 1)
    {
        (*F)->ini = N;
        (*F)->indicador = N;
    }
    else
    {
        ((*F)->fim)->prox = N;
    }
    (*F)->fim = N;
    return 1;
}

int remove_musica(tipofila *F, char musica[])
{
    int count = 0;
    if (fila_vazia(*F) == 1)
    {
        return 0;
    }
    struct nodo *Aux = (*F)->ini;
    if (strcmp(musica, ((*F)->ini)->musica) == 0)
    {
        if ((*F)->ini == (*F)->indicador)
        {
            (*F)->indicador = Aux->prox;
        }
        (*F)->ini = Aux->prox;
        free(Aux);
        return 1;
    }
    while (Aux->prox != NULL && strcmp(Aux->prox->musica, musica) != 0)
    {
        Aux = Aux->prox;
        count++;
    }
    if (Aux->prox == NULL)
    {
        return 0;
    }
    if ((*F)->indicador == Aux)
    {
        struct nodo *AuxCount = (*F)->ini;
        //Se o indicador estiver no nó que será removido, ele irá para o anterior
        while (count > 1)
        {
            AuxCount = AuxCount->prox;
            count--;
        }
        (*F)->indicador = AuxCount;
    }
    struct nodo *Aux2 = Aux->prox;
    Aux->prox = Aux2->prox;
    free(Aux2);
    return 1;
}

void toca(tipofila *F)
{
    if ((*F)->indicador == (*F)->fim)
    {
        printf("%s\n", (*F)->indicador->musica);
    }
    else
    {
        printf("%s\n", (*F)->indicador->musica);
        (*F)->indicador = (*F)->indicador->prox;
    }
}

int volta(tipofila *F)
{
    if (*F == NULL || (*F)->indicador == (*F)->ini)
    {
        return 0;
    }
    else
    {
        int count = 0;
        struct nodo *AuxCount = (*F)->ini;
        while (AuxCount != (*F)->indicador)
        {
            count++;
            AuxCount = AuxCount->prox;
        }
        AuxCount = (*F)->ini;
        while (count > 1)
        {
            AuxCount = AuxCount->prox;
            count--;
        }
        (*F)->indicador = AuxCount;
        return 1;
    }
}

void final(tipofila *F)
{
    //não sei se é pra mover o indicador pro final, mas pelo que o exercício fala, não é pra fazer isso
    struct nodo *Aux = (*F)->indicador;
    while (Aux != (*F)->fim)
    {
        printf("%s", Aux->musica);
        Aux = Aux->prox;
    }
}

void inverte(tipofila *F)
{
    struct nodo *Aux = (*F)->ini;
    struct nodo *AuxIndicador = (*F)->ini;
    int count = 0;
    int countIndicador = 0;
    while (AuxIndicador != (*F)->indicador)
    {
        countIndicador++;
        AuxIndicador = AuxIndicador->prox;
    }
    while (Aux->prox != NULL)
    {
        count++;
        Aux = Aux->prox;
    }
    Aux = (*F)->ini;
    while (count > 0)
    {
        //fazendo isso, estaremos adicionando uma musica no final, e tirando a musica do começo
        insere_musica(F, Aux->musica);
        remove_musica(F, Aux->musica);
        count--;
    }
    (*F)->indicador = (*F)->ini;
    while (countIndicador > 0)
    {
        (*F)->ini = (*F)->ini->prox;
    }
}

int imprimeFila(tipofila F){
    if(F == NULL){
        return 0;
    }
    struct nodo *aux;
    for(aux = F->ini; aux != NULL; aux = aux->prox){
        printf("%s\n", aux->musica);
    }
    return 1;
}

/*
int main()
{
    tipofila playlist = cria_fila();
    tipofila indicador = playlist;
    while (1)
    {
        int qtd_operacoes;
        int i = 0;
        scanf("%d", &qtd_operacoes);
        if (qtd_operacoes == 0)
        {
            break;
        }
        while (i < qtd_operacoes)
        {
            char operacao[10];
            scanf("%s", operacao);
            if (strncmp(operacao, "insere", 10) == 0)
            {
                char nome[100];
                scanf("%s", nome);
                insere_musica(&playlist, nome);
            }
            else if (strncmp(operacao, "remove", 10) == 0)
            {
                char nome[100];
                scanf("%s", nome);
                remove_musica(&playlist, nome);
            }
            else if (strncmp(operacao, "toca", 10) == 0)
            {
                toca(&playlist);
            }
            else if (strncmp(operacao, "final", 10) == 0)
            {
                final(&playlist);
            }
            else if (strncmp(operacao, "volta", 10) == 0)
            {
                volta(&playlist);
            }
            else if (strncmp(operacao, "inverte", 10) == 0)
            {
                inverte(&playlist);
            }
            i++;
        }
    }
    return 0;
}
*/

int main(){
    tipofila fila;
    fila = cria_fila();
    insere_musica(&fila, "TAKE ON ME");
    insere_musica(&fila, "SUCESSO");
    toca(&fila);
    volta(&fila);
    toca(&fila);
    return 0;
}