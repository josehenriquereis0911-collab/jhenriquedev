#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define SENHA_ADMIN "admin"

typedef struct {
    int id;
    char nome[50];
    char senha[20];     
    int ativo;
} Funcionario;
                                                                                                                                
typedef struct {
    int id_funcionario;                                                                            
    time_t data_hora;
    char tipo; 
} RegistroPonto;

Funcionario funcionarios[50];
RegistroPonto registros[500];
int total_funcionarios = 0;
int total_registros = 0;

void menu_funcionario(int id);
int autenticar_funcionario();
void registrar_ponto(int id);
void meus_registros(int id);
void menu_adm();
void cadastrar_funcionario();
void listar_funcionarios();
void desativar_funcionario();
void relatorio();
void limpar_buffer();

int main() {
    funcionarios[0].id = 1;
    strcpy(funcionarios[0].nome, "Administrador");
    strcpy(funcionarios[0].senha, SENHA_ADMIN);
    funcionarios[0].ativo = 1;
    total_funcionarios = 1;

    char opcao;
    do {
        system("cls");
        printf("=== SISTEMA DE PONTO ELETRONICO ===\n\n");
        printf("1 - Login usuario\n");
        printf("2 - Login administrador\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);
        limpar_buffer();

        switch(opcao) {
            case '1': {
                int id = autenticar_funcionario();
                if (id != -1) {
                    menu_funcionario(id);
                }
                break;
            }
            case '2': {
                char senha[20];
                printf("Digite a senha: ");
                scanf("%19s", senha);
                limpar_buffer();
                
                if(strcmp(senha, SENHA_ADMIN) == 0) {
                    menu_adm();
                } else {
                    printf("Senha incorreta!\n");
                    system("pause");
                }
                break;
            }
            case '3':
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                system("pause");
        }
    } while(opcao != '3');
    
    return 0;
}

void menu_funcionario(int id) {
    char opcao;
    do {
        system("cls");
        printf("=== MENU FUNCIONARIO ===\n\n");
        printf("1 - Registrar ponto\n");
        printf("2 - Meus registros\n");
        printf("3 - Voltar\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);
        limpar_buffer();

        switch(opcao) {
            case '1':
                registrar_ponto(id);
                break;
            case '2':
                meus_registros(id);
                break;
            case '3':
                break;
            default:
                printf("Opcao invalida!\n");
                system("pause");
        }
    } while(opcao != '3');
}

int autenticar_funcionario() {
    int id;
    char senha[20];
    
    system("cls");
    printf("=== LOGIN FUNCIONARIO ===\n\n");
    printf("ID do funcionario: ");
    if(scanf("%d", &id) != 1) {
        printf("ID invalido!\n");
        limpar_buffer();
        system("pause");
        return -1;
    }
    limpar_buffer();
    
    printf("Senha: ");
    scanf("%19s", senha);
    limpar_buffer();
    
    for(int i = 0; i < total_funcionarios; i++) {
        if(funcionarios[i].id == id && 
           strcmp(funcionarios[i].senha, senha) == 0 && 
           funcionarios[i].ativo) {
            return id;
        }
    }
    
    printf("ID ou senha incorretos, ou usuario inativo.\n");
    system("pause");
    return -1;
}

void registrar_ponto(int id_funcionario) {
    if(total_registros >= 500) {
        printf("Limite de registros atingido!\n");
        system("pause");
        return;
    }
    
    char opcao;
    system("cls");
    printf("=== REGISTRAR PONTO ===\n\n");
    printf("1 - Entrada\n");
    printf("2 - Saida\n");
    printf("3 - Cancelar\n");
    printf("Escolha: ");
    scanf(" %c", &opcao);
    limpar_buffer();
    
    if(opcao == '1' || opcao == '2') {
        registros[total_registros].id_funcionario = id_funcionario;
        registros[total_registros].data_hora = time(NULL);
        if (opcao == '1') {
            registros[total_registros].tipo = 'E';
        } else {
            registros[total_registros].tipo = 'S';
        }
        total_registros++;
        
        char data_hora[20];
        strftime(data_hora, 20, "%d/%m/%Y %H:%M:%S", localtime(&registros[total_registros-1].data_hora));
        printf("\nPonto registrado com sucesso!\n");
        printf("Tipo: %s\n", (opcao == '1') ? "Entrada" : "Saida");
        printf("Data/hora: %s\n", data_hora);
    }
    
    system("pause");
}

void meus_registros(int id_funcionario) {
    system("cls");
    printf("=== MEUS REGISTROS ===\n\n");
    
    int encontrados = 0;
    char data_hora[20];
    
    for(int i = 0; i < total_registros; i++) {
        if(registros[i].id_funcionario == id_funcionario) {
            strftime(data_hora, 20, "%d/%m/%Y %H:%M:%S", localtime(&registros[i].data_hora));
            if (registros[i].tipo == 'E') {
                printf("%s - %s\n", data_hora, "Entrada");
            } else {
                printf("%s - %s\n", data_hora, "Saida");
}
            encontrados++;
        }
    }
    
    if(!encontrados) {
        printf("Nenhum registro encontrado.\n");
    }
    
    system("pause");
}

void menu_adm() {
    char opcao;
    do {
        system("cls");
        printf("=== MENU ADMINISTRADOR ===\n\n1 - Cadastrar funcionario\n2 - Listar funcionarios\n3 - Desativar funcionario\n4 - Relatorio\n5 - Voltar\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);
        limpar_buffer();
        
        switch(opcao) {
            case '1':
                cadastrar_funcionario();
                break;
            case '2':
                listar_funcionarios();
                break;
            case '3':
                desativar_funcionario();
                break;
            case '4':
                relatorio();
                break;
            case '5':
                break;
            default:
                printf("Opcao invalida!\n");
                system("pause");
        }
    } while(opcao != '5');
}

void cadastrar_funcionario() {
    if(total_funcionarios >= 50) {
        printf("Limite de funcionarios atingido!\n");
        system("pause");
        return;
    }
    
    Funcionario novo;
    system("cls");
    printf("=== CADASTRAR FUNCIONARIO ===\n\n");
    
    printf("ID (numero inteiro): ");
    if(scanf("%d", &novo.id) != 1) {
        printf("ID invalido!\n");
        limpar_buffer();
        system("pause");
        return;
    }
    limpar_buffer();
    
    // Verifica se ID já existe
    for(int i = 0; i < total_funcionarios; i++) {
        if(funcionarios[i].id == novo.id) {
            printf("ID ja cadastrado!\n");
            system("pause");
            return;
        }
    }
    
    printf("Nome: ");
    fgets(novo.nome, 50, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    
    printf("Senha: ");
    fgets(novo.senha, 20, stdin);
    novo.senha[strcspn(novo.senha, "\n")] = '\0';
    
    novo.ativo = 1;
    funcionarios[total_funcionarios++] = novo;
    
    printf("\nFuncionario cadastrado com sucesso!\n");
    system("pause");
}

void listar_funcionarios() {
    system("cls");
    printf("=== LISTA DE FUNCIONARIOS ===\n\n");
    
    if(total_funcionarios == 0) {
        printf("Nenhum funcionario cadastrado.\n");
    } else {
        printf("%-5s %-30s      %-10s\n", "ID", "Nome", "Status");
        printf("----------------------------------------\n");
        
        for(int i = 0; i < total_funcionarios; i++) {
            printf("%-5d %-30s %-10s\n", 
                   funcionarios[i].id, 
                   funcionarios[i].nome,
                   funcionarios[i].ativo ? "Ativo" : "Inativo");
        }
    }
    
    system("pause");
}

void desativar_funcionario() {
    int id;
    
    system("cls");
    printf("=== DESATIVAR FUNCIONARIO ===\n\n");
    
    if(total_funcionarios == 0) {
        printf("Nenhum funcionario cadastrado.\n");
        system("pause");
        return;
    }
    
 
    
    printf("\nFuncionario nao encontrado!\n");
    system("pause");
}

void relatorio() {
    system("cls");
    printf("=== RELATORIO DE PONTOS ===\n\n");
    
    if(total_registros == 0) {
        printf("Nenhum registro de ponto encontrado.\n");
        system("pause");
        return;
    }
    
    char data_hora[20];
    char nome[50];
    
    printf("%-20s %-30s %-10s\n", "Data/Hora", "Funcionario", "Tipo");
    printf("----------------------------------------------------\n");
    
    for(int i = 0; i < total_registros; i++) {
        // Encontra o nome do funcionário
        strcpy(nome, "DESCONHECIDO");
        for(int j = 0; j < total_funcionarios; j++) {
            if(funcionarios[j].id == registros[i].id_funcionario) {
                strcpy(nome, funcionarios[j].nome);
                break;
            }
        }
        
        strftime(data_hora, 20, "%d/%m/%Y %H:%M:%S", localtime(&registros[i].data_hora));
        printf("%-20s %-30s %-10s\n", 
               data_hora, 
               nome, 
               (registros[i].tipo == 'E') ? "Entrada" : "Saida");
    }
    
    system("pause");
}

void limpar_buffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}