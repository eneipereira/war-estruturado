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

// Definição da estrutura Jogador
// Esta struct armazena as informações de cada jogador, incluindo sua missão estratégica
typedef struct {
    char nome[30];    // Nome do jogador
    char cor[10];     // Cor do exército do jogador
    char* missao;     // Missão estratégica do jogador (alocada dinamicamente)
} Jogador;

// Vetor global de missões pré-definidas
// Define as 8 possíveis missões estratégicas que podem ser atribuídas aos jogadores
const char* MISSOES_DISPONIVEIS[] = {
    "Conquistar 3 territórios consecutivos",
    "Eliminar todas as tropas da cor vermelha",
    "Conquistar 5 territórios com pelo menos 10 tropas cada",
    "Dominar todos os territórios de duas cores diferentes",
    "Acumular 100 tropas em seus territórios",
    "Conquistar o território com maior número de tropas",
    "Ter presença em pelo menos 70% dos territórios do mapa",
    "Eliminar completamente um jogador adversário (uma cor)"
};

// Total de missões disponíveis no vetor
const int TOTAL_MISSOES = 8;

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

// Função para liberar a memória alocada dinamicamente dos territórios
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("Memória dos territórios liberada com sucesso!\n");
    }
}

// Função para liberar a memória alocada dinamicamente das missões dos jogadores
// Parâmetros: jogadores (array de Jogador), quantidade (número de jogadores)
void liberarMissoes(Jogador* jogadores, int quantidade) {
    if (jogadores != NULL) {
        for (int i = 0; i < quantidade; i++) {
            if (jogadores[i].missao != NULL) {
                free(jogadores[i].missao);
                jogadores[i].missao = NULL;
            }
        }
        free(jogadores);
        printf("Memória das missões liberada com sucesso!\n");
    }
}

// Função para exibir o cabeçalho do sistema
void exibirCabecalho() {
    printf("=========================================\n");
    printf("       SISTEMA WAR - NÍVEL MESTRE\n");
    printf("     COM MISSÕES ESTRATÉGICAS\n");
    printf("=========================================\n\n");
}

// Função para atribuir missão aleatória a um jogador
// Utiliza strcpy para copiar a missão sorteada para a memória alocada do jogador
// Parâmetros: destino (ponteiro para string destino), missoes (array de strings),
//             totalMissoes (quantidade total de missões disponíveis)
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    // Sorteia um índice aleatório dentro do range de missões disponíveis
    int indiceSorteado = rand() % totalMissoes;
    
    // Copia a missão sorteada para o destino (passagem por referência)
    strcpy(destino, missoes[indiceSorteado]);
}

// Função para exibir a missão de um jogador
// Recebe a missão por VALOR para apenas exibição (não modifica)
// Parâmetros: nomeJogador (nome do jogador), missao (string da missão)
void exibirMissao(const char* nomeJogador, char missao[]) {
    printf("\n🎯 MISSÃO ESTRATÉGICA DE %s 🎯\n", nomeJogador);
    printf("Objetivo: %s\n", missao);
    printf("=========================================\n\n");
}

// Função para verificar se a missão do jogador foi cumprida
// Recebe missão por REFERÊNCIA para poder analisá-la sem cópia
// Parâmetros: missao (missão do jogador), mapa (array de territórios),
//             tamanho (quantidade de territórios), corJogador (cor do jogador)
// Retorna: 1 se missão cumprida, 0 caso contrário
int verificarMissao(char* missao, Territorio* mapa, int tamanho, const char* corJogador) {
    // Variáveis auxiliares para verificações
    int territoriosJogador = 0;
    int tropasTotais = 0;
    int territorios10Tropas = 0;
    int maiorTropas = 0;
    int territorioMaiorTropasConquistado = 0;
    
    // Primeira passagem: coletar estatísticas do mapa
    for (int i = 0; i < tamanho; i++) {
        // Conta territórios e tropas do jogador
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            territoriosJogador++;
            tropasTotais += mapa[i].tropas;
            
            if (mapa[i].tropas >= 10) {
                territorios10Tropas++;
            }
        }
        
        // Identifica território com maior número de tropas
        if (mapa[i].tropas > maiorTropas) {
            maiorTropas = mapa[i].tropas;
        }
    }
    
    // Segunda passagem: verificar se jogador tem o território com mais tropas
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas == maiorTropas) {
            territorioMaiorTropasConquistado = 1;
            break;
        }
    }
    
    // Verificações específicas de cada tipo de missão
    
    // Missão 1: Conquistar 3 territórios consecutivos
    if (strstr(missao, "3 territórios consecutivos") != NULL) {
        int consecutivos = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                consecutivos++;
                if (consecutivos >= 3) {
                    return 1;
                }
            } else {
                consecutivos = 0;
            }
        }
    }
    
    // Missão 2: Eliminar todas as tropas da cor vermelha
    if (strstr(missao, "cor vermelha") != NULL) {
        int temVermelho = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcasecmp(mapa[i].cor, "vermelho") == 0 || 
                strcasecmp(mapa[i].cor, "vermelha") == 0 ||
                strcasecmp(mapa[i].cor, "red") == 0) {
                temVermelho = 1;
                break;
            }
        }
        if (!temVermelho) {
            return 1;
        }
    }
    
    // Missão 3: Conquistar 5 territórios com pelo menos 10 tropas cada
    if (strstr(missao, "5 territórios com pelo menos 10 tropas") != NULL) {
        if (territorios10Tropas >= 5) {
            return 1;
        }
    }
    
    // Missão 4: Dominar todos os territórios de duas cores diferentes
    if (strstr(missao, "duas cores diferentes") != NULL) {
        // Verifica se jogador domina todos os territórios (simplificação)
        if (territoriosJogador >= tamanho - 1) {
            return 1;
        }
    }
    
    // Missão 5: Acumular 100 tropas em seus territórios
    if (strstr(missao, "100 tropas") != NULL) {
        if (tropasTotais >= 100) {
            return 1;
        }
    }
    
    // Missão 6: Conquistar o território com maior número de tropas
    if (strstr(missao, "maior número de tropas") != NULL) {
        if (territorioMaiorTropasConquistado) {
            return 1;
        }
    }
    
    // Missão 7: Ter presença em pelo menos 70% dos territórios
    if (strstr(missao, "70%") != NULL) {
        float percentual = (float)territoriosJogador / tamanho * 100;
        if (percentual >= 70.0) {
            return 1;
        }
    }
    
    // Missão 8: Eliminar completamente um jogador adversário
    if (strstr(missao, "Eliminar completamente") != NULL) {
        // Verifica quantas cores diferentes existem no mapa
        int coresUnicas = 0;
        char coresEncontradas[10][10];
        
        for (int i = 0; i < tamanho; i++) {
            int corJaContada = 0;
            for (int j = 0; j < coresUnicas; j++) {
                if (strcmp(coresEncontradas[j], mapa[i].cor) == 0) {
                    corJaContada = 1;
                    break;
                }
            }
            if (!corJaContada) {
                strcpy(coresEncontradas[coresUnicas], mapa[i].cor);
                coresUnicas++;
            }
        }
        
        // Se só há 2 cores ou menos, significa que eliminou pelo menos uma
        if (coresUnicas <= 2) {
            return 1;
        }
    }
    
    return 0; // Missão ainda não cumprida
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
    // Necessário para sortear missões e simular batalhas
    srand(time(NULL));
    
    // Variáveis principais
    int quantidadeTerritorios;
    int quantidadeJogadores;
    Territorio *territorios;
    Jogador *jogadores;
    
    // Exibir cabeçalho
    exibirCabecalho();
    
    // ========== FASE 1: CONFIGURAÇÃO DO JOGO ==========
    
    // Solicitar quantidade de jogadores
    printf("Quantos jogadores irão participar? ");
    while (scanf("%d", &quantidadeJogadores) != 1 || quantidadeJogadores < 2) {
        printf("Erro! Digite um número válido (mínimo 2 jogadores): ");
        limparBuffer();
    }
    limparBuffer();
    
    // Alocar memória dinamicamente para os jogadores
    jogadores = (Jogador*)calloc(quantidadeJogadores, sizeof(Jogador));
    if (jogadores == NULL) {
        printf("Erro: Não foi possível alocar memória para jogadores!\n");
        return 1;
    }
    
    // Cadastrar informações dos jogadores
    printf("\n=== CADASTRO DOS JOGADORES ===\n\n");
    for (int i = 0; i < quantidadeJogadores; i++) {
        printf("--- JOGADOR %d ---\n", i + 1);
        
        printf("Digite o nome do jogador: ");
        fgets(jogadores[i].nome, sizeof(jogadores[i].nome), stdin);
        jogadores[i].nome[strcspn(jogadores[i].nome, "\n")] = '\0';
        
        printf("Digite a cor do exército do jogador: ");
        fgets(jogadores[i].cor, sizeof(jogadores[i].cor), stdin);
        jogadores[i].cor[strcspn(jogadores[i].cor, "\n")] = '\0';
        
        // Alocar memória para a missão do jogador (máximo 100 caracteres)
        jogadores[i].missao = (char*)malloc(100 * sizeof(char));
        if (jogadores[i].missao == NULL) {
            printf("Erro: Não foi possível alocar memória para missão!\n");
            // Liberar memória já alocada
            for (int j = 0; j < i; j++) {
                free(jogadores[j].missao);
            }
            free(jogadores);
            return 1;
        }
        
        // Atribuir missão aleatória ao jogador (passagem por referência)
        atribuirMissao(jogadores[i].missao, MISSOES_DISPONIVEIS, TOTAL_MISSOES);
        
        printf("✓ Jogador cadastrado com sucesso!\n\n");
    }
    
    // Exibir missões de cada jogador (passagem por valor para exibição)
    printf("\n=========================================\n");
    printf("    MISSÕES ESTRATÉGICAS ATRIBUÍDAS\n");
    printf("=========================================\n");
    for (int i = 0; i < quantidadeJogadores; i++) {
        exibirMissao(jogadores[i].nome, jogadores[i].missao);
    }
    
    // Solicitar quantidade de territórios ao usuário
    printf("\nQuantos territórios deseja cadastrar? ");
    while (scanf("%d", &quantidadeTerritorios) != 1 || quantidadeTerritorios < 2) {
        printf("Erro! Digite um número válido (mínimo 2 territórios): ");
        limparBuffer();
    }
    limparBuffer();
    
    // Alocar memória dinamicamente para os territórios
    territorios = alocarTerritorios(quantidadeTerritorios);
    
    // ========== FASE 2: CADASTRO DE TERRITÓRIOS ==========
    
    printf("\n=== FASE DE CADASTRO DOS TERRITÓRIOS ===\n\n");
    printf("Você irá cadastrar %d territórios.\n", quantidadeTerritorios);
    printf("Para cada território, informe: nome, cor do exército e número de tropas.\n\n");
    
    // Cadastrar todos os territórios usando ponteiros
    for (int i = 0; i < quantidadeTerritorios; i++) {
        cadastrarTerritorio(&territorios[i], i);
    }
    
    // ========== FASE 3: LOOP PRINCIPAL DO JOGO ==========
    
    int opcao;
    int jogoAtivo = 1;
    int vencedorMissao = -1; // Índice do jogador que completou missão (-1 = nenhum)
    
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
                
                // Verificar missões de cada jogador (passagem por referência)
                printf("\n🔍 Verificando missões estratégicas...\n");
                for (int i = 0; i < quantidadeJogadores; i++) {
                    if (verificarMissao(jogadores[i].missao, territorios, 
                                       quantidadeTerritorios, jogadores[i].cor)) {
                        printf("\n🎉🎊 MISSÃO CUMPRIDA! 🎊🎉\n");
                        printf("Jogador %s completou sua missão estratégica!\n", jogadores[i].nome);
                        printf("Missão: %s\n", jogadores[i].missao);
                        vencedorMissao = i;
                        jogoAtivo = 0;
                        break;
                    }
                }
                
                // Se nenhuma missão foi cumprida, verificar vitória por dominação total
                if (jogoAtivo && verificarVencedor(territorios, quantidadeTerritorios)) {
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
    
    // ========== FASE 4: FINALIZAÇÃO E RESULTADOS ==========
    
    // Exibir territórios finais
    if (opcao != 1) {  // Só exibe se não acabou de exibir
        printf("\n=== ESTADO FINAL DOS TERRITÓRIOS ===\n");
        exibirTerritorios(territorios, quantidadeTerritorios);
    }
    
    // Exibir vencedor final
    if (vencedorMissao >= 0) {
        printf("\n=========================================\n");
        printf("       🏆 VITÓRIA POR MISSÃO! 🏆\n");
        printf("=========================================\n");
        printf("Vencedor: %s (%s)\n", jogadores[vencedorMissao].nome, 
               jogadores[vencedorMissao].cor);
        printf("Missão cumprida: %s\n", jogadores[vencedorMissao].missao);
        printf("=========================================\n");
    }
    
    // Liberar memória alocada dinamicamente
    liberarMemoria(territorios);
    liberarMissoes(jogadores, quantidadeJogadores);
    
    printf("\nObrigado por jogar WAR Estruturado - Nível Mestre!\n");
    printf("=========================================\n");
    
    return 0;
}