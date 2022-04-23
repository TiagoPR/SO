#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int main(int argc, char* argv[]){ // argc -> qtd de strings usadas para dar run ao programa || argv -> argumentos da linha de comando
    if (argc!= 3){
        fprintf(stderr,"usage: %s source destination\n", argv[0]);
        return 1;
    }

    int sfd = open(argv[1],O_RDONLY);
    if (sfd == -1){
        perror(argv[1]);
        return 1;
    }

    int dfd = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if (dfd == -1){
        perror(argv[2]);
        return 1;
    }

    int n;
    char c;
    while (1){
        n = read(sfd, &c, sizeof(c));
        if (n <= 0) break;
        write(dfd, &c, n);
    }
    close(sfd);
    close(dfd);

    return 0;
}