#include <stdio.h>
#include <string.h>

// Definição da estrutura Territorio
// Esta struct armazena as informações básicas de cada território no jogo
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Constante para definir o número total de territórios
#define TOTAL_TERRITORIOS 5

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para exibir o cabeçalho do sistema
void exibirCabecalho() {
    printf("========================================\n");
    printf("    SISTEMA DE CADASTRO DE TERRITÓRIOS\n");
    printf("========================================\n\n");
}

// Função simplificada para cadastrar território sem ponteiro
Territorio cadastrarTerritorio(int numero) {
    Territorio novoTerritorio;
    
    printf("--- CADASTRO DO TERRITÓRIO %d ---\n", numero + 1);
    
    // Entrada do nome do território
    printf("Digite o nome do território: ");
    fgets(novoTerritorio.nome, sizeof(novoTerritorio.nome), stdin);
    novoTerritorio.nome[strcspn(novoTerritorio.nome, "\n")] = '\0';
    
    // Entrada da cor do exército
    printf("Digite a cor do exército: ");
    fgets(novoTerritorio.cor, sizeof(novoTerritorio.cor), stdin);
    novoTerritorio.cor[strcspn(novoTerritorio.cor, "\n")] = '\0';
    
    // Entrada da quantidade de tropas
    printf("Digite a quantidade de tropas: ");
    while (scanf("%d", &novoTerritorio.tropas) != 1 || novoTerritorio.tropas < 0) {
        printf("Erro! Digite um número válido para as tropas: ");
        limparBuffer();
    }
    limparBuffer(); // Limpa o buffer após scanf
    
    printf("\n");
    
    return novoTerritorio; // Retorna a struct completa
}

// Função para exibir os dados de todos os territórios
void exibirTerritorios(Territorio territorios[], int quantidade) {
    printf("========================================\n");
    printf("       TERRITÓRIOS CADASTRADOS\n");
    printf("========================================\n\n");
    
    // Laço para percorrer e exibir cada território
    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("----------------------------------------\n");
    }
}

// Função para validar dados cadastrados
int validarDados(Territorio territorios[], int quantidade) {
    int dadosValidos = 1;
    
    for (int i = 0; i < quantidade; i++) {
        if (strlen(territorios[i].nome) == 0 || 
            strlen(territorios[i].cor) == 0 || 
            territorios[i].tropas < 0) {
            dadosValidos = 0;
            printf("Erro: Dados inválidos no território %d\n", i + 1);
        }
    }
    
    return dadosValidos;
}

// Função para exibir mensagem de finalização
void exibirRodape() {
    printf("\nCadastro concluído com sucesso!\n");
    printf("Todos os territórios foram registrados.\n");
    printf("========================================\n");
}

// Função principal do programa
int main() {
    // Declaração do vetor de structs para armazenar os territórios
    Territorio territorios[TOTAL_TERRITORIOS];
    
    // Exibe o cabeçalho do sistema
    exibirCabecalho();
    
    printf("Você irá cadastrar %d territórios.\n", TOTAL_TERRITORIOS);
    printf("Para cada território, informe: nome, cor do exército e número de tropas.\n\n");
    
    // Laço para cadastrar todos os territórios (SEM PONTEIRO - usando retorno)
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        territorios[i] = cadastrarTerritorio(i);
    }
    
    // Exibe todos os territórios cadastrados
    exibirTerritorios(territorios, TOTAL_TERRITORIOS);
    
    // Exibe mensagem de finalização
    exibirRodape();
    
    return 0;
}
