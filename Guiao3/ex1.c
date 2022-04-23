// int execlp(const char *file, const char *arg0, ..., NULL); 1- Ficheiro que queremos executar(nome) 2-(args) argumentos passados na consola , a última posicao
//                                                                                                             tem de ser um NULL
//                                                       /usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games (echo $PATH)

// se exec for bem sucedido o codigo abaixo nunca sera corrido

// int execvp(const char *file, char *const argv[]); mais flexível , mais trabalhoso

// char *coisas[]{
//     "ls",
//     "-l",
//     NULL;
// }

#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    // execlp("ls","ls","-l",NULL);
    // printf(blablla); // se execlp for bem sucedido nunca sera utilizado

    // if(fork() == 0){
    //     execlp("ls","ls","-l",NULL);
    //     perror("ls");
    //     _exit(1);
    // }
    // o pai espera que o processo filho acabe e dps pode-se fazer o temos abaixo

    execlp("ls","ls","-l",NULL);

    return 0;
}