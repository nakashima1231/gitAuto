#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// cores pro cmd bonito
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

void helpMenu() {
    printf("Uso:\n");
    printf("-m MessagemCommit (Obrigatoria!)\n");
    printf("--help Menu de ajuda\n");
    printf("Exemplos: \n");
    printf(".\\gitAuto.exe \"consertando bug\"\n");
    printf(".\\gitAuto.exe -m \"consertando bug\"\n");
}

int main(int argc, char* argv[]) {
    char branch[100] = "main";
    char message[256] = "";

    if(argc == 2 && strcmp(argv[1], "--help") == 0) {
        helpMenu();
        return 0;
    }

    // pega a branch padrao do projeto
    FILE* f = popen("git branch --show-current", "r");
    if(f != NULL) {
        if(fgets(branch, sizeof(branch), f) != NULL) {
            branch[strcspn(branch, "\n")] = 0;
        }

        pclose(f);
    }

    // pega a messagem do commit
    for(int i = 1; i < argc; i++) {
        // caso tenha passado a flag -m
        if(strcmp(argv[i], "-m") == 0 && (i + 1) < argc) {
            strncpy(message, argv[++i], sizeof(message) - 1);
            message[sizeof(message) - 1] = '\0';
        }
        // caso nao tenha passado a flag
        else if(message[0] == '\0') {
            strncpy(message, argv[i], sizeof(message) - 1);
            message[sizeof(message) - 1] = '\0';
        } else {
            // digitou qualquer coisa
            printf(RED "[ERRO] Argumento invalido: %s" RESET "\n", argv[i]);
            return 1;
        }
    }

    //mensagem vazia (.\gitAuto)
    if(message[0] == '\0') {
        printf(RED "[ERRO] Voce precisa informar uma mensagem! "RESET" \n");
        return 1;
    }

    char commitCommand[512];
    snprintf(commitCommand, sizeof(commitCommand), "git commit -m \"%s\"", message);
    
    char pushCommand[512];
    snprintf(pushCommand, sizeof(pushCommand),"git push origin %s", branch);

    printf(YELLOW "[1/3] Adicionando arquivos..." RESET "\n");

    if(system("git add .") != 0) {
        printf(RED "[ERRO] Falha ao adicionar arquivos!" RESET "\n");
        return 1;
    }

    printf(GREEN "[OK] Arquivos adicionados!" RESET "\n");

    printf(YELLOW "[2/3] Commitando..." RESET "\n");

    if(system(commitCommand) != 0) {
        printf(RED "[ERRO] Falha ao criar commit!" RESET "\n");
        return 1;
    }

    printf(CYAN "[INFO] Commit: %s" RESET "\n", message);
    printf(GREEN "[OK] Commit realizado!" RESET "\n");

    printf(YELLOW "[3/3] Enviando para %s..." RESET "\n", branch);

    if(system(pushCommand) != 0) {
        printf(RED "[ERRO] Falha ao enviar para o repositorio!" RESET "\n");
        return 1;
    }

    printf(GREEN "[OK] Codigo enviado com sucesso!" RESET "\n");
    return 0;
}