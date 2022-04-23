#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <fcntl.h> /* RDONLY */



// p[0] -> leitura
// p[1] -> escrita

// pai para o filho

int main(){
    int p[2];
    char *line[] = {"linha1","linha2","linha3","linha4","linha5"};
    char buf;
    int num_lines = 5;
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
        //fechar descritor de escrita no filho (comentar para mostrar que o filho não termina)
        close(p[1]);
        while (read(p[0],&buf,sizeof(buf)))
        {
            printf("[FILHO]: read %c from pipe\n",buf); //não recomendado ler caracter a caracter por causa da eficiência, mas só assim "nao lemos a mais"
        }
        printf("[FILHO]: out of while\n");
        close(p[0]);
        _exit(0);
    
    default:
        //pai
        //fechar descritor de leitura no pai
        close(p[0]);
        for (int i = 0; i < num_lines; i++)
        {
            write(p[1],line[i],sizeof(line[i]));
            printf("[PAI]: wrote %s to pipe\n",line[i]);
            //sleep(10);
        }

        close(p[1]);
        wait(&status);
        printf("[PAI]: out of wait");
    }

    return 0;

}