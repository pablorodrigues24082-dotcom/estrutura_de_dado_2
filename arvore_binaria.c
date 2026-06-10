//Questao 36 — Estrutura de no de arvore binaria
//Cada no precisa armazenar:
//um valor;
//ponteiro para filho da esquerda;
//ponteiro para filho da direita.
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

//Questao 37 — Insere nos manualmente na arvore binaria
//Nao ha regra de ordenacao, os nos sao ligados diretamente
//Exemplo de uso no main:
//  raiz->esq = criarNo(2);
//  raiz->dir = criarNo(3);

//Questao 38 — Percurso em pre-ordem
//Visita: raiz -> esquerda -> direita
void preOrdem(No *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

//Questao 39 — Percurso em ordem
//Visita: esquerda -> raiz -> direita
void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        emOrdem(raiz->dir);
    }
}

//Questao 40 — Percurso em pos-ordem
//Visita: esquerda -> direita -> raiz
void posOrdem(No *raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

//Questao 41 — Conta o numero de nos da arvore
int contarNos(No *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

//Questao 42 — Calcula a altura da arvore
//Convencao: arvore com 1 no tem altura 0
int calcularAltura(No *raiz) {
    if (raiz == NULL) return -1;

    int altEsq = calcularAltura(raiz->esq);
    int altDir = calcularAltura(raiz->dir);

    if (altEsq > altDir) return 1 + altEsq;
    return 1 + altDir;
}

//Questao 43 — Conta quantos nos folha existem
//No folha: nao possui filhos
int contarFolhas(No *raiz) {
    if (raiz == NULL) return 0;
    if (raiz->esq == NULL && raiz->dir == NULL) return 1;
    return contarFolhas(raiz->esq) + contarFolhas(raiz->dir);
}

//Questao 44 — Espelha a arvore binaria
//Troca os filhos esquerdo e direito de cada no
void espelhar(No *raiz) {
    if (raiz == NULL) return;

    No *temp = raiz->esq;
    raiz->esq = raiz->dir;
    raiz->dir = temp;

    espelhar(raiz->esq);
    espelhar(raiz->dir);
}

//Questao 45 — Verifica se duas arvores sao iguais
//Retorna 1 se iguais, 0 se diferentes
int saoIguais(No *a, No *b) {
    if (a == NULL && b == NULL) return 1;
    if (a == NULL || b == NULL) return 0;
    if (a->valor != b->valor) return 0;
    return saoIguais(a->esq, b->esq) && saoIguais(a->dir, b->dir);
}

int main() {
    No *raiz = NULL;

    //Monta a arvore manualmente (questao 37)
    raiz = criarNo(1);
    raiz->esq = criarNo(2);
    raiz->dir = criarNo(3);
    raiz->esq->esq = criarNo(4);
    raiz->esq->dir = criarNo(5);
    raiz->dir->dir = criarNo(6);

    printf("Pre-ordem: ");
    preOrdem(raiz);

    printf("\nEm ordem: ");
    emOrdem(raiz);

    printf("\nPos-ordem: ");
    posOrdem(raiz);

    printf("\n\nTotal de nos: %d\n", contarNos(raiz));
    printf("Altura: %d\n", calcularAltura(raiz));
    printf("Total de folhas: %d\n", contarFolhas(raiz));

    //Monta uma segunda arvore identica para testar igualdade
    No *raiz2 = NULL;
    raiz2 = criarNo(1);
    raiz2->esq = criarNo(2);
    raiz2->dir = criarNo(3);
    raiz2->esq->esq = criarNo(4);
    raiz2->esq->dir = criarNo(5);
    raiz2->dir->dir = criarNo(6);

    if (saoIguais(raiz, raiz2)) {
        printf("\nAs arvores sao iguais!\n");
    }
    else {
        printf("\nAs arvores sao diferentes!\n");
    }

    espelhar(raiz);
    printf("\nApos espelhar, em ordem: ");
    emOrdem(raiz);
    printf("\n");

    return 0;
}
