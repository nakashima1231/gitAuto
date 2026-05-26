#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void helpMenu() {
    printf("Uso:\n");
    printf("-b nomeDaBranch(main por padrao)\n");
    printf("-m MessagemCommit (Obrigatoria!)\n");
    printf("--help Menu de ajuda\n");
    printf("Exemplos: \n");
    printf(".\\gitAuto.exe \"consertando bug\"\n");
    printf(".\\gitAuto.exe -b dev -m \"consertando bug\"\n");
}


int main(int argc, char* argv[]) {

    char branch[100] = "master";
    char message[256] = "";

    if(argc == 2 && strcmp(argv[1], "--help") == 0) {
        helpMenu();
        return 0;
    }

    if(argc == 2) {
        strncpy(message, argv[1], sizeof(message) - 1);
        message[sizeof(message) - 1] = '\0';
    } else {
        for(int i = 1; i < argc; i++) {
            if(strcmp(argv[i], "-b") == 0 && (i + 1) < argc) {
                strncpy(branch, argv[++i], sizeof(branch) - 1);
                branch[sizeof(branch) - 1] = '\0';
            } else if(strcmp(argv[i], "-m") == 0 && (i + 1) < argc) {
                strncpy(message, argv[++i], sizeof(message) - 1);
                message[sizeof(message) - 1] = '\0';
            } else {
                printf("Argumento invalido: %s\n", argv[i]);
                return 1;   
            }
        }
    }

    if(strlen(message) == 0) {
        printf("Voce precisa informar uma mensagem com -m\n");
        return 1;
    }

    char commitCommand[512];
    snprintf(commitCommand, sizeof(commitCommand), "git commit -m \"%s\"", message);
    
    char pushCommand[512];
    snprintf(pushCommand, sizeof(pushCommand),"git push origin %s", branch);

    
    printf("\033[33m[1/3] Adicionando arquivos...\033[0m\n");

    if(system("git add .") != 0) {
        printf("\033[31m[ERRO] Falha ao adicionar arquivos!\033[0m\n");
        return 1;
    }

    printf("\033[32m[OK] Arquivos adicionados!\033[0m\n");

    printf("\033[33m[2/3] Commitando...\033[0m\n");

    if(system(commitCommand) != 0) {
        printf("\033[31m[ERRO] Falha ao criar commit!\033[0m\n");
        return 1;
    }

    printf("\033[36m[INFO] Commit: %s\033[0m\n", message);
    printf("\033[32m[OK] Commit realizado!\033[0m\n");

    printf("\033[33m[3/3] Enviando para %s...\033[0m\n", branch);

    if(system(pushCommand) != 0) {
        printf("\033[31m[ERRO] Falha ao enviar para o repositorio!\033[0m\n");
        return 1;
    }

    printf("\033[32m[OK] Codigo enviado com sucesso!\033[0m\n");
    return 0;
}