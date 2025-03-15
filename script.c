#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 100
#define MAX_PACIENTES 100

// Estrutura para armazenar dados dos funcionários
typedef struct {
    char nome[100];
    char login[50];
    char senha[50];
} Funcionario;

// Estrutura para armazenar dados dos pacientes
typedef struct {
    char nome[100];
    char cpf[15];
    char telefone[20];
    char endereco[200];
    int idade;
    char email[100];
    char data_diagnostico[12];
    char comorbidades[100];
} Paciente;

Funcionario funcionarios[MAX_USUARIOS];
Paciente pacientes[MAX_PACIENTES];
int totalFuncionarios = 0, totalPacientes = 0;

void cadastrarFuncionario();
int loginFuncionario();
void cadastrarPaciente();
void listarPacientes();
void salvarDados();
void carregarDados();

int main() {
    int opcao;
    carregarDados();

    printf("\nSistema de Cadastro e Diagnóstico de Pacientes com COVID-19\n");
    printf("1 - Login\n2 - Cadastrar Funcionario\n3 - Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    getchar();

    if (opcao == 2) {
        cadastrarFuncionario();
        return main();
    } else if (opcao == 1) {
        if (!loginFuncionario()) {
            printf("Login falhou. Encerrando...\n");
            return 0;
        }
    } else {
        return 0;
    }

    while (1) {
        printf("\nMenu Principal\n");
        printf("1 - Cadastrar Paciente\n2 - Listar Pacientes\n3 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarPaciente();
                break;
            case 2:
                listarPacientes();
                break;
            case 3:
                salvarDados();
                return 0;
            default:
                printf("Opcao invalida!\n");
        }
    }
    return 0;
}

void cadastrarFuncionario() {
    printf("\nCadastro de Funcionario\n");
    printf("Nome: ");
    fgets(funcionarios[totalFuncionarios].nome, 100, stdin);
    printf("Login: ");
    fgets(funcionarios[totalFuncionarios].login, 50, stdin);
    printf("Senha: ");
    fgets(funcionarios[totalFuncionarios].senha, 50, stdin);
    totalFuncionarios++;
    printf("Funcionario cadastrado com sucesso!\n");
}

int loginFuncionario() {
    char login[50], senha[50];
    printf("\nLogin\n");
    printf("Login: ");
    fgets(login, 50, stdin);
    printf("Senha: ");
    fgets(senha, 50, stdin);

    for (int i = 0; i < totalFuncionarios; i++) {
        if (strcmp(funcionarios[i].login, login) == 0 && strcmp(funcionarios[i].senha, senha) == 0) {
            printf("Login bem-sucedido!\n");
            return 1;
        }
    }
    printf("Login falhou!\n");
    return 0;
}

void cadastrarPaciente() {
    printf("\nCadastro de Paciente\n");
    printf("Nome: ");
    fgets(pacientes[totalPacientes].nome, 100, stdin);
    printf("CPF: ");
    fgets(pacientes[totalPacientes].cpf, 15, stdin);
    printf("Telefone: ");
    fgets(pacientes[totalPacientes].telefone, 20, stdin);
    printf("Endereco: ");
    fgets(pacientes[totalPacientes].endereco, 200, stdin);
    printf("Idade: ");
    scanf("%d", &pacientes[totalPacientes].idade);
    getchar();
    printf("Email: ");
    fgets(pacientes[totalPacientes].email, 100, stdin);
    printf("Data do Diagnostico: ");
    fgets(pacientes[totalPacientes].data_diagnostico, 12, stdin);
    printf("Comorbidades: ");
    fgets(pacientes[totalPacientes].comorbidades, 100, stdin);
    totalPacientes++;
    printf("Paciente cadastrado com sucesso!\n");
}

void listarPacientes() {
    printf("\nLista de Pacientes\n");
    for (int i = 0; i < totalPacientes; i++) {
        printf("Nome: %sCPF: %sTelefone: %sIdade: %d\n", pacientes[i].nome, pacientes[i].cpf, pacientes[i].telefone, pacientes[i].idade);
        printf("-------------------------\n");
    }
}

void salvarDados() {
    FILE *file = fopen("pacientes.txt", "w");
    for (int i = 0; i < totalPacientes; i++) {
        fprintf(file, "%s%s%s%d\n", pacientes[i].nome, pacientes[i].cpf, pacientes[i].telefone, pacientes[i].idade);
    }
    fclose(file);
}
