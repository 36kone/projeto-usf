#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura de cliente
struct cliente {
    char nome[31];
    int idade;
    char cpf[15];
    char telefone[15];
    char prioridade[11];
    char tomou_vacina;
    char data_vacina[11];
    int id_paciente;
};

// Variáveis globais
struct cliente *Lista = NULL;
int quantidade = 0;

// Função para listar todos os pacientes
void listarClientes() {
    if (quantidade == 0) {
        printf("\nNenhum paciente cadastrado.\n");
        return;
    }

    printf("\n=== Lista de Pacientes ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("ID: %d\n", Lista[i].id_paciente);
        printf("Nome: %s\n", Lista[i].nome);
        printf("Idade: %d\n", Lista[i].idade);
        printf("CPF: %s\n", Lista[i].cpf);
        printf("Telefone: %s\n", Lista[i].telefone);
        printf("Prioridade: %s\n", Lista[i].prioridade);
        printf("Tomou vacina: %c\n", Lista[i].tomou_vacina);
        printf("Data da vacina: %s\n", Lista[i].data_vacina);
        printf("--------------------------\n");
    }
}

// Função para deletar um paciente pelo CPF
void deletarClientePorCPF(char cpf[15]) {
    int encontrado = 0;
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(Lista[i].cpf, cpf) == 0) {
            encontrado = 1;
            for (int j = i; j < quantidade - 1; j++) {
                Lista[j] = Lista[j + 1];
            }
            quantidade--;
            Lista = realloc(Lista, quantidade * sizeof(struct cliente));
            printf("\nPaciente com CPF %s removido com sucesso.\n", cpf);
            return;
        }
    }

    if (!encontrado) {
        printf("\nPaciente com CPF %s não encontrado.\n", cpf);
    }
}

// Função para adicionar pacientes de exemplo
void carregarPacientesTeste() {
    quantidade = 2;
    Lista = malloc(quantidade * sizeof(struct cliente));

    strcpy(Lista[0].nome, "Ana Clara");
    Lista[0].idade = 28;
    strcpy(Lista[0].cpf, "11122233344");
    strcpy(Lista[0].telefone, "999999999");
    strcpy(Lista[0].prioridade, "Alta");
    Lista[0].tomou_vacina = 'S';
    strcpy(Lista[0].data_vacina, "10/01/2024");
    Lista[0].id_paciente = 1;

    strcpy(Lista[1].nome, "Carlos Silva");
    Lista[1].idade = 35;
    strcpy(Lista[1].cpf, "55566677788");
    strcpy(Lista[1].telefone, "988888888");
    strcpy(Lista[1].prioridade, "Baixa");
    Lista[1].tomou_vacina = 'N';
    strcpy(Lista[1].data_vacina, "--");
    Lista[1].id_paciente = 2;
}

// Menu interativo
int main() {
    int opcao;
    char cpf[15];

    carregarPacientesTeste();

    do {
        printf("\n=== Menu ===\n");
        printf("1 - Listar pacientes\n");
        printf("2 - Remover paciente por CPF\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch(opcao) {
            case 1:
                listarClientes();
                break;
            case 2:
                printf("Digite o CPF do paciente a remover: ");
                fgets(cpf, sizeof(cpf), stdin);
                cpf[strcspn(cpf, "\n")] = 0; // Remove \n
                deletarClientePorCPF(cpf);
                break;
            case 3:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while(opcao != 0);

    free(Lista);
    return 0;
}
