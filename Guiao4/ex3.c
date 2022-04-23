#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <fcntl.h> /* RDONLY */

int main(){

    int outputOriginal = dup(1);

    int fd = open("/etc/passwd", O_RDONLY); close(0); dup(fd); close(fd); // ou com dup2:
    // int fd = open("/etc/passwd", O_RDONLY); dup2(fd,0); close(fd);

    int fd2 = open("/tmp/saida.txt",O_CREAT|O_WRONLY|O_TRUNC,0666); close(1); dup(fd2); close(fd2); // 2º parte da questao
    int fd3 = open("/tmp/erros.txt", O_CREAT|O_WRONLY|O_TRUNC,0666); dup2(fd3,2); close(fd3);

    // ou

    // close(0); fd = open("/etc/passwd", O_RDONLY); // alternativa em nao usar dup

    execlp("wc","wc",NULL);
    perror("wc");

    fflush(stdout);
    dup2(outputOriginal,1);
    printf("Terminei\n");

    return 0;
}