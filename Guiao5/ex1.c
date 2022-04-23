#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <fcntl.h> /* RDONLY */



// p[0] -> leitura
// p[1] -> escrita

int main(){
    int p[2];
    char line[] = "linha1\n";
    char buffer[20];
    int res;
    int status;

    if (pipe(p) == -1)
    {
        perror("pipe");
        return -1;
    }

    switch (fork())
    {
    case -1:
        perror("fork");
        return -1;
    case 0:
        //filho
        //fechar descritor de leitura no filho
        close(p[0]);
        //sleep(5);
        write(p[1],&line,sizeof(line));
        printf("[FILHO]: wrote line to pipe\n");
        close(p[1]);
        _exit(0);
    
    default:
        //pai
        //fechar descritor de escrita no pai
        close(p[1]);
        //aqui o res é importante saber quantos lemos realmente
        res = read(p[0],&buffer,sizeof(buffer));
        printf("[PAI]: read %s from pipe\n",buffer);
        close(p[0]);

        wait(&status);
    }

    return 0;

}