#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    
    if(fork() == 0){
        execlp("ls","ls","-l",NULL);
        perror("ls");
        _exit(1);
    }

    wait(NULL); // O pai espera que o filhe termine , senão o filho continua a correr no bash

    return 0;
}