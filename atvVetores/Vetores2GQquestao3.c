#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100

typedef struct {
    int numero;
    char nome[50];
    char cpf[15];
    char telefone[20];
    float saldo;
} Conta;

typedef struct {
    Conta contas[MAX_CONTAS];
    int qtd;
} Cadastro;

int buscarConta(Cadastro *cad, int numero) {
    int i;

    if (cad->qtd == 0) {
        return -1;
    }

    for (i = 0; i < cad->qtd; i++) {
        if (cad->contas[i].numero == numero) {
            return i;
        }
    }
    return -2;
}

void cadastrarConta(Cadastro *cad, int numero) {
    Conta *nova;

    if (cad->qtd >= MAX_CONTAS) {
        printf("Cadastro cheio! Nao e possivel cadastrar mais contas.\n");
        return;
    }

    if (buscarConta(cad, numero) >= 0) {
        printf("Numero de conta repetido! Cadastramento nao realizado.\n");
        return;
    }

    nova = &cad->contas[cad->qtd];
    nova->numero = numero;
    printf("Nome do cliente: ");
    scanf(" %49[^\n]", nova->nome);
    printf("CPF: ");
    scanf(" %14[^\n]", nova->cpf);
    printf("Telefone: ");
    scanf(" %19[^\n]", nova->telefone);
    printf("Saldo inicial: ");
    scanf("%f", &nova->saldo);

    cad->qtd++;
    printf("Conta cadastrada com sucesso!\n");
}

void consultarSaldo(Cadastro *cad, int numero) {
    int pos = buscarConta(cad, numero);

    if (pos < 0) {
        printf("Conta nao cadastrada.\n");
    } else {
        printf("Saldo da conta %d: R$ %.2f\n", numero, cad->contas[pos].saldo);
    }
}

void depositar(Cadastro *cad, int numero) {
    int pos = buscarConta(cad, numero);
    float valor;

    if (pos < 0) {
        printf("Conta nao cadastrada.\n");
        return;
    }

    printf("Valor do deposito: ");
    scanf("%f", &valor);

    if (valor <= 0) {
        printf("Valor invalido!\n");
        return;
    }

    cad->contas[pos].saldo += valor;
    printf("Deposito realizado! Novo saldo: R$ %.2f\n", cad->contas[pos].saldo);
}

void sacar(Cadastro *cad, int numero) {
    int pos = buscarConta(cad, numero);
    float valor;

    if (pos < 0) {
        printf("Conta nao cadastrada.\n");
        return;
    }

    printf("Valor do saque: ");
    scanf("%f", &valor);

    if (valor <= 0) {
        printf("Valor invalido!\n");
    } else if (valor > cad->contas[pos].saldo) {
        printf("Nao existe saldo suficiente.\n");
    } else {
        cad->contas[pos].saldo -= valor;
        printf("Saque realizado! Novo saldo: R$ %.2f\n", cad->contas[pos].saldo);
    }
}

void exibirContas(Cadastro *cad) {
    int i;

    if (cad->qtd == 0) {
        printf("Cadastro vazio.\n");
        return;
    }

    for (i = 0; i < cad->qtd; i++) {
        printf("Conta: %d | Titular: %s | Telefone: %s\n",
               cad->contas[i].numero, cad->contas[i].nome,
               cad->contas[i].telefone);
    }
}

void menuCadastro(Cadastro *cad, const char *titulo) {
    int opcao, numero;

    do {
        printf("\n--- %s ---\n", titulo);
        printf("1 - Cadastrar conta\n");
        printf("2 - Consultar saldo\n");
        printf("3 - Depositar\n");
        printf("4 - Sacar\n");
        printf("5 - Exibir contas\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 4) {
            printf("Numero da conta: ");
            scanf("%d", &numero);
        }

        switch (opcao) {
            case 1: cadastrarConta(cad, numero); break;
            case 2: consultarSaldo(cad, numero); break;
            case 3: depositar(cad, numero); break;
            case 4: sacar(cad, numero); break;
            case 5: exibirContas(cad); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main() {
    Cadastro corrente, poupanca;
    int opcao;

    corrente.qtd = 0;
    poupanca.qtd = 0;

    do {
        printf("\n===== BANCO DINHEIRO CERTO =====\n");
        printf("1 - Conta corrente\n");
        printf("2 - Conta poupanca\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: menuCadastro(&corrente, "CONTA CORRENTE"); break;
            case 2: menuCadastro(&poupanca, "CONTA POUPANCA"); break;
            case 0: printf("Encerrando o programa...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}