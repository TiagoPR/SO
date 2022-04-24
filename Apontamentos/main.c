//
// Created by tiagorodrigues on 23-04-2022.
// ./sdstore proc-file banana.txt bananacomp.txt bcompress nop gcompress encrypt nop
// ./sdstore status
//

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h> 

int status(){
    return 0;
}

int procfile(int argc,char *argv[])
{
    // char* string [2];
    // char* comandos [1];
    // comandos[0] = (char *) malloc(sizeof (argv[0]) + 17);
    // string[0] = argv[1];
    // string[1] = argv[2];
    // strcat(comandos[0],"./SDStore-transf/");
    // strcat(comandos[0],argv[0]);
    // execvp(comandos[0],string);
    // //Funciona!

    // char* entrada_saida [2];
    // entrada_saida [0]= (char *) malloc(sizeof (argv[0]) + 4);
    // strcpy(entrada_saida[0],"< ");
    // entrada_saida [1]= (char *) malloc(sizeof (argv[1]));
    // strcat(entrada_saida [0],argv[0]);
    // strcpy(entrada_saida [1],argv[1]);
    // strcat(entrada_saida[0]," >");
    // printf("%s",entrada_saida[0]);
    // printf("%s",entrada_saida[1]);
    // for (int i = 2 ; i < argc ; i++)
    // {
    //     char transf [17 + strlen(argv[i])];
    //     strcpy(transf,"./SDStore-transf/");
    //     strcat(transf ,argv[i]);
    //     if (!fork())
    //     {
    //         //close(pipe_fd)
    //         execlp(transf,transf,entrada_saida[0], entrada_saida[1],NULL);
    //         _exit(1);
    //     }
    // }
    // wait(1);
    // return 0;

    char* args[3];
    char a[] = "< ";
    char b[] = " >";
    args[0] = (char *) malloc(sizeof(a) + sizeof(b) + sizeof(argv[0]));
    args[1] = (char *) malloc(sizeof(argv[1]));
    args[2] = NULL;

    strcpy( args[0], a );
    strcat( args[0], argv[0] );
    strcat( args[0], b );
    //printf("%s\n",args[0]);
    strcpy(args[1],argv[1]);
    //printf("%s\n",args[1]);

    int output = dup(1);
    int fd = open(args[1],O_CREAT|O_WRONLY|O_TRUNC,0666); dup2(fd,STDOUT_FILENO);

    execvp(argv[2],args); // O programa não termina sozinho

    close(fd);

    fflush(stdout);
    dup2(output,1);

}

int main (int argc, char *argv[]){

    // char *const parmList[] = {"./SDStore-transf/bcompress", "<banana.txt>", "banano", NULL};
    // execvp("./SDStore-transf/bcompress",parmList);
    //printf("%s %s\n",argv[0],argv[1]); // ele passa à frente o < banana.txt > banano no argv
    //printf("%d\n",argc);


    // printf("%s %s %s",argv[4],args[0],args[1]);
    // fflush(stdout);

    switch(strcmp(argv[1],"proc-file"))
    {
        case 0:
            procfile(argc-2,argv+2);
            break;
        default:
            //printf("OIiii");
            status();
            break;
    }
    //printf("OIiii");


    return 0;

}