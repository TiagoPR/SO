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

int status(){
    return 0;
}

int procfile(int argc,char *argv[])
{

    char* entrada_saida [2];
    entrada_saida [0]= (char *) malloc(sizeof (argv[0]) + 4);
    strcpy(entrada_saida[0],"< ");
    entrada_saida [1]= (char *) malloc(sizeof (argv[1]));
    strcat(entrada_saida [0],argv[0]);
    strcpy(entrada_saida [1],argv[1]);
    strcat(entrada_saida[0]," >");
    printf("%s",entrada_saida[0]);
    printf("%s",entrada_saida[1]);
    for (int i = 2 ; i < argc ; i++)
    {
        char transf [17 + strlen(argv[i])];
        strcpy(transf,"./SDStore-transf/");
        strcat(transf ,argv[i]);
        if (!fork())
        {
            //close(pipe_fd)
            execlp(transf,transf,entrada_saida[0], entrada_saida[1],NULL);
            _exit(1);
        }
    }
    wait(1);
    return 0;

}

int main (int argc, char *argv[]){

    // char *const parmList[] = {"./SDStore-transf/bcompress", "<banana.txt>", "banano", NULL};
    // execvp("./SDStore-transf/bcompress",parmList);

    execvp(argv[1],argv+1);

    // switch(strcmp(argv[1],"proc-file"))
    // {
    //     case 0:

    //         procfile(argc-2,argv+2);
    //         break;
    //     default:
    //         //printf("OIiii");
    //         status();
    //         break;
    // }
    // //printf("OIiii");


    return 0;

}