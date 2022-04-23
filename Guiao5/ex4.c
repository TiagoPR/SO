#include <unistd.h>
#include <stdio.h>

int main(){
    int pd[2];
    pipe(pd);
    switch (fork())
    {
    case 0: //filho
        dup2(pd[1], 1);
        close(pd[0]);
        close(pd[1]);
        execlp("ls", "ls", "/etc", NULL); // Executa o ls
        perror("ls");
        _exit(1);
        break;
    case 1: //pai, erro
        perror("fork");
        return 1; /* EXIT_FAILURE */
    default: //pai,sucesso
        dup2(pd[0], 0);
        close(pd[0]);
        close(pd[1]);
        execlp("wc", "wc", "-l", NULL); // o wc fica a espera do endLine do ls no pipe
        perror("wc");
        _exit(1);
    }

    return 0; // EXIT_SUCESS => #include <stdlib.h>
}