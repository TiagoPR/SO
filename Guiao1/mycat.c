#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int main(int argc, char* argv[]){ // argc -> qtd de strings usadas para dar run ao programa || argv -> argumentos da linha de comando
    if (argc!= 2){
        fprintf(stderr,"usage: %s source destination\n", argv[0]);
        return 1;
    }

    int sfd = open(argv[1],O_RDONLY);
    if (sfd == -1){
        perror(argv[1]);
        return 1;
    }
    int n;
    char c;
    while (1){
        n = read(sfd, &c, sizeof(c));
        if (n <= 0) break;
        printf("%c",c);
    }
    close(sfd);

    return 0;
}

