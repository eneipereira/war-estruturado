#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura Territorio
// Esta struct armazena as informações básicas de cada território no jogo
typedef struct {
    char nome[30];    // Nome do território (máximo 29 caracteres + '\0')
    char cor[10];     // Cor do exército (máximo 9 caracteres + '\0')
    int tropas;       // Quantidade de tropas no território
} Territorio;

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para alocar memória dinamicamente para os territórios
Territorio* alocarTerritorios(int quantidade) {
    Territorio* territorios = (Territorio*)calloc(quantidade, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro: Não foi possível alocar memória!\n");
        exit(1);
    }
    return territorios;
}

// Função para liberar a memória alocada dinamicamente
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("Memória liberada com sucesso!\n");
    }
}

// Função para exibir o cabeçalho do sistema
void exibirCabecalho() {
    printf("=========================================\n");
    printf("       SISTEMA WAR - NÍVEL AVENTUREIRO\n");
    printf("=========================================\n\n");
}

// Função para cadastrar um território usando ponteiros
void cadastrarTerritorio(Territorio *territorio, int numero) {
    printf("--- CADASTRO DO TERRITÓRIO %d ---\n", numero + 1);
    
    // Entrada do nome do território
    printf("Digite o nome do território: ");
    fgets(territorio->nome, sizeof(territorio->nome), stdin);
    territorio->nome[strcspn(territorio->nome, "\n")] = '\0';
    
    // Entrada da cor do exército
    printf("Digite a cor do exército: ");
    fgets(territorio->cor, sizeof(territorio->cor), stdin);
    territorio->cor[strcspn(territorio->cor, "\n")] = '\0';
    
    // Entrada da quantidade de tropas
    printf("Digite a quantidade de tropas (mínimo 1): ");
    while (scanf("%d", &territorio->tropas) != 1 || territorio->tropas < 1) {
        printf("Erro! Digite um número válido para as tropas (mínimo 1): ");
        limparBuffer();
    }
    limparBuffer();
    
    printf("\n");
}

// Função para exibir os dados de todos os territórios
void exibirTerritorios(Territorio *territorios, int quantidade) {
    printf("=========================================\n");
    printf("         TERRITÓRIOS CADASTRADOS\n");
    printf("=========================================\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------------------\n");
    }
}

// Função para simular rolagem de dados (1 a 6)
int rolarDados() {
    return (rand() % 6) + 1;
}

// Função principal de ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n*** INÍCIO DA BATALHA ***\n");
    printf("Atacante: %s (%s) com %d tropas\n", 
           atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) com %d tropas\n", 
           defensor->nome, defensor->cor, defensor->tropas);
    
    // Simulação da batalha com dados
    int dadoAtacante = rolarDados();
    int dadoDefensor = rolarDados();
    
    printf("\nRolagem dos dados:\n");
    printf("Atacante (%s): %d\n", atacante->cor, dadoAtacante);
    printf("Defensor (%s): %d\n", defensor->cor, dadoDefensor);
    
    // Determina o vencedor e aplica as consequências
    if (dadoAtacante > dadoDefensor) {
        printf("\n🎯 ATACANTE VENCEU!\n");
        
        // O defensor perde o território
        int tropasTransferidas = defensor->tropas / 2;
        if (tropasTransferidas < 1) tropasTransferidas = 1;
        
        printf("Território %s conquistado!\n", defensor->nome);
        printf("Cor alterada de %s para %s\n", defensor->cor, atacante->cor);
        printf("Tropas transferidas: %d\n", tropasTransferidas);
        
        // Atualiza os dados do defensor (agora do atacante)
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = tropasTransferidas;
        
    } else if (dadoDefensor > dadoAtacante) {
        printf("\n🛡️ DEFENSOR VENCEU!\n");
        printf("Atacante perde 1 tropa por falhar no ataque\n");
        
        // Atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
        
    } else {
        printf("\n⚖️ EMPATE!\n");
        printf("Nenhum território muda de dono, mas atacante perde 1 tropa\n");
        
        // Em caso de empate, atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
    }
    
    printf("\nResultado pós-batalha:\n");
    printf("Atacante: %s (%s) - %d tropas\n", 
           atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - %d tropas\n", 
           defensor->nome, defensor->cor, defensor->tropas);
    printf("*** FIM DA BATALHA ***\n\n");
}

// Função para selecionar território para ataque
int selecionarTerritorio(Territorio *territorios, int quantidade, const char* acao) {
    int escolha;
    
    printf("=== SELEÇÃO DE TERRITÓRIO PARA %s ===\n", acao);
    for (int i = 0; i < quantidade; i++) {
        printf("%d - %s (%s) - %d tropas\n", 
               i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
    
    printf("\nEscolha o território (1-%d): ", quantidade);
    while (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > quantidade) {
        printf("Erro! Digite um número válido (1-%d): ", quantidade);
        limparBuffer();
    }
    limparBuffer();
    
    return escolha - 1; // Retorna índice (0-based)
}

// Função para validar se o ataque é permitido
int validarAtaque(Territorio *atacante, Territorio *defensor) {
    // Não pode atacar território da mesma cor
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("❌ Erro: Não é possível atacar um território da mesma cor!\n");
        return 0;
    }
    
    // Atacante deve ter pelo menos 2 tropas (para manter 1 após o ataque)
    if (atacante->tropas < 2) {
        printf("❌ Erro: O atacante deve ter pelo menos 2 tropas para atacar!\n");
        return 0;
    }
    
    return 1; // Ataque válido
}

// Função para executar rodada de ataque
void executarRodadaAtaque(Territorio *territorios, int quantidade) {
    printf("\n🎯 FASE DE ATAQUE 🎯\n\n");
    
    // Selecionar território atacante
    int indiceAtacante = selecionarTerritorio(territorios, quantidade, "ATACAR");
    
    // Selecionar território defensor
    int indiceDefensor = selecionarTerritorio(territorios, quantidade, "DEFENDER");
    
    // Validar se o ataque é permitido
    if (!validarAtaque(&territorios[indiceAtacante], &territorios[indiceDefensor])) {
        return;
    }
    
    // Executar o ataque
    atacar(&territorios[indiceAtacante], &territorios[indiceDefensor]);
}

// Função para exibir menu principal
int exibirMenu() {
    int opcao;
    
    printf("\n=========================================\n");
    printf("              MENU PRINCIPAL\n");
    printf("=========================================\n");
    printf("1. Exibir territórios\n");
    printf("2. Realizar ataque\n");
    printf("3. Sair do jogo\n");
    printf("=========================================\n");
    printf("Escolha uma opção: ");
    
    while (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 3) {
        printf("Erro! Digite uma opção válida (1-3): ");
        limparBuffer();
    }
    limparBuffer();
    
    return opcao;
}

// Função para verificar se há apenas um vencedor (todas as cores iguais)
int verificarVencedor(Territorio *territorios, int quantidade) {
    char primeiraCor[10];
    strcpy(primeiraCor, territorios[0].cor);
    
    for (int i = 1; i < quantidade; i++) {
        if (strcmp(territorios[i].cor, primeiraCor) != 0) {
            return 0; // Ainda há territórios de cores diferentes
        }
    }
    
    printf("\n🎉 VITÓRIA! 🎉\n");
    printf("O exército %s conquistou todos os territórios!\n", primeiraCor);
    return 1;
}

// Função principal do programa
int main() {
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    // Variáveis principais
    int quantidadeTerritorios;
    Territorio *territorios;
    
    // Exibir cabeçalho
    exibirCabecalho();
    
    // Solicitar quantidade de territórios ao usuário
    printf("Quantos territórios deseja cadastrar? ");
    while (scanf("%d", &quantidadeTerritorios) != 1 || quantidadeTerritorios < 2) {
        printf("Erro! Digite um número válido (mínimo 2 territórios): ");
        limparBuffer();
    }
    limparBuffer();
    
    // Alocar memória dinamicamente para os territórios
    territorios = alocarTerritorios(quantidadeTerritorios);
    
    printf("\n=== FASE DE CADASTRO ===\n\n");
    printf("Você irá cadastrar %d territórios.\n", quantidadeTerritorios);
    printf("Para cada território, informe: nome, cor do exército e número de tropas.\n\n");
    
    // Cadastrar todos os territórios usando ponteiros
    for (int i = 0; i < quantidadeTerritorios; i++) {
        cadastrarTerritorio(&territorios[i], i);
    }
    
    // Loop principal do jogo
    int opcao;
    int jogoAtivo = 1;
    
    while (jogoAtivo) {
        opcao = exibirMenu();
        
        switch (opcao) {
            case 1:
                // Exibir territórios atualizados
                exibirTerritorios(territorios, quantidadeTerritorios);
                break;
                
            case 2:
                // Realizar ataque entre territórios
                executarRodadaAtaque(territorios, quantidadeTerritorios);
                
                // Verificar se há um vencedor
                if (verificarVencedor(territorios, quantidadeTerritorios)) {
                    jogoAtivo = 0;
                }
                break;
                
            case 3:
                // Sair do jogo
                printf("\n👋 Encerrando o jogo...\n");
                jogoAtivo = 0;
                break;
                
            default:
                printf("Opção inválida!\n");
                break;
        }
    }
    
    // Exibir territórios finais
    if (opcao != 1) {  // Só exibe se não acabou de exibir
        printf("\n=== ESTADO FINAL DOS TERRITÓRIOS ===\n");
        exibirTerritorios(territorios, quantidadeTerritorios);
    }
    
    // Liberar memória alocada dinamicamente
    liberarMemoria(territorios);
    
    printf("\nObrigado por jogar WAR Estruturado!\n");
    printf("=========================================\n");
    
    return 0;
}