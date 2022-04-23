#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <string.h>

typedef struct pessoa
{
    /* data */
    char nome[128]; 
    //char sex; padding
    unsigned idade; // por ordem da idade devido ao padding
}Pessoa;

int encontra(int fd,char* nome){
    int tamanho = sizeof(struct pessoa);
    Pessoa p;
    int flag;
    int count=0;
    read(fd,&p,tamanho);
    while(flag > 0)
    {
        printf("%s\n" ,p.nome);
        printf("%s\n",nome);
        printf("    %d\n", strcmp(p.nome,nome));
        printf("    %d\n",count);
        printf("    %d\n" , count*tamanho);
        if(!(strcmp(p.nome,nome)))
        {
            return count * tamanho;
        }
        count++;
        flag = read(fd,&p,tamanho);
    }
    return 0;
}


int main(int argc, char* argv[]){

    if (argc!= 4){
        fprintf(stderr,"usage: %s source destination\n", argv[0]);
        return 1;
    }

    int fd;
    Pessoa pessoa;
    strcpy(pessoa.nome,argv[2]);
    pessoa.idade = atoi(argv[3]);

    int encontrou;



    if (!(strcmp(argv[1],"-i"))){

        int fd = open("registo", O_CREAT | O_APPEND | O_RDWR , 0666);

        if (fd == -1)
        {
            puts("ERROR - Couldn't open or create registry file.");
            return 1;
        }

        struct stat st;
        fstat(fd, &st);
        off_t filesize = st.st_size;

        encontrou = encontra(fd,argv[2]);

        if(!(encontrou)){
            printf("Registo %ld\n",filesize);
            if(write(fd, &pessoa ,sizeof(struct pessoa)) < 1) {
                puts("ERROR - Couldn't write to registry file.");
                close(fd);
                return 0;
            }   
        }   

        close(fd);
    }
    else if (!(strcmp(argv[1], "-u"))){
        int fd = open("registo",O_RDWR);

        if (fd == -1)
        {
            puts("ERROR - Couldn't open or create registry file.");
            return 1;
        }

        if((encontra(fd,argv[2])) > 0){
            lseek(fd,-sizeof(Pessoa),SEEK_CUR);

            if(write(fd, &pessoa ,sizeof(struct pessoa)) < 1) {
                puts("ERROR - Couldn't write to registry file.");
                close(fd);
                return 0;
            }
        }

        close(fd);

    }
    // struct pessoa p = {"Vitor",51};

    fd = open("registo", O_RDONLY);
    printf("\n");
    while(read(fd, &pessoa, sizeof(struct pessoa)) > 0) {
        printf("%s - %d\n", pessoa.nome, pessoa.idade);
    }
    close(fd);

    return 0;
}