#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 40

typedef struct {
    int codigo;
    char descricao[50];
    float valor;
    int estoque;
} Produto;


int buscarProduto(Produto produtos[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}


void cadastrarProduto(Produto produtos[], int *total) {
    int codigo;

    if (*total >= MAX_PRODUTOS) {
        printf("Cadastro cheio! Nao e possivel cadastrar mais produtos.\n");
        return;
    }

    printf("Codigo: ");
    scanf("%d", &codigo);

    if (buscarProduto(produtos, *total, codigo) != -1) {
        printf("Ja existe um produto com esse codigo!\n");
        return;
    }

    produtos[*total].codigo = codigo;
    printf("Descricao: ");
    scanf(" %49[^\n]", produtos[*total].descricao);
    printf("Valor unitario: ");
    scanf("%f", &produtos[*total].valor);
    printf("Quantidade em estoque: ");
    scanf("%d", &produtos[*total].estoque);

    (*total)++;
    printf("Produto cadastrado com sucesso!\n");
}


void alterarValor(Produto produtos[], int total, int codigo) {
    int pos = buscarProduto(produtos, total, codigo);

    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    printf("Valor atual: R$ %.2f\n", produtos[pos].valor);
    printf("Novo valor unitario: ");
    scanf("%f", &produtos[pos].valor);
    printf("Valor alterado com sucesso!\n");
}

float valorUnitario(Produto produtos[], int total, int codigo) {
    int pos = buscarProduto(produtos, total, codigo);

    if (pos == -1) {
        return -1;
    }
    return produtos[pos].valor;
}

int quantidadeEstoque(Produto produtos[], int total, int codigo) {
    int pos = buscarProduto(produtos, total, codigo);

    if (pos == -1) {
        return -1;
    }
    return produtos[pos].estoque;
}

void vender(Produto produtos[], int total, int codigo, int quantidade) {
    int pos = buscarProduto(produtos, total, codigo);
    char resposta;

    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    if (produtos[pos].estoque == 0) {
        printf("Produto sem estoque!\n");
        return;
    }

    if (quantidade <= produtos[pos].estoque) {
        produtos[pos].estoque -= quantidade;
        printf("Venda realizada! Valor a pagar: R$ %.2f\n",
               quantidade * produtos[pos].valor);
    } else {
        printf("Estoque insuficiente! Existem apenas %d unidade(s).\n",
               produtos[pos].estoque);
        printf("Deseja comprar todo o estoque disponivel? (s/n): ");
        scanf(" %c", &resposta);

        if (resposta == 's' || resposta == 'S') {
            printf("Venda realizada! Valor a pagar: R$ %.2f\n",
                   produtos[pos].estoque * produtos[pos].valor);
            produtos[pos].estoque = 0;
        } else {
            printf("Compra cancelada.\n");
        }
    }
}


void atualizarEstoque(Produto produtos[], int total, int codigo) {
    int pos = buscarProduto(produtos, total, codigo);

    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    printf("Estoque atual: %d\n", produtos[pos].estoque);
    printf("Nova quantidade em estoque: ");
    scanf("%d", &produtos[pos].estoque);
    printf("Estoque atualizado com sucesso!\n");
}

void exibirProdutos(Produto produtos[], int total) {
    int i;

    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- Produtos cadastrados ---\n");
    for (i = 0; i < total; i++) {
        printf("Codigo: %d | Descricao: %s\n",
               produtos[i].codigo, produtos[i].descricao);
    }
}
void exibirSemEstoque(Produto produtos[], int total) {
    int i, achou = 0;

    printf("\n--- Produtos com estoque zero ---\n");
    for (i = 0; i < total; i++) {
        if (produtos[i].estoque == 0) {
            printf("Codigo: %d | Descricao: %s\n",
                   produtos[i].codigo, produtos[i].descricao);
            achou = 1;
        }
    }
    if (!achou) {
        printf("Nenhum produto com estoque zero.\n");
    }
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    int total = 0;
    int opcao, codigo, quantidade;
    float valor;

    do {
        printf("\n===== PAPELARIA ESCOLAR =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Alterar valor unitario\n");
        printf("3 - Consultar valor unitario\n");
        printf("4 - Consultar quantidade em estoque\n");
        printf("5 - Vender produto\n");
        printf("6 - Atualizar estoque\n");
        printf("7 - Exibir todos os produtos\n");
        printf("8 - Exibir produtos com estoque zero\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &total);
                break;
            case 2:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                alterarValor(produtos, total, codigo);
                break;
            case 3:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                valor = valorUnitario(produtos, total, codigo);
                if (valor == -1)
                    printf("Produto nao encontrado!\n");
                else
                    printf("Valor unitario: R$ %.2f\n", valor);
                break;
            case 4:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                quantidade = quantidadeEstoque(produtos, total, codigo);
                if (quantidade == -1)
                    printf("Produto nao encontrado!\n");
                else
                    printf("Quantidade em estoque: %d\n", quantidade);
                break;
            case 5:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                printf("Quantidade desejada: ");
                scanf("%d", &quantidade);
                vender(produtos, total, codigo, quantidade);
                break;
            case 6:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                atualizarEstoque(produtos, total, codigo);
                break;
            case 7:
                exibirProdutos(produtos, total);
                break;
            case 8:
                exibirSemEstoque(produtos, total);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}