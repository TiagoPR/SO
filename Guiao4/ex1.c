#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <fcntl.h> /* RDONLY */


int dup(int fd);

int dup2(int ofd, int dfd); // ofd é o soure , dfd é o destination

int main(){

    int outputOriginal = dup(1);

    int fd = open("/etc/passwd", O_RDONLY); close(0); dup(fd); close(fd); // ou com dup2:
    // int fd = open("/etc/passwd", O_RDONLY); dup2(fd,0); close(fd);

    int fd2 = open("/tmp/saida.txt",O_CREAT|O_WRONLY|O_TRUNC,0666); close(1); dup(fd2); close(fd2); // 2º parte da questao
    int fd3 = open("/tmp/erros.txt", O_CREAT|O_WRONLY|O_TRUNC,0666); dup2(fd3,2); close(fd3);

    // ou

    // close(0); fd = open("/etc/passwd", O_RDONLY); // alternativa em nao usar dup


    char nome[100];
    fgets(nome,sizeof(nome),stdin); // o stdin passa a ler o ficheiro pq mudamos o apontador com o dup em cima
    printf("ola, %s\n", nome); // escreve no ficheiro de saida
    // ou usar write(1,"ola",sizeof("ola")); que tem de escrever logo em vez de esperar por um printf
    fflush(stdout); // forçar a fazer os printf's em cima, senão passaria o dup2 primeiro do que o printf do ola
    dup2(outputOriginal,1); // com isto o 1 volta a apontar para o ecra
    printf("Terminei\n");
    return 0;
}