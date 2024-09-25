#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição de uma struct para endereço
typedef struct {
    char rua[50];
    int numero;
    char bairro[30];
    char cidade[30];
    char estado[3];
    char cep[10];
} Endereco;

// Definição da struct para contato
typedef struct {
    char nome[30];
    char sobrenome[30];
    char **telefones;    // Ponteiro para vetor de telefones
    int numTelefones;    // Número de telefones
    Endereco *enderecos; // Ponteiro para vetor de endereços
    int numEnderecos;    // Número de endereços
    char **emails;       // Ponteiro para vetor de emails
    int numEmails;       // Número de emails
    char aniversario[11]; // Data de aniversário (dd/mm/aaaa)
} Contato;

// Vetor de contatos e contador de contatos
Contato *contatos = NULL;
int numContatos = 0;

// Função para adicionar um contato
void adicionarContato() {
    contatos = realloc(contatos, (numContatos + 1) * sizeof(Contato)); // Redimensiona o array de contatos
    Contato *novoContato = &contatos[numContatos]; // Referencia o próximo contato disponível
    numContatos++; // Incrementa o número de contatos

    // Preenche os dados do contato
    printf("Nome: ");
    scanf(" %[^\n]", novoContato->nome);
    printf("Sobrenome: ");
    scanf(" %[^\n]", novoContato->sobrenome);
    printf("Aniversário (dd/mm/aaaa): ");
    scanf(" %[^\n]", novoContato->aniversario);

    // Adiciona telefones
    printf("Quantos telefones deseja adicionar? ");
    scanf("%d", &novoContato->numTelefones);
    novoContato->telefones = malloc(novoContato->numTelefones * sizeof(char*));
    for (int i = 0; i < novoContato->numTelefones; i++) {
        novoContato->telefones[i] = malloc(15 * sizeof(char)); // Aloca espaço para cada telefone
        printf("Telefone %d: ", i + 1);
        scanf(" %[^\n]", novoContato->telefones[i]);
    }

    // Adiciona emails
    printf("Quantos emails deseja adicionar? ");
    scanf("%d", &novoContato->numEmails);
    novoContato->emails = malloc(novoContato->numEmails * sizeof(char*));
    for (int i = 0; i < novoContato->numEmails; i++) {
        novoContato->emails[i] = malloc(50 * sizeof(char)); // Aloca espaço para cada email
        printf("Email %d: ", i + 1);
        scanf(" %[^\n]", novoContato->emails[i]);
    }

    // Adiciona endereços
    printf("Quantos endereços deseja adicionar? ");
    scanf("%d", &novoContato->numEnderecos);
    novoContato->enderecos = malloc(novoContato->numEnderecos * sizeof(Endereco));
    for (int i = 0; i < novoContato->numEnderecos; i++) {
        printf("Endereço %d - Rua: ", i + 1);
        scanf(" %[^\n]", novoContato->enderecos[i].rua);
        printf("Número: ");
        scanf("%d", &novoContato->enderecos[i].numero);
        printf("Bairro: ");
        scanf(" %[^\n]", novoContato->enderecos[i].bairro);
        printf("Cidade: ");
        scanf(" %[^\n]", novoContato->enderecos[i].cidade);
        printf("Estado (Sigla): ");
        scanf(" %[^\n]", novoContato->enderecos[i].estado);
        printf("CEP: ");
        scanf(" %[^\n]", novoContato->enderecos[i].cep);
    }

    printf("Contato adicionado com sucesso!\n");
}

// Função para remover um contato
void removerContato() {
    char nome[30];
    printf("Digite o nome do contato a ser removido: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < numContatos; i++) {
        if (strcmp(contatos[i].nome, nome) == 0) {
            // Libera memória dos campos dinâmicos
            for (int j = 0; j < contatos[i].numTelefones; j++) {
                free(contatos[i].telefones[j]);
            }
            free(contatos[i].telefones);
            
            for (int j = 0; j < contatos[i].numEmails; j++) {
                free(contatos[i].emails[j]);
            }
            free(contatos[i].emails);
            
            free(contatos[i].enderecos);

            // Move os contatos para preencher o espaço
            for (int j = i; j < numContatos - 1; j++) {
                contatos[j] = contatos[j + 1];
            }
            numContatos--; // Reduz o número de contatos
            contatos = realloc(contatos, numContatos * sizeof(Contato)); // Redimensiona o array de contatos

            printf("Contato removido com sucesso!\n");
            return;
        }
    }
    printf("Contato não encontrado.\n");
}

// Função para buscar um contato por nome
void buscarContatoPorNome() {
    char nome[30];
    printf("Digite o nome do contato a buscar: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < numContatos; i++) {
        if (strcmp(contatos[i].nome, nome) == 0) {
            printf("Contato encontrado:\n");
            printf("Nome: %s %s\n", contatos[i].nome, contatos[i].sobrenome);
            printf("Aniversário: %s\n", contatos[i].aniversario);
            
            printf("Telefones:\n");
            for (int j = 0; j < contatos[i].numTelefones; j++) {
                printf("%s\n", contatos[i].telefones[j]);
            }

            printf("Emails:\n");
            for (int j = 0; j < contatos[i].numEmails; j++) {
                printf("%s\n", contatos[i].emails[j]);
            }

            printf("Endereços:\n");
            for (int j = 0; j < contatos[i].numEnderecos; j++) {
                printf("%s, %d, %s, %s, %s - %s\n", contatos[i].enderecos[j].rua, contatos[i].enderecos[j].numero,
                        contatos[i].enderecos[j].bairro, contatos[i].enderecos[j].cidade,
                        contatos[i].enderecos[j].estado, contatos[i].enderecos[j].cep);
            }
            return;
        }
    }
    printf("Contato não encontrado.\n");
}

// Função para listar todos os contatos
void listarContatos() {
    if (numContatos == 0) {
        printf("Nenhum contato na agenda.\n");
    } else {
        for (int i = 0; i < numContatos; i++) {
            printf("%s %s\n", contatos[i].nome, contatos[i].sobrenome);
        }
    }
}

// Função principal com menu
int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar Contato\n");
        printf("2. Remover Contato\n");
        printf("3. Buscar Contato por Nome\n");
        printf("4. Listar Contatos\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                removerContato();
                break;
            case 3:
                buscarContatoPorNome();
                break;
            case 4:
                listarContatos();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);

    // Libera a memória alocada para os contatos
    for (int i = 0; i < numContatos; i++) {
        for (int j = 0; j < contatos[i].numTelefones; j++) {
            free(contatos[i].telefones[j]);
        }
        free(contatos[i].telefones);
        
        for (int j = 0; j < contatos[i].numEmails; j++) {
            free(contatos[i].emails[j]);
        }
        free(contatos[i].emails);
        
        free(contatos[i].enderecos);
    }
    free(contatos);

    return 0;
}
