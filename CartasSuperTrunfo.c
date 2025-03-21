#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Biblioteca necessária para usar a função system()

// Função para mudar a codificação para UTF-8 no CMD
void configurar_codificacao() {
    system("chcp 65001"); // Altera a codificação para UTF-8
}

// Estrutura para armazenar os dados das cidades
typedef struct {
    char estado[3];
    char codigo[10];
    char nome[50];
    unsigned long int populacao; // Alterado para unsigned long int
    double pib;
    double area;
    int pontos_turisticos;
    float densidade;
    float pib_per_capita;
    float super_poder; // Novo atributo para o super poder
} Cidade;

// Função para calcular densidade populacional e PIB per capita
void calcular_propriedades(Cidade* c) {
    if (c->area > 0) { // Verifica se a área é maior que zero
        c->densidade = c->populacao / c->area;
    }
    else {
        c->densidade = 0; // Se a área for zero ou negativa, define densidade como 0
    }

    if (c->populacao > 0) { // Verifica se a população é maior que zero
        c->pib_per_capita = c->pib / c->populacao;
    }
    else {
        c->pib_per_capita = 0; // Se a população for zero ou negativa, define PIB per capita como 0
    }
}

// Função para calcular o Super Poder
void calcular_super_poder(Cidade* c) {
    // O Super Poder é a soma de todos os atributos numéricos, sendo inverso da densidade.
    c->super_poder = (float)(c->populacao + c->area + c->pib + c->pontos_turisticos + c->pib_per_capita + (1 / c->densidade));
}

// Função para registrar uma cidade
void registrar_cidade(Cidade* c) {
    printf("\nDigite o estado (sigla, ex: MG): ");
    scanf("%2s", c->estado);
    printf("Digite o codigo da cidade: ");
    scanf("%9s", c->codigo); // Limita a 9 caracteres para evitar overflow
    printf("Digite o nome da cidade: ");
    getchar(); // Consumir o '\n' pendente
    fgets(c->nome, sizeof(c->nome), stdin);
    c->nome[strcspn(c->nome, "\n")] = 0; // Remover o '\n' do fgets
    printf("Digite a população: ");
    scanf("%lu", &c->populacao); // Alterado para unsigned long int
    printf("Digite o PIB (em bilhões): ");
    scanf("%lf", &c->pib);
    printf("Digite a área (km²): ");
    scanf("%lf", &c->area);
    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &c->pontos_turisticos);

    // Calcular propriedades e super poder após o registro
    calcular_propriedades(c);
    calcular_super_poder(c);
}

// Função para exibir os dados de uma cidade
void exibir_cidade(Cidade c) {
    printf("\nCarta:\n");
    printf("Estado: %s\n", c.estado);
    printf("Código: %s\n", c.codigo);
    printf("Nome da Cidade: %s\n", c.nome);
    printf("População: %lu\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f bilhões de reais\n", c.pib);
    printf("Número de Pontos Turísticos: %d\n", c.pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", c.densidade);
    printf("PIB per Capita: %.2f reais\n", c.pib_per_capita);
    printf("Super Poder: %.2f\n", c.super_poder);
}

// Função para comparar as cartas atributo por atributo
void comparar_cartas(Cidade c1, Cidade c2) {
    printf("\nComparação de Cartas:\n");

    // Comparação de População
    printf("População: ");
    printf(c1.populacao > c2.populacao ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");

    // Comparação de Área
    printf("Área: ");
    printf(c1.area > c2.area ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");

    // Comparação de PIB
    printf("PIB: ");
    printf(c1.pib > c2.pib ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");

    // Comparação de Pontos Turísticos
    printf("Pontos Turísticos: ");
    printf(c1.pontos_turisticos > c2.pontos_turisticos ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");

    // Comparação de Densidade Populacional
    printf("Densidade Populacional: ");
    printf(c1.densidade < c2.densidade ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n"); // Menor densidade vence

    // Comparação de PIB per Capita
    printf("PIB per Capita: ");
    printf(c1.pib_per_capita > c2.pib_per_capita ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");

    // Comparação de Super Poder
    printf("Super Poder: ");
    printf(c1.super_poder > c2.super_poder ? "Carta 1 venceu (1)\n" : "Carta 2 venceu (0)\n");
}

int main() {
    // Configura a codificação UTF-8
    configurar_codificacao();

    Cidade carta1, carta2;

    printf("Cadastro da Carta 1:\n");
    registrar_cidade(&carta1);

    printf("\nCadastro da Carta 2:\n");
    registrar_cidade(&carta2);

    printf("\nCartas cadastradas:\n");
    exibir_cidade(carta1);
    exibir_cidade(carta2);

    // Comparar as cartas
    comparar_cartas(carta1, carta2);

    return 0;
}
