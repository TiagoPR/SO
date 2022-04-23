#include <unistd.h>
#include <stdio.h>

// Para acabar a escrita -> CTRL + D 

int main(){
    int pd[2];
    char buffer[512];
    int nb;
    pipe(pd);
    switch (fork())
    {
    case 0: //filho
        dup2(pd[0], 0);
        close(pd[0]);
        close(pd[1]);
        execlp("wc", "wc", NULL); //faz o comando wc no pipe
        perror("wc");
        _exit(1);
        break;
    case 1: //pai, erro
        perror("fork");
        return 1;
    default: //pai,sucesso
        close(pd[0]);
        while ((nb = read(0, buffer, sizeof(buffer))) > 0) // read(0,...) lê do standard input
        {
            write(pd[1], buffer, nb); // escreve no pipe
        }
        close(pd[1]);
        
        break;
    }

    return 0; // EXIT_SUCESS => #include <stdlib.h>
}