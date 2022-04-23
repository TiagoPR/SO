// history.h   wordexp.h   readline.h   getopt.h -> tips para criar a tua propria shell


#include <unistd.h>
#include <stdio.h>

int meuSystem(const char *command){
    char *linhas[80];
    int count = 1;
    linhas[0] = strtok(command," ");
    printf("%s",linhas[0]);
    char *token = linhas[0];
    char i[2] = " ";

    while (token != NULL)
    {
        token = strtok(NULL,i);
        linhas[count] = token;
        count++;
    }
    
    linhas[count] = NULL;

    if(fork() == 0){
        execvp(linhas[0],linhas);
        perror(linhas[0]);
        _exit(1);
    }

    return 0;
}

int main(int argc, char *argv[]){

    char comando[20] = "ls -l";
    int i = meuSystem(comando);

    return 0;
}