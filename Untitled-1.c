#include <stdio.h>
#include <string.h>

#define MAX_TENIS 100 // Define o número máximo de tênis que podem ser cadastrados

// Estrutura que representa um tênis
typedef struct {
    char nome[50];
    char cor[30];
    int tamanho;
    float preco;
} Tenis;

// Vetor que armazena os tênis cadastrados
Tenis loja[MAX_TENIS];

// Contador de quantos tênis foram cadastrados
int total_tenis = 0;

// Função que pausa a execução até o usuário apertar Enter
void aguardar() {
    printf("Pressione Enter para continuar...");
    while(getchar() != '\n'); // Limpa o buffer
    getchar(); // Aguarda o Enter final
}

// Função para cadastrar um novo tênis
void cadastrar() {
    if (total_tenis >= MAX_TENIS) {
        printf("Limite de tênis atingido!\n");
        aguardar();
        return;
    }

    printf("Nome do tênis: ");
    getchar(); // Limpa o buffer antes de usar fgets
    fgets(loja[total_tenis].nome, 50, stdin); // Lê o nome
    loja[total_tenis].nome[strcspn(loja[total_tenis].nome, "\n")] = 0; // Remove o '\n'

    printf("Cor do tênis: ");
    fgets(loja[total_tenis].cor, 30, stdin); // Lê a cor
    loja[total_tenis].cor[strcspn(loja[total_tenis].cor, "\n")] = 0;

    printf("Tamanho do tênis (número): ");
    scanf("%d", &loja[total_tenis].tamanho); // Lê o tamanho

    printf("Preço do tênis: R$ ");
    scanf("%f", &loja[total_tenis].preco); // Lê o preço

    total_tenis++; // Incrementa o número total de tênis
    printf("Tênis cadastrado!\n");
    aguardar();
}

// Função que lista todos os tênis cadastrados
void listar() {
    if (total_tenis == 0) {
        printf("Nenhum tênis cadastrado.\n");
        aguardar();
        return;
    }

    // Percorre todos os tênis e exibe as informações
    for (int i = 0; i < total_tenis; i++) {
        printf("%d. %s - Cor: %s - Tamanho: %d - R$ %.2f\n",
               i + 1, loja[i].nome, loja[i].cor, loja[i].tamanho, loja[i].preco);
    }
    aguardar();
}

// Função para buscar um tênis pelo nome
void buscar() {
    char nome[50];
    printf("Nome do tênis: ");
    getchar(); // Limpa o buffer
    fgets(nome, 50, stdin); // Lê o nome a ser buscado
    nome[strcspn(nome, "\n")] = 0;

    // Procura pelo nome
    for (int i = 0; i < total_tenis; i++) {
        if (strcmp(loja[i].nome, nome) == 0) {
            printf("Encontrado: %s - Cor: %s - Tamanho: %d - R$ %.2f\n",
                   loja[i].nome, loja[i].cor, loja[i].tamanho, loja[i].preco);
            aguardar();
            return;
        }
    }

    printf("Tênis não encontrado.\n");
    aguardar();
}

// Função para alterar os dados de um tênis
void alterar() {
    char nome[50];
    printf("Nome do tênis: ");
    getchar(); // Limpa buffer
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = 0;

    // Busca o tênis pelo nome
    for (int i = 0; i < total_tenis; i++) {
        if (strcmp(loja[i].nome, nome) == 0) {
            // Solicita os novos dados
            printf("Novo preço: R$ ");
            scanf("%f", &loja[i].preco);

            printf("Nova cor: ");
            getchar(); // Limpa o buffer
            fgets(loja[i].cor, 30, stdin);
            loja[i].cor[strcspn(loja[i].cor, "\n")] = 0;

            printf("Novo tamanho: ");
            scanf("%d", &loja[i].tamanho);

            printf("Dados alterados!\n");
            aguardar();
            return;
        }
    }

    printf("Tênis não encontrado.\n");
    aguardar();
}

// Função para remover um tênis pelo nome
void remover() {
    char nome[50];
    printf("Nome do tênis: ");
    getchar(); // Limpa buffer
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = 0;

    // Procura o tênis
    for (int i = 0; i < total_tenis; i++) {
        if (strcmp(loja[i].nome, nome) == 0) {
            // Remove o tênis movendo os elementos seguintes para trás
            for (int j = i; j < total_tenis - 1; j++) {
                loja[j] = loja[j + 1];
            }
            total_tenis--;
            printf("Tênis removido!\n");
            aguardar();
            return;
        }
    }

    printf("Tênis não encontrado.\n");
    aguardar();
}

// Função para aplicar descontos baseados no valor total gasto
void aplicar_desconto(float total) {
    float desconto = 0.0f;

    // Verifica a faixa de desconto
    if (total >= 600.0f) {
        desconto = total * 0.15f;
        printf("Desconto progressivo de 15%% aplicado!\n");
    } else if (total >= 300.0f) {
        desconto = total * 0.10f;
        printf("Desconto progressivo de 10%% aplicado!\n");
    } else if (total >= 200.0f) {
        desconto = total * 0.05f;
        printf("Desconto progressivo de 5%% aplicado!\n");
    } else {
        printf("Nenhum desconto aplicado. Gaste mais para obter desconto.\n");
    }

    // Mostra os valores
    printf("Total: R$ %.2f\nDesconto: R$ %.2f\nTotal após desconto: R$ %.2f\n",
           total, desconto, total - desconto);
    aguardar();
}

// Função principal
int main() {
    // Cria um tênis pré-cadastrado
    strcpy(loja[0].nome, "Nike");
    strcpy(loja[0].cor, "Preto");
    loja[0].tamanho = 42;
    loja[0].preco = 500.0f;
    total_tenis = 1;

    char usuario[50];
    char tipo[15];

    // Pede o nome do usuário
    printf("Olá! Seja bem-vindo à Loja de Tênis.\n");
    printf("Por favor, informe seu nome: ");
    fgets(usuario, 50, stdin);
    usuario[strcspn(usuario, "\n")] = 0;

    // Pergunta se o usuário é vendedor ou comprador
    do {
        printf("Você é 'vendedor' ou 'comprador'? ");
        fgets(tipo, 15, stdin);
        tipo[strcspn(tipo, "\n")] = 0;

        // Converte a string para letras minúsculas para facilitar a comparação
        for (int i = 0; tipo[i]; i++) {
            if (tipo[i] >= 'A' && tipo[i] <= 'Z') {
                tipo[i] = tipo[i] + ('a' - 'A');
            }
        }

        // Verifica se a resposta é válida
        if (strcmp(tipo, "vendedor") != 0 && strcmp(tipo, "comprador") != 0) {
            printf("Tipo inválido. Tente novamente.\n");
        }
    } while (strcmp(tipo, "vendedor") != 0 && strcmp(tipo, "comprador") != 0);

    printf("\nOlá %s, você está logado como %s.\n", usuario, tipo);

    int opcao;
    float total_gasto = 0.0f;

    // Loop principal do menu
    do {
        printf("\n=== Menu Loja de Tênis ===\n");

        // Menu do vendedor
        if (strcmp(tipo, "vendedor") == 0) {
            printf("1. Cadastrar tênis\n");
            printf("2. Listar tênis\n");
            printf("3. Buscar tênis\n");
            printf("4. Alterar tênis\n");
            printf("5. Remover tênis\n");
            printf("6. Aplicar desconto\n");
            printf("7. Sair\n");
        } else { // Menu do comprador
            printf("1. Listar tênis\n");
            printf("2. Buscar tênis\n");
            printf("3. Aplicar desconto\n");
            printf("4. Sair\n");
        }

        // Lê a opção escolhida
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Executa a ação conforme o tipo de usuário
        if (strcmp(tipo, "vendedor") == 0) {
            switch (opcao) {
                case 1: cadastrar(); break;
                case 2: listar(); break;
                case 3: buscar(); break;
                case 4: alterar(); break;
                case 5: remover(); break;
                case 6:
                    printf("Digite o total gasto: R$ ");
                    scanf("%f", &total_gasto);
                    aplicar_desconto(total_gasto);
                    break;
                case 7:
                    printf("Encerrando o programa...\n");
                    break;
                default:
                    printf("Opção inválida!\n");
                    aguardar();
            }
        } else { // comprador
            switch (opcao) {
                case 1: listar(); break;
                case 2: buscar(); break;
                case 3:
                    printf("Digite o total gasto: R$ ");
                    scanf("%f", &total_gasto);
                    aplicar_desconto(total_gasto);
                    break;
                case 4:
                    printf("Encerrando o programa...\n");
                    break;
                default:
                    printf("Opção inválida!\n");
                    aguardar();
            }
        }

    } while ((strcmp(tipo, "vendedor") == 0 && opcao != 7) || (strcmp(tipo, "comprador") == 0 && opcao != 4));

    return 0;
}
