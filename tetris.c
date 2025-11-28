#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca itens[MAX_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;

typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

int contadorID = 0;

void inicializarFila(Fila *f);
void inicializarPilha(Pilha *p);
int enqueue(Fila *f, Peca p);
int dequeue(Fila *f, Peca *p);
int push(Pilha *p, Peca x);
int pop(Pilha *p, Peca *x);
void exibirFila(Fila f);
void exibirPilha(Pilha p);
Peca gerarPeca();

int main() {
    Fila fila;
    Pilha pilha;
    int opcao;

    srand(time(NULL));

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    do {
        printf("\n=====================================\n");
        printf("         ESTADO ATUAL\n");
        printf("=====================================\n");
        exibirFila(fila);
        exibirPilha(pilha);

        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) { 
            Peca jogada;
            if (dequeue(&fila, &jogada)) {
                printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);
                enqueue(&fila, gerarPeca());
            }
        }
        else if (opcao == 2) {
            Peca removida;
            if (pilha.topo == MAX_PILHA - 1) {
                printf("\nA pilha está cheia! Não é possível reservar.\n");
            } else if (dequeue(&fila, &removida)) {
                push(&pilha, removida);
                printf("\nPeça [%c %d] reservada!\n", removida.nome, removida.id);
                enqueue(&fila, gerarPeca());
            }
        }
        else if (opcao == 3) {
            Peca usada;
            if (pop(&pilha, &usada)) {
                printf("\nPeça reservada usada: [%c %d]\n", usada.nome, usada.id);
                enqueue(&fila, gerarPeca());
            } else {
                printf("\nA pilha está vazia! Não há peça reservada.\n");
            }
        }

    } while (opcao != 0);

    printf("\nEncerrando sistema...\n");
    return 0;
}

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->quantidade = 0;
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int enqueue(Fila *f, Peca p) {
    if (f->quantidade == MAX_FILA) return 0;
    f->itens[f->tras] = p;
    f->tras = (f->tras + 1) % MAX_FILA;
    f->quantidade++;
    return 1;
}

int dequeue(Fila *f, Peca *p) {
    if (f->quantidade == 0) return 0;
    *p = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->quantidade--;
    return 1;
}

int push(Pilha *p, Peca x) {
    if (p->topo == MAX_PILHA - 1) return 0;
    p->topo++;
    p->itens[p->topo] = x;
    return 1;
}

int pop(Pilha *p, Peca *x) {
    if (p->topo == -1) return 0;
    *x = p->itens[p->topo];
    p->topo--;
    return 1;
}

void exibirFila(Fila f) {
    printf("\nFila de peças: ");
    int i = f.frente;
    for (int c = 0; c < f.quantidade; c++) {
        printf("[%c %d] ", f.itens[i].nome, f.itens[i].id);
        i = (i + 1) % MAX_FILA;
    }
}

void exibirPilha(Pilha p) {
    printf("\nPilha de reserva (Topo -> Base): ");
    if (p.topo == -1) {
        printf("vazia");
        return;
    }
    for (int i = p.topo; i >= 0; i--) {
        printf("[%c %d] ", p.itens[i].nome, p.itens[i].id);
    }
}

Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = contadorID++;
    return p;
}
