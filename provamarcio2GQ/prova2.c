//questao 1
void cadastraConta(struct Conta v[], int *tam) {
    struct Conta c;

    if (*tam == TAM_CONTAS) {
        printf("Vetor cheio\n");
        return;
    }
    printf("ID: ");
    scanf("%d", &c.id);
    if (buscaId(v, *tam, c.id) != -1) {
        printf("ID repetido\n");
        return;
    }
    printf("Cliente: ");
    scanf(" %[^\n]", c.cliente);
    printf("Limite: ");
    scanf("%lf", &c.limite);
    if (c.limite < 0) {
        printf("Limite negativo\n");
        return;
    }
    c.saldo = 0;
    v[*tam] = c;
    (*tam)++;
}

//questao 2
int buscaBinariaNome(struct Conta v[], int tam, char x[]) {
    int ini = 0, fim = tam - 1, meio;

    while (ini <= fim) {
        meio = (ini + fim) / 2;
        if (strcmp(x, v[meio].cliente) == 0)
            return meio;
        if (strcmp(x, v[meio].cliente) < 0)
            fim = meio - 1;
        else
            ini = meio + 1;
    }
    return -1;
}

//questao 3
void filtraDevedores(struct Conta vContas[], int tamConta,
                     struct Conta vDevedores[], int *tamDevedores) {
    int i;

    *tamDevedores = 0;
    for (i = 0; i < tamConta; i++) {
        if (vContas[i].saldo < 0) {
            vDevedores[*tamDevedores] = vContas[i];
            (*tamDevedores)++;
        }
    }
}

//questao 4
int realizarSaque(struct Conta vContas[], int tamConta,
                  struct Operacao vOp[], int *tamOp) {
    int id, pos;
    double valor;

    printf("ID: ");
    scanf("%d", &id);
    pos = buscaId(vContas, tamConta, id);
    if (pos == -1)
        return 0;

    printf("Valor: ");
    scanf("%lf", &valor);
    if (vContas[pos].saldo + vContas[pos].limite < valor)
        return 0;

    vContas[pos].saldo = vContas[pos].saldo - valor;
    vOp[*tamOp].id = *tamOp + 1;
    vOp[*tamOp].idConta = id;
    vOp[*tamOp].tipo = 'S';
    vOp[*tamOp].valor = -valor;
    (*tamOp)++;
    return 1;
}

//questao 5
void extrato(struct Conta vContas[], int tamConta,
             struct Operacao vOp[], int *tamOp) {
    int id, pos, i, total = 0, n = 0;
    double saldo = 0;

    printf("ID: ");
    scanf("%d", &id);
    pos = buscaId(vContas, tamConta, id);
    if (pos == -1)
        return;

    for (i = 0; i < *tamOp; i++)
        if (vOp[i].idConta == id)
            total++;

    printf("CONTA N.%03d\n", id);
    printf("CLIENTE: %s\n", vContas[pos].cliente);

    for (i = 0; i < *tamOp; i++) {
        if (vOp[i].idConta == id) {
            n++;
            if (n == total - 4 || (total <= 5 && n == 1))
                printf("Saldo Anterior: %.2f%c\n", fabs(saldo), saldo >= 0 ? 'C' : 'D');
            saldo = saldo + vOp[i].valor;
            if (n > total - 5)
                printf("%04d %c %.2f%c %.2f%c\n", vOp[i].id, vOp[i].tipo,
                       fabs(vOp[i].valor), vOp[i].valor >= 0 ? 'C' : 'D',
                       fabs(saldo), saldo >= 0 ? 'C' : 'D');
        }
    }
    printf("Saldo Atual: %.2f%c\n", fabs(saldo), saldo >= 0 ? 'C' : 'D');
}