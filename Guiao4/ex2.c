#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <fcntl.h> /* RDONLY */
#include <string.h>

int main(){

    int outputOriginal = dup(1);

    int fd = open("/etc/passwd", O_RDONLY); close(0); dup(fd); close(fd); // ou com dup2:
    // int fd = open("/etc/passwd", O_RDONLY); dup2(fd,0); close(fd);

    int fd2 = open("/tmp/saida.txt",O_CREAT|O_WRONLY|O_TRUNC,0666); close(1); dup(fd2); close(fd2); // 2º parte da questao
    int fd3 = open("/tmp/erros.txt", O_CREAT|O_WRONLY|O_TRUNC,0666); dup2(fd3,2); close(fd3);

    // ou

    // close(0); fd = open("/etc/passwd", O_RDONLY); // alternativa em nao usar dup

    if (fork() == 0)
    {
        char nome[100];
        fgets(nome,sizeof(nome),stdin); // o stdin passa a ler o ficheiro pq mudamos o apontador com o dup em cima
        printf("ola, %s\n", nome);
        // write(1,"ola",3);
        // write(1,nome,strlen(nome));
        fflush(stdout);
        _exit(1);
    }

    wait(0);

    dup2(outputOriginal,1);
    printf("Terminei");
    return 0;
}