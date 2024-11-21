#include <stdio.h>
#include <string.h>

// Funções para as opções do login
void sair() {
    printf("Programa encerrado\n");
}

int validarLogin() {
    char cpf[15], senha[20];
    char cpfArquivo[15], senhaArquivo[20];
    char linha[150];
    FILE *arquivo;

    // Abrir o arquivo para leitura
    arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Solicitar CPF e senha do usuário
    printf("Digite o CPF: ");
    getchar();
    fgets(cpf, sizeof(cpf), stdin);
    printf("Digite a senha: ");
    fgets(senha, sizeof(senha), stdin);

    // Remover o '\n' ao final de CPF e senha, se existir
    cpf[strcspn(cpf, "\n")] = '\0';
    senha[strcspn(senha, "\n")] = '\0';

    // Ler o arquivo linha por linha e validar o login
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Procurar e capturar o CPF do arquivo
        if (strncmp(linha, "Cpf: ", 5) == 0) {
            strcpy(cpfArquivo, linha + 5);
            cpfArquivo[strcspn(cpfArquivo, "\n")] = '\0'; // Remover o '\n'
        }
        // Procurar e capturar a senha do arquivo
        else if (strncmp(linha, "Senha: ", 7) == 0) {
            strcpy(senhaArquivo, linha + 7);
            senhaArquivo[strcspn(senhaArquivo, "\n")] = '\0'; // Remover o '\n'

            // Verificar se CPF e senha correspondem
            if (strcmp(cpf, cpfArquivo) == 0 && strcmp(senha, senhaArquivo) == 0) {
                fclose(arquivo);
                printf("Login bem-sucedido!\n");
                
                return 0;
            }
        }
    }

    // Fechar o arquivo e informar que o login falhou
    fclose(arquivo);
    printf("CPF ou senha inválidos.\n");
    return 1;
}


int criaradm() {
      char nome[100], cpf[15], senha[20];

      // Abrir o arquivo para escrita
      FILE *arquivo = fopen("usuarios.txt", "a"); // O "a" abre para anexar ao final do arquivo
      if (arquivo == NULL) {
          // Se o arquivo não abrir corretamente, exibe uma mensagem de erro
          printf("Erro ao abrir o arquivo.\n");
          return 1;
      }
      getchar();
      // Solicitar informações ao usuário
      printf("Digite o nome do usuário:");
      fgets(nome, sizeof(nome), stdin); 
      printf("Digite o CPF do usuário: ");
      fgets(cpf, sizeof(cpf), stdin);
      printf("Digite a senha do usuário: ");
      fgets(senha, sizeof(senha), stdin);

      // Escrever os dados no arquivo
      fprintf(arquivo, "Nome: %s", nome);
      fprintf(arquivo, "Cpf: %s", cpf);
      fprintf(arquivo, "Senha: %s", senha);
  
      // Fechar o arquivo
      fclose(arquivo);

      printf("Dados armazenados com sucesso!\n");

      return 0;
  }


int main() {
    int opcao;

    // Loop principal do programa
    do {
        printf("\nMenu administrativo");
        printf("\nSelecione uma opção:\n");
        printf("1. Login\n");
        printf("2. Cadastrar\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Executa a opção escolhida
        switch (opcao) {
            case 1:
                validarLogin();
                break;
            case 2:
                criaradm();
                break;
            case 3:
                sair();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);  // O loop continua até o usuário escolher a opção 3 (Sair)

    return 0;
}

