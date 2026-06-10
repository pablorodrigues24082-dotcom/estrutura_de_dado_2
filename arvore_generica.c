#include <stdio.h>
#include <stdlib.h>
 
//Questao 16 — Estrutura de no para arvore generica
//Cada no precisa armazenar:
//um valor;
//ponteiro para o primeiro filho;
//ponteiro para o proximo irmao.
typedef struct No {
    int valor;
    struct No *primeiro_filho;
    struct No *proximo_irmao;
} No;
 
//Questao 17 — Inicializa uma arvore vazia
//Uma arvore vazia e representada por um ponteiro NULL
//Esta funcao cria um no raiz com o valor informado
No* criarNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    return novo;
}
 
No* inicializarArvore(int valor) {
    return criarNo(valor);
}
 
//Questao 18 — Insere um filho em um no pai
//Percorre a lista de irmaos ate o ultimo e adiciona o novo filho
void inserirFilho(No *pai, int valor) {
    if (pai == NULL) return;
 
    No *novo = criarNo(valor);
 
    // se o pai nao tem filhos ainda
    if (pai->primeiro_filho == NULL) {
        pai->primeiro_filho = novo;
        return;
    }
 
    // percorre ate o ultimo irmao
    No *atual = pai->primeiro_filho;
    while (atual->proximo_irmao != NULL) {
        atual = atual->proximo_irmao;
    }
    atual->proximo_irmao = novo;
}
 
//Questao 19 — Conta quantos nos existem na arvore
//Conta 1 (no atual) + nos de cada subarvore filho
int contarNos(No *raiz) {
    if (raiz == NULL) return 0;
 
    int total = 1;
    No *filho = raiz->primeiro_filho;
    while (filho != NULL) {
        total += contarNos(filho);
        filho = filho->proximo_irmao;
    }
    return total;
}
 
//Questao 20 — Calcula a altura da arvore (recursiva)
//Altura = maior caminho da raiz ate uma folha
//Convencao: arvore com 1 no tem altura 0
int calcularAltura(No *raiz) {
    if (raiz == NULL) return -1;
    if (raiz->primeiro_filho == NULL) return 0;
 
    int maior = -1;
    No *filho = raiz->primeiro_filho;
    while (filho != NULL) {
        int h = calcularAltura(filho);
        if (h > maior) maior = h;
        filho = filho->proximo_irmao;
    }
    return 1 + maior;
}
 
//Questao 21 — Conta quantas folhas existem
//Um no e folha quando nao possui filhos
int contarFolhas(No *raiz) {
    if (raiz == NULL) return 0;
    if (raiz->primeiro_filho == NULL) return 1;
 
    int folhas = 0;
    No *filho = raiz->primeiro_filho;
    while (filho != NULL) {
        folhas += contarFolhas(filho);
        filho = filho->proximo_irmao;
    }
    return folhas;
}
 
//Questao 22 — Verifica se um valor existe na arvore
//Retorna 1 se encontrou, 0 se nao encontrou
int buscar(No *raiz, int valor) {
    if (raiz == NULL) return 0;
    if (raiz->valor == valor) return 1;
 
    No *filho = raiz->primeiro_filho;
    while (filho != NULL) {
        if (buscar(filho, valor)) return 1;
        filho = filho->proximo_irmao;
    }
    return 0;
}
 
//Questao 23 — Imprime os nos por nivel (BFS)
//Usa uma fila simples com vetor para percorrer em largura
#define MAX 100
 
void imprimirPorNivel(No *raiz) {
    if (raiz == NULL) {
        printf("Arvore vazia.\n");
        return;
    }
 
    No *fila[MAX];
    int niveis[MAX];
    int inicio = 0, fim = 0;
 
    fila[fim] = raiz;
    niveis[fim] = 0;
    fim++;
 
    int nivelAtual = -1;
 
    while (inicio < fim) {
        No *atual = fila[inicio];
        int nivel = niveis[inicio];
        inicio++;
 
        if (nivel != nivelAtual) {
            nivelAtual = nivel;
            printf("\nNivel %d: ", nivel);
        }
        printf("%d ", atual->valor);
 
        No *filho = atual->primeiro_filho;
        while (filho != NULL) {
            fila[fim] = filho;
            niveis[fim] = nivel + 1;
            fim++;
            filho = filho->proximo_irmao;
        }
    }
    printf("\n");
}
 
/
//O codigo fica mais simples e legivel porque espelha
//a estrutura da propria arvore. O call stack do C
//funciona como a pilha de controle automaticamente.
 
//Questao 25 — Destroi e libera toda a arvore da memoria
//Usa pos-ordem: libera os filhos antes de liberar o pai
void destruirArvore(No **raiz) {
    if (*raiz == NULL) return;
 
    No *filho = (*raiz)->primeiro_filho;
    while (filho != NULL) {
        No *proximo = filho->proximo_irmao;
        destruirArvore(&filho);
        filho = proximo;
    }
 
    free(*raiz);
    *raiz = NULL;
}
 
int main() {
    // inicializa a arvore com a raiz
    No *raiz = inicializarArvore(1);
 
    // insere filhos da raiz
    inserirFilho(raiz, 2);
    inserirFilho(raiz, 3);
    inserirFilho(raiz, 4);
 
    // insere filhos do no 2
    No *no2 = raiz->primeiro_filho;
    inserirFilho(no2, 5);
    inserirFilho(no2, 6);
 
    // insere filho do no 4
    No *no4 = no2->proximo_irmao->proximo_irmao;
    inserirFilho(no4, 7);
 
    // insere filhos do no 7
    No *no7 = no4->primeiro_filho;
    inserirFilho(no7, 8);
    inserirFilho(no7, 9);
 
    printf("Impressao por nivel:");
    imprimirPorNivel(raiz);
 
    printf("\nTotal de nos: %d\n", contarNos(raiz));
    printf("Altura da arvore: %d\n", calcularAltura(raiz));
    printf("Total de folhas: %d\n", contarFolhas(raiz));
 
    int valor;
    printf("\nDigite um valor para buscar: ");
    scanf("%d", &valor);
    if (buscar(raiz, valor)) {
        printf("Valor encontrado!\n");
    }
    else {
        printf("Valor nao encontrado!\n");
    }
 
    destruirArvore(&raiz);
    if (raiz == NULL) {
        printf("\nArvore destruida com sucesso!\n");
    }
 
    return 0;
}
