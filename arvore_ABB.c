#include <stdio.h>
#include <stdlib.h>

//Estrutura de no da ABB
//Cada no armazena um valor e dois ponteiros: esq e dir
typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

//Cria um novo no e inicializa os ponteiros como NULL
No* criarNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

//Questao 10 — Insercao na ABB usando recursao
//Regras:
//se o valor for menor -> vai para esquerda;
//se o valor for maior -> vai para direita.
No* inserir(No *raiz, int valor) {
    // arvore vazia
    if (raiz == NULL) {
        return criarNo(valor);
    }
    // insercao a esquerda
    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    }
    // insercao a direita
    else if (valor > raiz->valor) {
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;
}

//Questao 11 — Busca na ABB
//Retorna o no encontrado ou NULL se nao existir
No* buscar(No *raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }
    if (valor < raiz->valor) {
        return buscar(raiz->esq, valor);
    }
    return buscar(raiz->dir, valor);
}

//Questao 12 — Percurso em ordem na ABB
//Ordem: esquerda -> raiz -> direita
//Resultado sempre sai em ordem crescente
void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        emOrdem(raiz->dir);
    }
}

//Funcao auxiliar: retorna o menor no da subarvore
//Usado na remocao com dois filhos
No* menorNo(No *raiz) {
    No *atual = raiz;
    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

//Questao 13 — Remove um no folha (sem filhos)
//Questao 14 — Remove um no com apenas um filho
//Questao 15 — Remove um no com dois filhos usando sucessor em ordem
No* remover(No *raiz, int valor) {
    No *temp = NULL;
    // arvore vazia
    if (raiz == NULL) {
        return NULL;
    }
    // busca do no
    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    }
    else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    }
    // encontrou o no
    else {
        // CASO 1 - sem filhos (no folha)
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
        // CASO 2 - um filho a direita
        else if (raiz->esq == NULL) {
            temp = raiz->dir;
            free(raiz);
            return temp;
        }
        // CASO 2 - um filho a esquerda
        else if (raiz->dir == NULL) {
            temp = raiz->esq;
            free(raiz);
            return temp;
        }
        // CASO 3 - dois filhos: substitui pelo sucessor em ordem
        temp = menorNo(raiz->dir);
        raiz->valor = temp->valor;
        raiz->dir = remover(raiz->dir, temp->valor);
    }
    return raiz;
}

//Questao 16 — Encontra o menor e o maior valor da ABB
//Menor: caminha sempre para a esquerda
//Maior: caminha sempre para a direita
int menorValor(No *raiz) {
    if (raiz == NULL) return -1;
    if (raiz->esq == NULL) return raiz->valor;
    return menorValor(raiz->esq);
}

int maiorValor(No *raiz) {
    if (raiz == NULL) return -1;
    if (raiz->dir == NULL) return raiz->valor;
    return maiorValor(raiz->dir);
}

//Questao 17 — Verifica se a arvore e uma ABB valida
//Em uma ABB valida:
//todo no da esquerda e menor que a raiz;
//todo no da direita e maior que a raiz.
int ehABBValida(No *raiz, int min, int max) {
    if (raiz == NULL) return 1;
    if (raiz->valor <= min || raiz->valor >= max) return 0;
    return ehABBValida(raiz->esq, min, raiz->valor) &&
           ehABBValida(raiz->dir, raiz->valor, max);
}

//Questao 18 — Conta quantos niveis existem na ABB
//Nivel = altura + 1
//Arvore com 1 no tem 1 nivel
int contarNiveis(No *raiz) {
    if (raiz == NULL) return 0;

    int esq = contarNiveis(raiz->esq);
    int dir = contarNiveis(raiz->dir);

    if (esq > dir) return 1 + esq;
    return 1 + dir;
}

//Questao 19 — Menu completo de ABB
void menu(No **raiz) {
    int opcao, valor;
    No *resultado = NULL;

    do {
        printf("\n=== MENU ABB ===\n");
        printf("1. Inserir\n");
        printf("2. Buscar\n");
        printf("3. Remover\n");
        printf("4. Imprimir em ordem\n");
        printf("5. Mostrar altura\n");
        printf("0. Encerrar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Valor para inserir: ");
                scanf("%d", &valor);
                *raiz = inserir(*raiz, valor);
                printf("Inserido!\n");
                break;

            case 2:
                printf("Valor para buscar: ");
                scanf("%d", &valor);
                resultado = buscar(*raiz, valor);
                if (resultado != NULL) {
                    printf("Valor encontrado!\n");
                }
                else {
                    printf("Valor nao encontrado!\n");
                }
                break;

            case 3:
                printf("Valor para remover: ");
                scanf("%d", &valor);
                *raiz = remover(*raiz, valor);
                printf("Removido!\n");
                break;

            case 4:
                printf("Em ordem: ");
                emOrdem(*raiz);
                printf("\n");
                break;

            case 5:
                printf("Altura: %d\n", contarNiveis(*raiz) - 1);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main() {
    No *raiz = NULL;

    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);
    raiz = inserir(raiz, 90);
    raiz = inserir(raiz, 35);
    raiz = inserir(raiz, 25);

    printf("Em ordem: ");
    emOrdem(raiz);

    printf("\nMenor valor: %d\n", menorValor(raiz));
    printf("Maior valor: %d\n", maiorValor(raiz));
    printf("Niveis: %d\n", contarNiveis(raiz));

    if (ehABBValida(raiz, -2147483648, 2147483647)) {
        printf("E uma ABB valida!\n");
    }
    else {
        printf("Nao e uma ABB valida!\n");
    }

    printf("\nAntes de remover elementos:\n");
    emOrdem(raiz);

    raiz = remover(raiz, 80);
    printf("\n\nDepois de remover 80:\n");
    emOrdem(raiz);

    raiz = remover(raiz, 30);
    printf("\n\nDepois de remover 30:\n");
    emOrdem(raiz);

    menu(&raiz);

    return 0;
}
