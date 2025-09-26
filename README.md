# Trabalho: War Estruturado em C

Repositório do trabalho da disciplina **Estrutura de Dados**, do curso de **Engenharia de Software** da **UNESA (Universidade Estácio de Sá)**.

---

## Descrição

Este projeto tem como objetivo desenvolver, em linguagem **C**, o jogo War Estruturado, dividido em três níveis de complexidade. A proposta é construir progressivamente funcionalidades relacionadas ao cadastro, manipulação e batalha de territórios, utilizando técnicas fundamentais da programação estruturada.

---

## Níveis do Projeto

- **Nível Novato**  
  Cadastro dos territórios do jogo War, usando uma `struct` chamada `Territorio` com os campos: nome, cor do exército e quantidade de tropas. Os dados de 5 territórios são cadastrados via terminal e exibidos ao final.

- **Nível Aventureiro**  
  Implementação da funcionalidade de ataque entre territórios, permitindo a seleção de territórios atacante e defensor, simulação de batalhas com rolagem de dados aleatórios, atualização de controle e tropas, uso de ponteiros para manipulação dos territórios e alocação dinâmica de memória para flexibilidade no cadastro.

- **Nível Mestre**  
  Adição de missões estratégicas automáticas para cada jogador, incluindo sorteio automático a partir de um vetor de missões, consulta de missão durante o jogo para checar condição de vitória, organização modular do código, uso avançado de ponteiros, passagem de parâmetros por valor e referência, e gerenciamento eficiente de memória.

---

## Como compilar

Certifique-se de ter o compilador `gcc` instalado e rode o seguinte comando no terminal:

```bash
gcc war.c -o war
```

---

## Como executar

Após compilar, execute o programa com:

```bash
./war
```

O programa solicitará a entrada dos dados para os territórios e, em seguida, permitirá as operações de batalha e consulta de missões.

---

## Estrutura do projeto

- `war.c`: Código-fonte principal do programa em C.

- `.gitignore`: Arquivo para ignorar arquivos compilados e temporários.

- `README.md`: Documento com a descrição do projeto, instruções de uso e informações complementares.

- `LICENSE`: Arquivo contendo a licença de uso do projeto (MIT License).

---

## Autor

Enei - Curso de Engenharia de Software - UNESA

---

## Licença

Este projeto está sob a licença MIT. Veja o arquivo LICENSE para mais detalhes.